/*
 * AnalogIn.cpp
 *
 *  Created on: 6 Sep 2018
 *      Author: David
 */

#ifdef RTOS

#include <CoreIO.h>

#if !SAME5x
# error Wrong processor!
#endif

#include "AnalogIn.h"
#include <RTOSIface/RTOSIface.h>

#include <hri_adc_e54.h>

constexpr unsigned int AdcGclkNum = GclkNum60MHz;
constexpr uint32_t AdcConversionTimeout = 5;		// milliseconds

static uint32_t conversionsStarted = 0;
static uint32_t conversionsCompleted = 0;
static uint32_t conversionTimeouts = 0;
static uint32_t errors = 0;

// DMA sequencing in this MCU is an abomination. It goes wrong in the presence of SBC SPI DMA and recovery is difficult, because we need to set the AUTOSTART bit
// to convert a whole sequence, and that means that a new sequence will start as soon as the old one has finished.
// So now we use one interrupt per channel so that we can avoid using DMA.

// Register values we send. These are constant except for INPUTCTRL which changes to select the required ADC channel
constexpr uint32_t CtrlB = ADC_CTRLB_RESSEL_16BIT;
constexpr uint32_t RefCtrl = ADC_REFCTRL_REFSEL_INTVCC1;
constexpr uint32_t AvgCtrl = ADC_AVGCTRL_SAMPLENUM_64;
constexpr uint32_t SampCtrl = ADC_SAMPCTRL_OFFCOMP;

class AdcClass
{
public:
	enum class State : uint8_t
	{
		noChannels = 0,
		starting,
		converting,
		ready
	};

	AdcClass(Adc * const p_device, IRQn irqn, NvicPriority irqPriority) noexcept;

	bool ConversionDone() noexcept;
	bool EnableChannel(unsigned int chan, AnalogInCallbackFunction fn, CallbackParameter param, uint32_t p_ticksPerCall) noexcept;
	bool SetCallback(unsigned int chan, AnalogInCallbackFunction fn, CallbackParameter param, uint32_t p_ticksPerCall) noexcept;
	bool IsChannelEnabled(unsigned int chan) const noexcept;
	bool StartConversion() noexcept;
	uint16_t ReadChannel(unsigned int chan) const noexcept { return resultsByChannel[chan]; }
	bool EnableTemperatureSensor(unsigned int sensorNumber, AnalogInCallbackFunction fn, CallbackParameter param, uint32_t p_ticksPerCall) noexcept;

	void ExecuteCallbacks() noexcept;

	void Exit() noexcept;

	void ResultReadyInterrupt() noexcept;

private:
	bool InternalEnableChannel(unsigned int chan, AnalogInCallbackFunction fn, CallbackParameter param, uint32_t p_ticksPerCall) noexcept;
	size_t GetChannel(size_t slot) noexcept { return inputRegisters[slot].inputCtrl & 0x1F; }
	void ReInit() noexcept;

	static constexpr size_t NumAdcChannels = 32;				// number of channels per ADC including temperature sensor inputs etc.
	static constexpr size_t MaxSequenceLength = 16;				// the maximum length of the read sequence

	struct InputRegisters
	{
		uint16_t inputCtrl;
		uint16_t avgCtrl;
	};

	Adc * const device;
	const IRQn irqNumber;
	volatile size_t numChannelsEnabled;							// volatile because multiple tasks access it
	size_t numChannelsConverting;
	volatile uint32_t channelsEnabled;
	volatile TaskHandle taskToWake;
	uint32_t whenLastConversionStarted;
	uint32_t currentChannel;
	volatile State state;
	AnalogInCallbackFunction callbackFunctions[MaxSequenceLength];
	CallbackParameter callbackParams[MaxSequenceLength];
	uint32_t ticksPerCall[MaxSequenceLength];
	uint32_t ticksAtLastCall[MaxSequenceLength];
	InputRegisters inputRegisters[MaxSequenceLength];
	volatile uint16_t results[MaxSequenceLength];				// results are written to this buffer
	volatile uint16_t resultsByChannel[NumAdcChannels];			// must be large enough to handle PTAT and CTAT temperature sensor inputs
};

AdcClass::AdcClass(Adc * const p_device, IRQn irqn, NvicPriority irqPriority) noexcept
	: device(p_device), irqNumber(irqn),
	  numChannelsEnabled(0), numChannelsConverting(0), channelsEnabled(0),
	  taskToWake(nullptr), whenLastConversionStarted(0), state(State::noChannels)
{
	NVIC_DisableIRQ(irqn);
	NVIC_SetPriority(irqn, irqPriority);

	for (size_t i = 0; i < MaxSequenceLength; ++i)
	{
		callbackFunctions[i] = nullptr;
		callbackParams[i].u32 = 0;
	}
	for (volatile uint16_t& r : resultsByChannel)
	{
		r = 0;
	}
}

// Shut down the ADC, making it safe to terminate the AnalogIn task
void AdcClass::Exit() noexcept
{
	taskToWake = nullptr;
	device->INTENCLR.reg = 0x07;								// disable interrupts from the ADC
	NVIC_DisableIRQ(irqNumber);
}

// Try to enable this ADC on the specified channel returning true if successful
// Only single ended mode with gain x1 is supported
// There is no check to avoid adding the same channel twice. If you do that it will be converted twice.
bool AdcClass::EnableChannel(unsigned int chan, AnalogInCallbackFunction fn, CallbackParameter param, uint32_t p_ticksPerCall) noexcept
{
	if (numChannelsEnabled == MaxSequenceLength || chan >= NumAdcChannels)
	{
		return false;
	}

	return InternalEnableChannel(chan, fn, param, p_ticksPerCall);
}

bool AdcClass::SetCallback(unsigned int chan, AnalogInCallbackFunction fn, CallbackParameter param, uint32_t p_ticksPerCall) noexcept
{
	for (size_t i = 0; i < numChannelsEnabled; ++i)
	{
		if (GetChannel(i) == chan)
		{
			AtomicCriticalSectionLocker lock;

			callbackFunctions[i] = fn;
			callbackParams[i] = param;
			ticksPerCall[i] = p_ticksPerCall;
			ticksAtLastCall[i] = millis();
			return true;
		}
	}
	return false;
}

bool AdcClass::IsChannelEnabled(unsigned int chan) const noexcept
{
	return (channelsEnabled & (1ul << chan)) != 0;
}

bool AdcClass::EnableTemperatureSensor(unsigned int sensorNumber, AnalogInCallbackFunction fn, CallbackParameter param, uint32_t p_ticksPerCall) noexcept
{
	if (numChannelsEnabled == MaxSequenceLength || sensorNumber >= 2)
	{
		return false;
	}

	return InternalEnableChannel(sensorNumber + ADC_INPUTCTRL_MUXPOS_PTAT_Val, fn, param, p_ticksPerCall);
}

// Initialise or re-initialise the ADC. The ADC clock has already been enabled.
void AdcClass::ReInit() noexcept
{
	hri_adc_write_CTRLA_reg(device, ADC_CTRLA_SWRST);
	hri_adc_wait_for_sync(device, ADC_SYNCBUSY_SWRST);

	// From the SAME5x errata:
	// 2.1.4 DMA Sequencing
	//	ADC DMA Sequencing with prescaler>8 (ADC->CTRLA.bit.PRESCALER>2) does not produce the expected channel sequence.
	// Workaround
	//  Keep the prescaler setting to a maximum of 8, and use the GCLK Generator divider if more prescaling is needed.
	// 2.1.5 DMA Sequencing
	//  ADC DMA Sequencing with averaging enabled (AVGCTRL.SAMPLENUM>1) without the AVGCTRL bit set (DSEQCTRL.AVGCTRL=0) in the update sequence
	//  does not produce the expected channel sequence.
	// Workaround
	//  Add the AVGCTRL register in the register update list (DSEQCTRL.AVGCTRL=1) and set the desired value in this list.
	hri_adc_write_CTRLA_reg(device, ADC_CTRLA_PRESCALER_DIV8);			// GCLK1 is 60MHz, divided by 8 is 7.5MHz
	hri_adc_write_CTRLB_reg(device, CtrlB);
	hri_adc_write_REFCTRL_reg(device,  RefCtrl);
	hri_adc_write_EVCTRL_reg(device, 0);
	hri_adc_write_INPUTCTRL_reg(device, ADC_INPUTCTRL_MUXNEG_GND);
	hri_adc_write_AVGCTRL_reg(device, AvgCtrl);
	hri_adc_write_SAMPCTRL_reg(device, SampCtrl);						// this also extends the sample time to 4 ADC clocks
	hri_adc_write_WINLT_reg(device, 0);
	hri_adc_write_WINUT_reg(device, 0xFFFF);
	hri_adc_write_GAINCORR_reg(device, 1u << 11);
	hri_adc_write_OFFSETCORR_reg(device, 0);
	hri_adc_write_DSEQCTRL_reg(device, 0);
	hri_adc_write_DBGCTRL_reg(device, 0);

	// Load CALIB with NVM data calibration results
	do
	{
		uint32_t biasComp, biasRefbuf, biasR2R;
		if (device == ADC0)
		{
			biasComp = (*reinterpret_cast<const uint32_t*>(ADC0_FUSES_BIASCOMP_ADDR) & ADC0_FUSES_BIASCOMP_Msk) >> ADC0_FUSES_BIASCOMP_Pos;
			biasRefbuf = (*reinterpret_cast<const uint32_t*>(ADC0_FUSES_BIASREFBUF_ADDR) & ADC0_FUSES_BIASREFBUF_Msk) >> ADC0_FUSES_BIASREFBUF_Pos;
			biasR2R = (*reinterpret_cast<const uint32_t*>(ADC0_FUSES_BIASR2R_ADDR) & ADC0_FUSES_BIASR2R_Msk) >> ADC0_FUSES_BIASR2R_Pos;
		}
		else if (device == ADC1)
		{
			biasComp = (*reinterpret_cast<const uint32_t*>(ADC1_FUSES_BIASCOMP_ADDR) & ADC1_FUSES_BIASCOMP_Msk) >> ADC1_FUSES_BIASCOMP_Pos;
			biasRefbuf = (*reinterpret_cast<const uint32_t*>(ADC1_FUSES_BIASREFBUF_ADDR) & ADC1_FUSES_BIASREFBUF_Msk) >> ADC1_FUSES_BIASREFBUF_Pos;
			biasR2R = (*reinterpret_cast<const uint32_t*>(ADC1_FUSES_BIASR2R_ADDR) & ADC1_FUSES_BIASR2R_Msk) >> ADC1_FUSES_BIASR2R_Pos;
		}
		else
		{
			break;
		}
		hri_adc_write_CALIB_reg(device, ADC_CALIB_BIASCOMP(biasComp) | ADC_CALIB_BIASREFBUF(biasRefbuf) | ADC_CALIB_BIASR2R(biasR2R));
	} while (false);

	device->INTENCLR.reg = 0x07;										// disable all interrupts
	NVIC_ClearPendingIRQ(irqNumber);
	NVIC_EnableIRQ(irqNumber);

	hri_adc_set_CTRLA_ENABLE_bit(device);

	// Set the supply controller to on-demand mode so that we can get at both temperature sensors
	hri_supc_set_VREF_ONDEMAND_bit(SUPC);
	hri_supc_set_VREF_TSEN_bit(SUPC);
	hri_supc_clear_VREF_VREFOE_bit(SUPC);

	currentChannel = 0;
	state = State::starting;
}

bool AdcClass::InternalEnableChannel(unsigned int chan, AnalogInCallbackFunction fn, CallbackParameter param, uint32_t p_ticksPerCall) noexcept
{
	if (chan < NumAdcChannels)
	{
		TaskCriticalSectionLocker lock;

		// Set up the ADC
		const size_t newChannelNumber = numChannelsEnabled;
		callbackFunctions[newChannelNumber] = fn;
		callbackParams[newChannelNumber] = param;
		ticksPerCall[newChannelNumber] = p_ticksPerCall;
		ticksAtLastCall[newChannelNumber] = millis();

		// Set up the input registers
		inputRegisters[newChannelNumber].inputCtrl = ADC_INPUTCTRL_MUXNEG_GND | (uint16_t)chan;
		inputRegisters[newChannelNumber].avgCtrl = AvgCtrl;

		resultsByChannel[chan] = 0;
		channelsEnabled |= 1ul << chan;
		numChannelsEnabled = newChannelNumber + 1;

		if (newChannelNumber == 0)
		{
			// First channel is being enabled, so initialise the ADC
			ReInit();
		}

		return true;
	}

	return false;
}

// If no conversion is already in progress and there are channels to convert, start a conversion and return true; else return false
bool AdcClass::StartConversion() noexcept
{
	const size_t numEnabled = numChannelsEnabled;			// capture volatile variable to ensure we use a consistent value
	if (numEnabled == 0)
	{
		return false;
	}

	if (state == State::converting)
	{
		if (millis() - whenLastConversionStarted < AdcConversionTimeout)
		{
			return false;									// let the current conversion continue
		}

		++conversionTimeouts;
		ReInit();
	}

	numChannelsConverting = numEnabled;						// this is the number of channels we will convert this time
	taskToWake = TaskBase::GetCallerTaskHandle();

	state = State::converting;
	(void)device->RESULT.reg;								// make sure no result pending
	currentChannel = numEnabled - 1;						// start with the last channel because in the ISR it's quicker to compare with zero
	device->INPUTCTRL.reg = inputRegisters[currentChannel].inputCtrl;
	device->AVGCTRL.reg = inputRegisters[currentChannel].avgCtrl;
	while (device->SYNCBUSY.reg & (ADC_SYNCBUSY_INPUTCTRL | ADC_SYNCBUSY_AVGCTRL)) { }
	device->INTENSET.reg = ADC_INTENSET_RESRDY;
	device->SWTRIG.reg = ADC_SWTRIG_START;

	++conversionsStarted;
	whenLastConversionStarted = millis();
	return true;
}

void AdcClass::ExecuteCallbacks() noexcept
{
	TaskCriticalSectionLocker lock;
	const uint32_t now = millis();
	for (size_t i = 0; i < numChannelsConverting; ++i)
	{
		const uint16_t currentResult = results[i];
		resultsByChannel[GetChannel(i)] = currentResult;
		if (now - ticksAtLastCall[i] >= ticksPerCall[i])
		{
			ticksAtLastCall[i] = now;
			if (callbackFunctions[i] != nullptr)
			{
				callbackFunctions[i](callbackParams[i], currentResult);
			}
		}
	}
}

// Indirect callback from the DMA controller ISR
// This ISR takes 660ns to execute including blipping a port at the start and end
// To achieve this we had to un-inline TaskBase::GiveFromIsr()
void AdcClass::ResultReadyInterrupt() noexcept
{
#if 0	// for timing the ISR speed
	fastDigitalWriteHigh(PortDPin(10));
#endif
	const uint16_t result = device->RESULT.reg;;
	if (state == State::converting)
	{
		results[currentChannel] = result;
		if (currentChannel == 0)
		{
			state = State::ready;
			++conversionsCompleted;
			TaskBase::GiveFromISR(taskToWake);
		}
		else
		{
			--currentChannel;
			device->INPUTCTRL.reg = inputRegisters[currentChannel].inputCtrl;
			device->AVGCTRL.reg = inputRegisters[currentChannel].avgCtrl;
			while (device->SYNCBUSY.reg & (ADC_SYNCBUSY_INPUTCTRL | ADC_SYNCBUSY_AVGCTRL)) { }
			device->SWTRIG.reg = ADC_SWTRIG_START;
		}
	}
#if 0	// for timing the ISR speed
	fastDigitalWriteLow(PortDPin(10));
#endif
}

// Check whether the conversion was successful
bool AdcClass::ConversionDone() noexcept
{
	return state == State::ready;
}

// ADC instances
static AdcClass *adcs[2];

// ADC ISRs
void ADC0_1_Handler() noexcept
{
	adcs[0]->ResultReadyInterrupt();
}

void ADC1_1_Handler() noexcept
{
	adcs[1]->ResultReadyInterrupt();
}

// Main loop executed by the AIN task
void AnalogIn::TaskLoop(void *) noexcept
{
	// Loop taking readings and processing them
	for (;;)
	{
		// Loop through ADCs
		bool conversionStarted = false;
		for (AdcClass* adc : adcs)
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

		if (conversionStarted)
		{
			TaskBase::Take(100);
		}
		else
		{
			// No ADCs enabled yet, or all converting. This should only happens during startup, before we enable the voltage monitor(s).
			delay(2);							// don't delay too long here, we want the ADCs to start up quickly once channels are enabled
		}
	}
}

// Initialise the analog input subsystem. Call this just once.
void AnalogIn::Init(NvicPriority interruptPriority) noexcept
{
	// Enable ADC clocks
	hri_mclk_set_APBDMASK_ADC0_bit(MCLK);
	hri_gclk_write_PCHCTRL_reg(GCLK, ADC0_GCLK_ID, GCLK_PCHCTRL_GEN(AdcGclkNum) | GCLK_PCHCTRL_CHEN);
	hri_mclk_set_APBDMASK_ADC1_bit(MCLK);
	hri_gclk_write_PCHCTRL_reg(GCLK, ADC1_GCLK_ID, GCLK_PCHCTRL_GEN(AdcGclkNum) | GCLK_PCHCTRL_CHEN);

	// Create the device instances
	adcs[0] = new AdcClass(ADC0, ADC0_1_IRQn, interruptPriority);
	adcs[1] = new AdcClass(ADC1, ADC1_1_IRQn, interruptPriority);
}

// Shut down the analog system. making it safe to terminate the AnalogIn task
void AnalogIn::Exit() noexcept
{
	adcs[0]->Exit();
	adcs[1]->Exit();
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
	return (deviceNumber < ARRAY_SIZE(adcs)) ? adcs[deviceNumber]->ReadChannel(GetInputNumber(adcin)) : 0;
}

// Enable an on-chip MCU temperature sensor
// From the SAME5x-E5x errata document version K:
// 2.23.1 Temperature Sensor
// Both internal temperature sensors, TSENSP and TSENSC, are not supported and should not be used.
// Workaround: None
// Affected Silicon Revisions: A, D
bool AnalogIn::EnableTemperatureSensor(unsigned int sensorNumber, AnalogInCallbackFunction fn, CallbackParameter param, uint32_t ticksPerCall, unsigned int adcnum) noexcept
{
	if (adcnum < ARRAY_SIZE(adcs))
	{
		// Set the supply controller to on-demand mode so that we can get at both temperature sensors
		SUPC->VREF.reg |= (SUPC_VREF_ONDEMAND | SUPC_VREF_TSEN | SUPC_VREF_VREFOE);

		return adcs[adcnum]->EnableTemperatureSensor(sensorNumber, fn, param, ticksPerCall);
	}
	return false;
}

// Return debug information
void AnalogIn::GetDebugInfo(uint32_t &convsStarted, uint32_t &convsCompleted, uint32_t &convTimeouts, uint32_t& errs) noexcept
{
	convsStarted = conversionsStarted;
	convsCompleted = conversionsCompleted;
	convTimeouts = conversionTimeouts;
	errs = errors;
}

#endif

// End
