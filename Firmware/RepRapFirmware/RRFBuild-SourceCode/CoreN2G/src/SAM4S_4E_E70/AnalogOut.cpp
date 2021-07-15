/*
 Copyright (c) 2011 Arduino.  All right reserved.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 See the GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <AnalogOut.h>
#include <cmath>
#include <cstring>

#include <pmc/pmc.h>
#include <pwm/pwm.h>
#include <pio/pio.h>
#include <tc/tc.h>

// PWM channels are 16 bit. We can choose two PWM frequencies. The first one should be a sub-multiple of the peripheral clock.
#if SAM3XA
// Peripheral clock is 84MHz so we can do 14MHz = 84/6
static const uint32_t PwmFastClock = 14000000;			// fast PWM clock for Intel spec PWM fans that need 25kHz PWM, resolution is 1 part in 560 @ 240MHz
#else
// Peripheral clock is 120MHz or 150MHz, so we can do 15MHz in either case
static const uint32_t PwmFastClock = 15000000;			// fast PWM clock for Intel spec PWM fans that need 25kHz PWM, resolution is 1 part in 600 @ 120MHz
#endif

static const uint32_t PwmSlowClock = 100000;			// slow PWM clock to allow us to get slow speeds, minimum a little under 2Hz, servo resolution is 10us

// Initialise this module
extern void AnalogOut::Init()
{
	// Nothing to do yet
}

// Convert a float in 0..1 to unsigned integer in 0..N
static inline uint32_t ConvertRange(float f, uint32_t top) noexcept
pre(0.0 <= ulValue; ulValue <= 1.0)
post(result <= top)
{
	return lrintf(f * (float)top);
}

#if SAM3XA || SAME70
const unsigned int numPwmChannels = 8;
#elif SAM4E || SAM4S
const unsigned int numPwmChannels = 4;
#endif

static bool PWMEnabled = false;
static uint16_t PWMChanFreq[numPwmChannels] = {0};
static uint16_t PWMChanPeriod[numPwmChannels];

#ifdef PWM_DEBUG
//***Temporary for debugging
uint32_t maxPwmLoopCount = 0;
#endif

// AnalogWrite to a PWM pin
// Return true if successful, false if we need to fall back to digitalWrite
static bool AnalogWritePwm(Pin pin, const PinDescriptionBase * const pinDesc, float ulValue, PwmFrequency freq) noexcept
pre(0.0 <= ulValue; ulValue <= 1.0)
pre((pinDesc.ulPinAttribute & PIN_ATTR_PWM) != 0)
{
	const uint32_t chanIndex = GetChannelNumber(pinDesc->pwm);
	if (freq == 0)
	{
		PWMChanFreq[chanIndex] = freq;
		return false;
	}

	// Which PWM interface and channel within that interface do we need to work with?
#if SAME70
	Pwm * const PWMInterface = (chanIndex < 4) ? PWM0 : PWM1;
	const uint32_t chan = chanIndex & 3;							// SAME70 has two PWM controllers with 3 channels each
#else
	Pwm * const PWMInterface = PWM;
	const uint32_t chan = chanIndex;								// other supported processors have one PWM controller with 4 or 8 channels
#endif

	if (PWMChanFreq[chanIndex] != freq)
	{
		if (!PWMEnabled)
		{
			// PWM Startup code
#if SAME70
			pmc_enable_periph_clk(ID_PWM0);
			pmc_enable_periph_clk(ID_PWM1);
#else
			pmc_enable_periph_clk(ID_PWM);
#endif
			pwm_clock_t clockConfig;
			clockConfig.ul_clka = PwmSlowClock;
			clockConfig.ul_clkb = PwmFastClock;
			clockConfig.ul_mck = SystemPeripheralClock();
#if SAME70
			pwm_init(PWM0, &clockConfig);
			PWM0->PWM_SCM = 0;										// ensure no sync channels
			pwm_init(PWM1, &clockConfig);
			PWM1->PWM_SCM = 0;										// ensure no sync channels
#else
			pwm_init(PWM, &clockConfig);
			PWM->PWM_SCM = 0;										// ensure no sync channels
#endif
			PWMEnabled = true;
		}

		const bool useFastClock = (freq >= PwmFastClock/65535);
		const uint16_t period = (uint16_t)min<uint32_t>(((useFastClock) ? PwmFastClock : PwmSlowClock)/freq, 65535);
		const uint16_t duty = (uint16_t)ConvertRange(ulValue, period);

		PWMChanFreq[chanIndex] = freq;
		PWMChanPeriod[chanIndex] = (uint16_t)period;

		// Set up the PWM channel
		// We need to work around a bug in the SAM PWM channels. Enabling a channel is supposed to clear the counter, but it doesn't.
		// A further complication is that on the SAM3X, the update-period register doesn't appear to work.
		// So we need to make sure the counter is less than the new period before we change the period.
		for (unsigned int j = 0; j < 5; ++j)							// twice through should be enough, but just in case...
		{
			pwm_channel_disable(PWMInterface, chan);
#ifdef PWM_DEBUG
			if (j > maxPwmLoopCount)
			{
				maxPwmLoopCount = j;
			}
#endif
			uint32_t oldCurrentVal = PWMInterface->PWM_CH_NUM[chan].PWM_CCNT & 0xFFFF;
			if (oldCurrentVal < period || oldCurrentVal > 65536 - 10)	// if counter is already small enough or about to wrap round, OK
			{
				break;
			}
			oldCurrentVal += 2;											// note: +1 doesn't work here, has to be at least +2
			PWMInterface->PWM_CH_NUM[chan].PWM_CPRD = oldCurrentVal;	// change the period to be just greater than the counter
			PWMInterface->PWM_CH_NUM[chan].PWM_CMR = PWM_CMR_CPRE_CLKB;	// use the fast clock to avoid waiting too long
			pwm_channel_enable(PWMInterface, chan);
			for (unsigned int i = 0; i < 1000; ++i)
			{
				const uint32_t newCurrentVal = PWMInterface->PWM_CH_NUM[chan].PWM_CCNT & 0xFFFF;
				if (newCurrentVal < period || newCurrentVal > oldCurrentVal)
				{
					break;												// get out when we have wrapped round, or failed to
				}
			}
		}

		pwm_channel_t channelConfig;
		memset(&channelConfig, 0, sizeof(channelConfig));				// clear unused fields
		channelConfig.channel = chan;
		channelConfig.ul_prescaler = (useFastClock) ? PWM_CMR_CPRE_CLKB : PWM_CMR_CPRE_CLKA;
		channelConfig.ul_duty = duty;
		channelConfig.ul_period = period;
		channelConfig.b_pwmh_output_inverted = true;					// both outputs have same polarity

		pwm_channel_init(PWMInterface, &channelConfig);
		pwm_channel_enable(PWMInterface, chan);

		// Now setup the PWM output pin for PWM this channel - do this after configuring the PWM to avoid glitches
		SetPinFunction(pin, GetPeriNumber(pinDesc->pwm));
	}
	else
	{
		// We have to pass a pwm_channel_t struct to pwm_channel_update duty, but the only fields it reads are 'chan' and 'ul_period'.
		pwm_channel_t channelConfig;
		channelConfig.channel = chan;
		channelConfig.ul_period = (uint32_t)PWMChanPeriod[chanIndex];
		pwm_channel_update_duty(PWMInterface, &channelConfig, ConvertRange(ulValue, channelConfig.ul_period));
	}
	return true;
}

#if SAM4S
const unsigned int NumTcChannels = 6;
#elif SAM3XA || SAM4E
const unsigned int NumTcChannels = 9;
#elif SAME70
const unsigned int NumTcChannels = 12;
#endif

// Map from timer channel to TC channel number
static const uint8_t channelToChNo[NumTcChannels] =
{
	0, 1, 2,
	0, 1, 2,
#if SAM3XA || SAM4E || SAME70
	0, 1, 2,
#endif
#if SAME70
	0, 1, 2
#endif
};

// Map from timer channel to TC number
static Tc * const channelToTC[NumTcChannels] =
{
	TC0, TC0, TC0,
	TC1, TC1, TC1,
#if SAM3XA || SAM4E || SAME70
	TC2, TC2, TC2,
#endif
#if SAME70
	TC3, TC3, TC3
#endif
};

// Map from timer channel to TIO number
static const uint8_t channelToId[NumTcChannels] =
{
	ID_TC0, ID_TC1, ID_TC2,
	ID_TC3, ID_TC4, ID_TC5,
#if SAM3XA || SAM4E || SAME70
	ID_TC6, ID_TC7, ID_TC8,
#endif
#if SAME70
	ID_TC9, ID_TC10, ID_TC11
#endif
};

// Current frequency of each TC channel
static uint16_t TCChanFreq[NumTcChannels] = {0};

static inline void TC_SetCMR_ChannelA(Tc *tc, uint32_t chan, uint32_t v) noexcept
{
	tc->TC_CHANNEL[chan].TC_CMR = (tc->TC_CHANNEL[chan].TC_CMR & 0xFFF0FFFF) | v;
}

static inline void TC_SetCMR_ChannelB(Tc *tc, uint32_t chan, uint32_t v) noexcept
{
	tc->TC_CHANNEL[chan].TC_CMR = (tc->TC_CHANNEL[chan].TC_CMR & 0xF0FFFFFF) | v;
}

static inline void TC_WriteCCR(Tc *tc, uint32_t chan, uint32_t v) noexcept
{
	tc->TC_CHANNEL[chan].TC_CCR = v;
}

// AnalogWrite to a TC pin
// Return true if successful, false if we need to fall back to digitalWrite
// WARNING: this will screw up big time if you try to use both the A and B outputs of the same timer at different frequencies.
// The Duet boards use only A outputs, so this is OK.
static bool AnalogWriteTc(Pin pin, const PinDescriptionBase * const pinDesc, float ulValue, PwmFrequency freq) noexcept
pre(0.0 <= ulValue; ulValue <= 1.0)
pre((pinDesc.ulPinAttribute & PIN_ATTR_TIMER) != 0)
{
	const uint32_t chan = (uint32_t)GetDeviceNumber(pinDesc->tc);
	if (freq == 0)
	{
		TCChanFreq[chan] = freq;
		return false;
	}
	else
	{
		Tc* const chTC = channelToTC[chan];
		const uint32_t chNo = channelToChNo[chan];
		const bool doInit = (TCChanFreq[chan] != freq);

		if (doInit)
		{
			TCChanFreq[chan] = freq;

			// Enable the peripheral clock to this timer
			pmc_enable_periph_clk(channelToId[chan]);

			// Set up the timer mode and top count
#if SAM4S || SAME70
			// The timer/counters are only 16 bits wide on the SAM4S and SAME70 so we need to use a higher prescaler
			tc_init(chTC, chNo,
							TC_CMR_TCCLKS_TIMER_CLOCK4 |			// clock is MCLK/128 (SAM4S) or peripheral_clock/128 (SAME70)
							TC_CMR_WAVE |         					// Waveform mode
							TC_CMR_WAVSEL_UP_RC | 					// Counter running up and then down when equals to RC
							TC_CMR_EEVT_XC0 |     					// Set external events from XC0 (this allows TIOB to be an output)
							TC_CMR_ACPA_CLEAR | TC_CMR_ACPC_CLEAR |
							TC_CMR_BCPB_CLEAR | TC_CMR_BCPC_CLEAR |
							TC_CMR_ASWTRG_SET | TC_CMR_BSWTRG_SET);	// Software trigger will let us set the output high
			const uint32_t top = min<uint32_t>((SystemPeripheralClock()/128)/(uint32_t)freq, 65535);	// with 120MHz clock (SAM4S) this varies between 14 @ 65.535kHz and 65535 @ 14.3Hz
#else
			tc_init(chTC, chNo,
							TC_CMR_TCCLKS_TIMER_CLOCK2 |			// clock is MCLK/8 to save a little power and avoid overflow later on
							TC_CMR_WAVE |         					// Waveform mode
							TC_CMR_WAVSEL_UP_RC | 					// Counter running up and reset when equals to RC
							TC_CMR_EEVT_XC0 |     					// Set external events from XC0 (this allows TIOB to be an output)
							TC_CMR_ACPA_CLEAR | TC_CMR_ACPC_CLEAR |
							TC_CMR_BCPB_CLEAR | TC_CMR_BCPC_CLEAR |
							TC_CMR_ASWTRG_SET | TC_CMR_BSWTRG_SET);	// Software trigger will let us set the output high
			const uint32_t top = (SystemPeripheralClock()/8)/(uint32_t)freq;	// with 120MHz clock this varies between 228 @ 65.535kHz and 15 million @ 1Hz
#endif
			// The datasheet doesn't say directly how the period relates to the RC value, but from measurement it seems that we do not need to subtract one from top
			tc_write_rc(chTC, chNo, top);

			// When using TC channels to do PWM control of heaters with active low outputs on the Duet WiFi, if we don't take precautions
			// then we get a glitch straight after initialising the channel, because the compare output starts in the low state.
			// To avoid that, set the output high here if a high PWM was requested.
			if (ulValue >= 0.5)
			{
				TC_WriteCCR(chTC, chan, TC_CCR_SWTRG);
			}
		}

		const uint32_t threshold = ConvertRange(ulValue, tc_read_rc(chTC, chNo));
		if (threshold == 0)
		{
			if (((uint32_t)GetOutputNumber(pinDesc->tc) & 1) == 0)
			{
				tc_write_ra(chTC, chNo, 1);
				TC_SetCMR_ChannelA(chTC, chNo, TC_CMR_ACPA_CLEAR | TC_CMR_ACPC_CLEAR);
			}
			else
			{
				tc_write_rb(chTC, chNo, 1);
				TC_SetCMR_ChannelB(chTC, chNo, TC_CMR_BCPB_CLEAR | TC_CMR_BCPC_CLEAR);
			}
		}
		else
		{
			if (((uint32_t)GetOutputNumber(pinDesc->tc) & 1) == 0)
			{
				tc_write_ra(chTC, chNo, threshold);
				TC_SetCMR_ChannelA(chTC, chNo, TC_CMR_ACPA_CLEAR | TC_CMR_ACPC_SET);
			}
			else
			{
				tc_write_rb(chTC, chNo, threshold);
				TC_SetCMR_ChannelB(chTC, chNo, TC_CMR_BCPB_CLEAR | TC_CMR_BCPC_SET);
			}
		}

		if (doInit)
		{
			SetPinFunction(pin, GetPeriNumber(pinDesc->tc));
			tc_start(chTC, chNo);
		}
	}
	return true;
}

// Analog write to DAC, PWM, TC or plain output pin
// Setting the frequency of a TC or PWM pin to zero resets it so that the next call to AnalogOut with a non-zero frequency
// will re-initialise it. The pinMode function relies on this.
void AnalogOut::Write(Pin pin, float ulValue, PwmFrequency freq) noexcept
{
	const PinDescriptionBase * const pinDesc = AppGetPinDescription(pin);
	if (pinDesc == nullptr || std::isnan(ulValue))
	{
		return;
	}

	ulValue = constrain<float>(ulValue, 0.0, 1.0);

	if (pinDesc->pwm != PwmOutput::none)
	{
		if (AnalogWritePwm(pin, pinDesc, ulValue, freq))
		{
			return;
		}
	}
	else if (pinDesc->tc != TcOutput::none)
	{
		if (AnalogWriteTc(pin, pinDesc, ulValue, freq))
		{
			return;
		}
	}

	// Fall back to digital write
	pinMode(pin, (ulValue < 0.5) ? OUTPUT_LOW : OUTPUT_HIGH);
}

// End
