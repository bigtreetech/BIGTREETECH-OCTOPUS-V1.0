/*
 * AnalogIn_SAMC21.cpp
 *
 *  Created on: 20 Aug 2019
 *      Author: David
 */

#ifdef RTOS

#include <CoreIO.h>

#if !SAMC21
# error Wrong processor!
#endif

#include "AnalogIn.h"
#include <RTOSIface/RTOSIface.h>
#include <DmacManager.h>
#include <Cache.h>

#include <hri_adc_c21.h>
#include <hri_sdadc_c21.h>

#define ADC_INPUTCTRL_MUXNEG_GND   (0x18 << ADC_INPUTCTRL_MUXNEG_Pos)			// this definition is missing from file adc.h for the SAMC21

#ifndef SUPPORT_SDADC
# define SUPPORT_SDADC	1
#endif

constexpr unsigned int AdcGclkNum = GclkNum48MHz;
constexpr uint32_t AdcConversionTimeout = 5;		// milliseconds

static uint32_t conversionsStarted = 0;
static uint32_t conversionsCompleted = 0;
static uint32_t conversionTimeouts = 0;
static uint32_t errors = 0;

static AnalogInCallbackFunction tempCallbackFn = nullptr;
static CallbackParameter tempCallbackParam;
static uint32_t tempTicksPerCall = 1;

static uint32_t tempTicksAtLastCall = 0;

class AdcBase
{
public:
	enum class State : uint8_t
	{
		noChannels = 0,
		starting,
		idle,
		converting,
		ready
	};

	AdcBase(DmaChannel p_dmaChan, DmaPriority priority, DmaTrigSource p_trigSrc) noexcept;

	virtual bool StartConversion() noexcept = 0;
	virtual void ExecuteCallbacks() noexcept = 0;

	bool ConversionDone() noexcept;
	bool EnableChannel(unsigned int chan, AnalogInCallbackFunction fn, CallbackParameter param, uint32_t p_ticksPerCall) noexcept;
	bool SetCallback(unsigned int chan, AnalogInCallbackFunction fn, CallbackParameter param, uint32_t p_ticksPerCall) noexcept;
	bool IsChannelEnabled(unsigned int chan) const noexcept;
	uint16_t ReadChannel(unsigned int chan) const noexcept { return resultsByChannel[chan]; }
	void Exit() noexcept;

	void EnableTemperatureSensor() noexcept;

	void ResultReadyCallback(DmaCallbackReason reason) noexcept;

protected:
	virtual bool InternalEnableChannel(unsigned int chan, AnalogInCallbackFunction fn, CallbackParameter param, uint32_t p_ticksPerCall) noexcept = 0;

	static void DmaCompleteCallback(CallbackParameter cp, DmaCallbackReason reason) noexcept;

	static constexpr size_t NumAdcChannels = 12;		// number of channels per ADC
	static constexpr size_t MaxSequenceLength = 12;		// the maximum length of the read sequence

	const DmaChannel dmaChan;
	const DmaPriority dmaPrio;
	const DmaTrigSource trigSrc;

	volatile DmaCallbackReason dmaFinishedReason;
	volatile size_t numChannelsEnabled;
	volatile uint32_t channelsEnabled;
	volatile TaskHandle taskToWake;
	uint32_t whenLastConversionStarted;
	volatile State state;
	bool justStarted;
	AnalogInCallbackFunction callbackFunctions[NumAdcChannels];
	CallbackParameter callbackParams[NumAdcChannels];
	uint32_t ticksPerCall[NumAdcChannels];
	uint32_t ticksAtLastCall[NumAdcChannels];
	volatile uint16_t results[MaxSequenceLength];
	volatile uint16_t resultsByChannel[NumAdcChannels];
};

AdcBase::AdcBase(DmaChannel p_dmaChan, DmaPriority priority, DmaTrigSource p_trigSrc) noexcept
	: dmaChan(p_dmaChan), dmaPrio(priority), trigSrc(p_trigSrc),
	  numChannelsEnabled(0), channelsEnabled(0),
	  taskToWake(nullptr), whenLastConversionStarted(0), state(State::noChannels)
{
	for (size_t i = 0; i < NumAdcChannels; ++i)
	{
		callbackFunctions[i] = nullptr;
		callbackParams[i].u32 = 0;
		resultsByChannel[i] = 0;
	}
}

// Shut down the ADC, making it safe to terminate the AnalogIn task
void AdcBase::Exit() noexcept
{
	taskToWake = nullptr;
	DmacManager::DisableCompletedInterrupt(dmaChan);		// disable the reader completed interrupt
	DmacManager::DisableChannel(dmaChan);					// disable the reader DMA
}

// Try to enable this ADC on the specified pin returning true if successful
// Only single ended mode with gain x1 is supported
// There is no check to avoid adding the same channel twice. If you do that it will be converted twice.
bool AdcBase::EnableChannel(unsigned int chan, AnalogInCallbackFunction fn, CallbackParameter param, uint32_t p_ticksPerCall) noexcept
{
	if (numChannelsEnabled == MaxSequenceLength || chan >= NumAdcChannels)
	{
		return false;
	}

	return InternalEnableChannel(chan, fn, param, p_ticksPerCall);
}

bool AdcBase::SetCallback(unsigned int chan, AnalogInCallbackFunction fn, CallbackParameter param, uint32_t p_ticksPerCall) noexcept
{
	if (IsChannelEnabled(chan))
	{
		AtomicCriticalSectionLocker lock;

		callbackFunctions[chan] = fn;
		callbackParams[chan] = param;
		ticksPerCall[chan] = p_ticksPerCall;
		ticksAtLastCall[chan] = millis();
		return true;
	}
	return false;
}

bool AdcBase::IsChannelEnabled(unsigned int chan) const noexcept
{
	return (channelsEnabled & (1ul << chan)) != 0;
}

// Indirect callback from the DMA controller ISR
void AdcBase::ResultReadyCallback(DmaCallbackReason reason) noexcept
{
	dmaFinishedReason = reason;
	state = State::ready;
	++conversionsCompleted;
	DmacManager::DisableChannel(dmaChan);			// disable the sequencer DMA, just in case it is out of sync
	if (taskToWake != nullptr)
	{
		TaskBase::GiveFromISR(taskToWake);
	}
}

// Callback from the DMA controller ISR
/*static*/ void AdcBase::DmaCompleteCallback(CallbackParameter cp, DmaCallbackReason reason) noexcept
{
	static_cast<AdcBase *>(cp.vp)->ResultReadyCallback(reason);
}

// Check whether the conversion was successful
bool AdcBase::ConversionDone() noexcept
{
	if (state == State::ready)
	{
		if (dmaFinishedReason == DmaCallbackReason::complete)
		{
			return true;
		}

		++errors;
	}
	return false;
}


class AdcClass : public AdcBase
{
public:
	AdcClass(Adc * const p_device, DmaChannel p_dmaChan, DmaPriority priority, DmaTrigSource p_trigSrc) noexcept;

	bool StartConversion() noexcept override;
	void ExecuteCallbacks() noexcept override;

protected:
	bool InternalEnableChannel(unsigned int chan, AnalogInCallbackFunction fn, CallbackParameter param, uint32_t p_ticksPerCall) noexcept override;
	void ReInit() noexcept;

private:
	Adc * const device;
};

AdcClass::AdcClass(Adc * const p_device, DmaChannel p_dmaChan, DmaPriority priority, DmaTrigSource p_trigSrc) noexcept
	: AdcBase(p_dmaChan, priority, p_trigSrc), device(p_device)
{
}

void AdcClass::ReInit() noexcept
{
	if (!hri_adc_is_syncing(device, ADC_SYNCBUSY_SWRST))
	{
		if (hri_adc_get_CTRLA_reg(device, ADC_CTRLA_ENABLE))
		{
			hri_adc_clear_CTRLA_ENABLE_bit(device);
			hri_adc_wait_for_sync(device, ADC_SYNCBUSY_ENABLE);
		}
		hri_adc_write_CTRLA_reg(device, ADC_CTRLA_SWRST);
	}
	hri_adc_wait_for_sync(device, ADC_SYNCBUSY_SWRST);

	hri_adc_write_CTRLB_reg(device, ADC_CTRLB_PRESCALER_DIV4);			// Max ADC clock is 16MHz. GCLK0 is 48MHz, divided by 4 is 12MHz
#if defined(EXP1XD) || defined(EXP1HCE)
	hri_adc_write_CTRLC_reg(device, ADC_CTRLC_RESSEL_16BIT | ADC_CTRLC_R2R);	// 16 bit result, rail-to-rail input
#else
	hri_adc_write_CTRLC_reg(device, ADC_CTRLC_RESSEL_16BIT);			// 16 bit result
#endif
	hri_adc_write_REFCTRL_reg(device,  ADC_REFCTRL_REFSEL_INTVCC2);
	hri_adc_write_EVCTRL_reg(device, ADC_EVCTRL_RESRDYEO);
	hri_adc_write_INPUTCTRL_reg(device, ADC_INPUTCTRL_MUXNEG_GND);
	hri_adc_write_AVGCTRL_reg(device, ADC_AVGCTRL_SAMPLENUM_64);		// average 64 measurements
	hri_adc_write_SAMPCTRL_reg(device, ADC_SAMPCTRL_OFFCOMP);			// enable comparator offset compensation, sampling time is fixed at 4 ADC clocks
	hri_adc_write_WINLT_reg(device, 0);
	hri_adc_write_WINUT_reg(device, 0xFFFF);
	hri_adc_write_GAINCORR_reg(device, 1u << 11);
	hri_adc_write_OFFSETCORR_reg(device, 0);
	hri_adc_write_DBGCTRL_reg(device, 0);

	// Load CALIB with NVM data calibration results
	do
	{
		uint32_t biasComp, biasRefbuf;
		if (device == ADC0)
		{
			biasComp = (*reinterpret_cast<const uint32_t*>(ADC0_FUSES_BIASCOMP_ADDR) & ADC0_FUSES_BIASCOMP_Msk) >> ADC0_FUSES_BIASCOMP_Pos;
			biasRefbuf = (*reinterpret_cast<const uint32_t*>(ADC0_FUSES_BIASREFBUF_ADDR) & ADC0_FUSES_BIASREFBUF_Msk) >> ADC0_FUSES_BIASREFBUF_Pos;
		}
		else if (device == ADC1)
		{
			biasComp = (*reinterpret_cast<const uint32_t*>(ADC1_FUSES_BIASCOMP_ADDR) & ADC1_FUSES_BIASCOMP_Msk) >> ADC1_FUSES_BIASCOMP_Pos;
			biasRefbuf = (*reinterpret_cast<const uint32_t*>(ADC1_FUSES_BIASREFBUF_ADDR) & ADC1_FUSES_BIASREFBUF_Msk) >> ADC1_FUSES_BIASREFBUF_Pos;
		}
		else
		{
			break;
		}
		hri_adc_write_CALIB_reg(device, ADC_CALIB_BIASCOMP(biasComp) | ADC_CALIB_BIASREFBUF(biasRefbuf));
	} while (false);

	hri_adc_set_CTRLA_ENABLE_bit(device);

	// Initialise the DMAC to read the result
	DmacManager::DisableChannel(dmaChan);
	DmacManager::SetBtctrl(dmaChan, DMAC_BTCTRL_VALID | DMAC_BTCTRL_EVOSEL_DISABLE | DMAC_BTCTRL_BLOCKACT_INT | DMAC_BTCTRL_BEATSIZE_HWORD
								| DMAC_BTCTRL_DSTINC | DMAC_BTCTRL_STEPSEL_DST | DMAC_BTCTRL_STEPSIZE_X1);
	DmacManager::SetSourceAddress(dmaChan, const_cast<uint16_t *>(&device->RESULT.reg));
	DmacManager::SetInterruptCallback(dmaChan, DmaCompleteCallback, this);
	DmacManager::SetTriggerSource(dmaChan, trigSrc);
}

// A note on ADC timings.
// The maximum clock frequency of the ADC is 16MHz. We could probably generate this by running the DPLL at 96MHz, but for simplicity we run the ADC at 48MHz/4 = 12MHz.
// Each conversion takes 17 clocks with comparator offset compensation enabled. That's 1.5167us per conversion.
// We have a maximum of 6 input channels: 3 temperature, Vref, Vssa, and the Z probe. If we enable all of them, that's 8.5us per set of conversions.
// If we average 128 readings in hardware, a full set of conversions takes 1.088ms, a little longer than the time between tick interrupts.
// Averaging 64 readings seems to give us lower noise.
bool AdcClass::InternalEnableChannel(unsigned int chan, AnalogInCallbackFunction fn, CallbackParameter param, uint32_t p_ticksPerCall) noexcept
{
	if (chan < NumAdcChannels)
	{
		TaskCriticalSectionLocker lock;

		// Set up the ADC
		callbackFunctions[chan] = fn;
		callbackParams[chan] = param;
		ticksPerCall[chan] = p_ticksPerCall;
		ticksAtLastCall[chan] = millis();
		resultsByChannel[chan] = 0;
		if ((channelsEnabled & 1ul << chan) == 0)
		{
			channelsEnabled |= 1ul << chan;
			++numChannelsEnabled;

			if (numChannelsEnabled == 1)
			{
				// First channel is being enabled, so initialise the ADC
				ReInit();
				state = State::starting;
			}
		}

		return true;
	}

	return false;
}

// Start a conversion if we are not already doing one and have channels to convert, or timeout an existing conversion
bool AdcClass::StartConversion() noexcept
{
	const size_t numChannelsConverting = numChannelsEnabled;			// capture volatile variable to ensure we use a consistent value
	if (numChannelsConverting == 0)
	{
		return false;
	}

	if (state == State::converting)
	{
		if (millis() - whenLastConversionStarted < AdcConversionTimeout)
		{
			return false;
		}
		++conversionTimeouts;
		ReInit();
	}

	taskToWake = TaskBase::GetCallerTaskHandle();

	DmacManager::DisableChannel(dmaChan);

	(void)device->RESULT.reg;			// make sure no result pending

	device->SEQCTRL.reg = channelsEnabled;

	// Set up DMA to read the results our of the ADC into the results array
	DmacManager::SetDestinationAddress(dmaChan, results);
	DmacManager::SetDataLength(dmaChan, numChannelsConverting);

	dmaFinishedReason = DmaCallbackReason::none;
	DmacManager::EnableCompletedInterrupt(dmaChan);

	DmacManager::EnableChannel(dmaChan, dmaPrio);

	state = State::converting;
	device->SWTRIG.reg = ADC_SWTRIG_START;
	++conversionsStarted;
	whenLastConversionStarted = millis();
	return true;
}

void AdcClass::ExecuteCallbacks() noexcept
{
	Cache::InvalidateAfterDMAReceive(results, sizeof(results));
	TaskCriticalSectionLocker lock;

	const uint32_t now = millis();
	const volatile uint16_t *p = results;
	const uint32_t channelsPreviouslyEnabled = device->SEQCTRL.reg;
	for (size_t i = 0; i < NumAdcChannels; ++i)
	{
		if ((channelsPreviouslyEnabled & (1ul << i)) != 0)
		{
			const uint16_t currentResult = *p++;
			resultsByChannel[i] = currentResult;
			if (now - ticksAtLastCall[i] >= ticksPerCall[i])
			{
				ticksAtLastCall[i] = now;
				const AnalogInCallbackFunction fn = callbackFunctions[i];
				if (fn != nullptr)
				{
					fn(callbackParams[i], currentResult);
				}
			}
		}
	}
}

#if SUPPORT_SDADC

class SdAdcClass : public AdcBase
{
public:
	SdAdcClass(Sdadc * const p_device, DmaChannel p_dmaChan, DmaPriority priority, DmaTrigSource p_trigSrc) noexcept;

	bool StartConversion() noexcept override;
	void ExecuteCallbacks() noexcept override;

protected:
	bool InternalEnableChannel(unsigned int chan, AnalogInCallbackFunction fn, CallbackParameter param, uint32_t p_ticksPerCall) noexcept override;
	void ReInit() noexcept;

private:
	static constexpr size_t NumSdAdcChannels = 2;

	Sdadc * const device;
};

SdAdcClass::SdAdcClass(
	Sdadc * const p_device, DmaChannel p_dmaChan, DmaPriority priority, DmaTrigSource p_trigSrc) noexcept
	: AdcBase(p_dmaChan, priority, p_trigSrc), device(p_device)
{
}

// Start a conversion if we are not already doing one and have channels to convert, or timeout an existing conversion
bool SdAdcClass::StartConversion() noexcept
{
	const size_t numChannelsConverting = numChannelsEnabled;			// capture volatile variable to ensure we use a consistent value
	if (numChannelsConverting == 0)
	{
		return false;
	}

	if (state == State::converting)
	{
		if (millis() - whenLastConversionStarted < AdcConversionTimeout)
		{
			return false;
		}
		++conversionTimeouts;
		ReInit();
	}

	taskToWake = TaskBase::GetCallerTaskHandle();
	(void)device->RESULT.reg;			// make sure no result pending
	device->SEQCTRL.reg = channelsEnabled;

	// Set up DMA to read the results our of the ADC into the results array
	DmacManager::SetDestinationAddress(dmaChan, results);
	DmacManager::SetDataLength(dmaChan, numChannelsConverting);

	dmaFinishedReason = DmaCallbackReason::none;
	DmacManager::EnableCompletedInterrupt(dmaChan);

	DmacManager::EnableChannel(dmaChan, dmaPrio);

	state = State::converting;
	device->SWTRIG.reg = SDADC_SWTRIG_START;
	++conversionsStarted;
	whenLastConversionStarted = millis();
	return true;
}

void SdAdcClass::ExecuteCallbacks() noexcept
{
	Cache::InvalidateAfterDMAReceive(results, sizeof(results));
	TaskCriticalSectionLocker lock;
	const uint32_t now = millis();
	const volatile uint16_t *p = results;
	const uint32_t channelsPreviouslyEnabled = device->SEQCTRL.reg;
	for (size_t i = 0; i < NumSdAdcChannels; ++i)
	{
		if ((channelsPreviouslyEnabled & (1ul << i)) != 0)
		{
			const uint16_t currentResult = *p++;
			resultsByChannel[i] = currentResult;
			if (now - ticksAtLastCall[i] >= ticksPerCall[i])
			{
				ticksAtLastCall[i] = now;
				const AnalogInCallbackFunction fn = callbackFunctions[i];
				if (fn != nullptr)
				{
					fn(callbackParams[i], currentResult);
				}
			}
		}
	}
}

void SdAdcClass::ReInit() noexcept
{
	if (!hri_sdadc_is_syncing(device, SDADC_SYNCBUSY_SWRST))
	{
		if (hri_sdadc_get_CTRLA_reg(device, SDADC_CTRLA_ENABLE))
		{
			hri_sdadc_clear_CTRLA_ENABLE_bit(device);
			hri_sdadc_wait_for_sync(device, SDADC_SYNCBUSY_ENABLE);
		}
		hri_sdadc_write_CTRLA_reg(device, SDADC_CTRLA_SWRST);
	}
	hri_sdadc_wait_for_sync(device, SDADC_SYNCBUSY_SWRST);

	// Min SDADC clock is 1MHz, max is 6MHz. GCLK0 is 48MHz, divided by prescaler 8 is 6MHz
	static constexpr uint16_t SDADC_OSR_256 = 0x02;
	hri_sdadc_write_CTRLB_reg(device, SDADC_CTRLB_PRESCALER(8/2 - 1) | SDADC_CTRLB_OSR(SDADC_OSR_256) | SDADC_CTRLB_SKPCNT(4));
	hri_sdadc_write_REFCTRL_reg(device, SDADC_REFCTRL_REFSEL_INTVCC | SDADC_REFCTRL_REFRANGE(0x3));
	hri_sdadc_write_EVCTRL_reg(device, SDADC_EVCTRL_RESRDYEO);
	hri_sdadc_write_WINLT_reg(device, 0);
	hri_sdadc_write_WINUT_reg(device, 0xFFFF);
	hri_sdadc_write_GAINCORR_reg(device, 1);
	hri_sdadc_write_OFFSETCORR_reg(device, 0);
	hri_sdadc_write_SHIFTCORR_reg(device, 7);			// convert 24-bit positive signed result to 16-bit unsigned
	hri_sdadc_set_ANACTRL_ONCHOP_bit(device);
	hri_sdadc_write_DBGCTRL_reg(device, 0);

	hri_sdadc_set_CTRLA_ENABLE_bit(device);

	// Initialise the DMAC to read the result. The result register is 32 bits wide but we are only interested in the lowest 16 bits.
	DmacManager::SetBtctrl(dmaChan, DMAC_BTCTRL_VALID | DMAC_BTCTRL_EVOSEL_DISABLE | DMAC_BTCTRL_BLOCKACT_INT | DMAC_BTCTRL_BEATSIZE_HWORD
								| DMAC_BTCTRL_DSTINC | DMAC_BTCTRL_STEPSEL_DST | DMAC_BTCTRL_STEPSIZE_X1);
	DmacManager::SetSourceAddress(dmaChan, const_cast<uint16_t *>(reinterpret_cast<volatile uint16_t*>(&device->RESULT.reg)));
	DmacManager::SetInterruptCallback(dmaChan, DmaCompleteCallback, this);
	DmacManager::SetTriggerSource(dmaChan, trigSrc);
}

bool SdAdcClass::InternalEnableChannel(unsigned int chan, AnalogInCallbackFunction fn, CallbackParameter param, uint32_t p_ticksPerCall) noexcept
{
	if (chan < NumSdAdcChannels)
	{
		TaskCriticalSectionLocker lock;

		// Set up the ADC
		callbackFunctions[chan] = fn;
		callbackParams[chan] = param;
		ticksPerCall[chan] = p_ticksPerCall;
		ticksAtLastCall[chan] = millis();
		resultsByChannel[chan] = 0;

		if ((channelsEnabled & 1ul << chan) == 0)
		{
			channelsEnabled |= 1ul << chan;
			++numChannelsEnabled;

			if (numChannelsEnabled == 1)
			{
				// First channel is being enabled, so initialise the ADC
				ReInit();
				state = State::starting;
			}
		}

		return true;
	}

	return false;
}

#endif	// SUPPORT_SDADC

// ADC instances
static AdcBase *adcs[1 + SUPPORT_SDADC];

// Main loop executed by the AIN task
void AnalogIn::TaskLoop(void*) noexcept
{
	// Loop taking readings and processing them
	for (;;)
	{
		// Loop through ADCs
		bool conversionStarted = false;
		for (AdcBase*& adc : adcs)
		{
			if (adc->ConversionDone())
			{
				adc->ExecuteCallbacks();
			}
			if (adc->StartConversion())
			{
				conversionStarted = true;
			}
		}

		// Do the temperature sensor
		const AnalogInCallbackFunction fn = tempCallbackFn;
		if (tempCallbackFn != nullptr && TSENS->INTFLAG.bit.RESRDY)
		{
			const uint32_t now = millis();
			if (now - tempTicksAtLastCall >= tempTicksPerCall)
			{
				tempTicksAtLastCall = now;
				fn(tempCallbackParam, (TSENS->VALUE.bit.VALUE & 0xFFFF) ^ (1u << 15));		// VALUE is 2's complement, but the filter expects unsigned values
				TSENS->CTRLB.bit.START = 1;
			}
		}

		if (conversionStarted)
		{
			TaskBase::Take(100);
			delay(2);
		}
		else
		{
			// No ADCs enabled yet, or all converting
			delay(10);
		}
	}
}

// Initialise the analog input subsystem. Call this just once.
void AnalogIn::Init(DmaChannel dmaChan, DmaPriority priority) noexcept
{
	// Create the device instances
	adcs[0] = new AdcClass(ADC0, dmaChan, priority, DmaTrigSource::adc0_resrdy);
#if SUPPORT_SDADC
	adcs[1] = new SdAdcClass(SDADC, dmaChan + 1, priority, DmaTrigSource::sdadc_resrdy);
#endif

	// Enable ADC clocks. SAMC21 has 2 ADCs but we use only the first one
	hri_mclk_set_APBCMASK_ADC0_bit(MCLK);
	hri_gclk_write_PCHCTRL_reg(GCLK, ADC0_GCLK_ID, GCLK_PCHCTRL_GEN(AdcGclkNum) | GCLK_PCHCTRL_CHEN);

#if SUPPORT_SDADC
	// SAMC21 also has a SDADC
	hri_mclk_set_APBCMASK_SDADC_bit(MCLK);
	hri_gclk_write_PCHCTRL_reg(GCLK, SDADC_GCLK_ID, GCLK_PCHCTRL_GEN(AdcGclkNum) | GCLK_PCHCTRL_CHEN);
#endif
}

// Shut down the analog system. making it safe to terminate the AnalogIn task
void AnalogIn::Exit() noexcept
{
	adcs[0]->Exit();
#if SUPPORT_SDADC
	adcs[1]->Exit();
#endif
}

// Enable analog input on a pin.
// Readings will be taken and about every 'ticksPerCall' milliseconds the callback function will be called with the specified parameter and ADC reading.
// Set ticksPerCall to 0 to get a callback on every reading.
bool AnalogIn::EnableChannel(AdcInput adcin, AnalogInCallbackFunction fn, CallbackParameter param, uint32_t ticksPerCall, bool useAlternateAdc) noexcept
{
	const unsigned int deviceNumber = GetDeviceNumber(adcin);
	if (deviceNumber < ARRAY_SIZE(adcs))				// this test handles AdcInput::none as well as out-of-range ADC numbers
	{
		return adcs[deviceNumber]->EnableChannel(GetInputNumber(adcin), fn, param, ticksPerCall);
	}
	return false;
}

// Readings will be taken and about every 'ticksPerCall' milliseconds the callback function will be called with the specified parameter and ADC reading.
// Set ticksPerCall to 0 to get a callback on every reading.
bool AnalogIn::SetCallback(AdcInput adcin, AnalogInCallbackFunction fn, CallbackParameter param, uint32_t ticksPerCall, bool useAlternateAdc) noexcept
{
	const unsigned int deviceNumber = GetDeviceNumber(adcin);
	if (deviceNumber < ARRAY_SIZE(adcs))				// this test handles AdcInput::none as well as out-of-range ADC numbers
	{
		return adcs[deviceNumber]->SetCallback(GetInputNumber(adcin), fn, param, ticksPerCall);
	}
	return false;
}

// Return whether or not the channel is enabled
bool AnalogIn::IsChannelEnabled(AdcInput adcin, bool useAlternateAdc) noexcept
{
	const unsigned int deviceNumber = GetDeviceNumber(adcin);
	if (deviceNumber < ARRAY_SIZE(adcs))				// this test handles AdcInput::none as well as out-of-range ADC numbers
	{
		return adcs[deviceNumber]->IsChannelEnabled(GetInputNumber(adcin));
	}
	return false;
}

// Disable a previously-enabled channel
void AnalogIn::DisableChannel(AdcInput adcin, bool useAlternateAdc) noexcept
{
	//TODO not implemented yet (do we need it?)
}

uint16_t AnalogIn::ReadChannel(AdcInput adcin) noexcept
{
	const unsigned int deviceNumber = GetDeviceNumber(adcin);
	return (deviceNumber < ARRAY_SIZE(adcs))				// this test handles AdcInput::none as well as out-of-range ADC numbers
			? adcs[deviceNumber]->ReadChannel(GetInputNumber(adcin))
				: 0;
}

// Enable an on-chip MCU temperature sensor
void AnalogIn::EnableTemperatureSensor(AnalogInCallbackFunction fn, CallbackParameter param, uint32_t ticksPerCall) noexcept
{
	tempCallbackParam = param;
	tempCallbackFn = fn;
	tempTicksPerCall = ticksPerCall;

	hri_mclk_set_APBAMASK_TSENS_bit(MCLK);
	hri_gclk_write_PCHCTRL_reg(GCLK, TSENS_GCLK_ID, GCLK_PCHCTRL_GEN_GCLK0_Val | (1 << GCLK_PCHCTRL_CHEN_Pos));		// use the main 48MHz as the clock source, it gives better readings than the DFLL

	TSENS->CTRLA.bit.SWRST = 1;
	while (TSENS->CTRLA.bit.SWRST) { }
	TSENS->CTRLC.reg = 0;

	const uint32_t calGain0 = (*reinterpret_cast<const uint32_t*>(TSENS_FUSES_GAIN_0_ADDR) & TSENS_FUSES_GAIN_0_Msk) >> TSENS_FUSES_GAIN_0_Pos;
	const uint32_t calGain1 = (*reinterpret_cast<const uint32_t*>(TSENS_FUSES_GAIN_1_ADDR) & TSENS_FUSES_GAIN_1_Msk) >> TSENS_FUSES_GAIN_1_Pos;
	const uint32_t calOffset = (*reinterpret_cast<const uint32_t*>(TSENS_FUSES_OFFSET_ADDR) & TSENS_FUSES_OFFSET_Msk) >> TSENS_FUSES_OFFSET_Pos;
	const uint32_t calFcal = (*reinterpret_cast<const uint32_t*>(TSENS_FUSES_FCAL_ADDR) & TSENS_FUSES_FCAL_Msk) >> TSENS_FUSES_FCAL_Pos;
	const uint32_t calTcal = (*reinterpret_cast<const uint32_t*>(TSENS_FUSES_TCAL_ADDR) & TSENS_FUSES_TCAL_Msk) >> TSENS_FUSES_TCAL_Pos;

	TSENS->GAIN.reg = calGain0 | (calGain1 << 20);
	TSENS->OFFSET.reg = calOffset;
	TSENS->CAL.reg = TSENS_CAL_TCAL(calTcal) | TSENS_CAL_FCAL(calFcal);

	TSENS->CTRLA.bit.ENABLE = 1;
	while (TSENS->SYNCBUSY.bit.ENABLE) { }
	TSENS->CTRLB.reg = TSENS_CTRLB_START;
}

void AnalogIn::GetDebugInfo(uint32_t &convsStarted, uint32_t &convsCompleted, uint32_t &convTimeouts, uint32_t& errs) noexcept
{
	convsStarted = conversionsStarted;
	convsCompleted = conversionsCompleted;
	convTimeouts = conversionTimeouts;
	errs = errors;
}

#endif

// End
