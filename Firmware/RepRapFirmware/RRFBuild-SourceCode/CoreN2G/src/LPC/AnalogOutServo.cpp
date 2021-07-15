//Author: sdavi/gloomyandy
#include "CoreImp.h"
#include "chip.h"
#include "AnalogOut.h"
extern "C" void debugPrintf(const char* fmt, ...) __attribute__ ((format (printf, 1, 2)));

template<class T, size_t N>
constexpr size_t size(T (&)[N]) { return N; }


static bool PWMEnabled = false;
Pin UsedHardwarePWMChannel[NumPwmChannels] = {NoPin, NoPin, NoPin, NoPin, NoPin, NoPin};

void PWM_Set( Pin pin, uint32_t dutyCycle )
{
    //find entry in array
    for(uint8_t i=0;i<size(PinMap_PWM); i++)
    {
        if(PinMap_PWM[i].pinNumber == pin)
        {
            GPIO_PinFunction(pin, PinMap_PWM[i].PinFunSel); //configure pin to PWM
            switch(PinMap_PWM[i].pwmChannelNumber)
            {
                case PWM1_1:
                    LPC_PWM1->MR1 = dutyCycle;
                    LPC_PWM1->LER|= PWM_LER1_EN;
                    LPC_PWM1->PCR|= PWM_PWMENA1;
                    break;
                case PWM1_2:
                    LPC_PWM1->MR2 = dutyCycle;
                    LPC_PWM1->LER|= PWM_LER2_EN;
                    LPC_PWM1->PCR|= PWM_PWMENA2;
                    break;
                case PWM1_3:
                    LPC_PWM1->MR3 = dutyCycle;
                    LPC_PWM1->LER|= PWM_LER3_EN;
                    LPC_PWM1->PCR|= PWM_PWMENA3;
                    break;
                case PWM1_4:
                    LPC_PWM1->MR4 = dutyCycle;
                    LPC_PWM1->LER|= PWM_LER4_EN;
                    LPC_PWM1->PCR|= PWM_PWMENA4;
                    break;
                case PWM1_5:
                    LPC_PWM1->MR5 = dutyCycle;
                    LPC_PWM1->LER|= PWM_LER5_EN;
                    LPC_PWM1->PCR|= PWM_PWMENA5;
                    break;
                case PWM1_6:
                    LPC_PWM1->MR6 = dutyCycle;
                    LPC_PWM1->LER|= PWM_LER6_EN;
                    LPC_PWM1->PCR|= PWM_PWMENA6;
                    break;
            }
        }
    }
}


void PWM_Clear( Pin pin)
{
    for(uint8_t i=0;i<size(PinMap_PWM); i++)
    {
        if(PinMap_PWM[i].pinNumber == pin)
        {
            //Disable the PWM Outout
            switch(PinMap_PWM[i].pwmChannelNumber)
            {
                case PWM1_1:
                    LPC_PWM1->PCR &= ~PWM_PWMENA1;
                    break;
                case PWM1_2:
                    LPC_PWM1->PCR &= ~PWM_PWMENA2;
                    break;
                case PWM1_3:
                    LPC_PWM1->PCR &= ~PWM_PWMENA3;
                    break;
                case PWM1_4:
                    LPC_PWM1->PCR &= ~PWM_PWMENA4;
                    break;
                case PWM1_5:
                    LPC_PWM1->PCR &= ~PWM_PWMENA5;
                    break;
                case PWM1_6:
                    LPC_PWM1->PCR &= ~PWM_PWMENA6;
                    break;
            }
        }
    }
}



// AnalogWrite to a PWM pin
// Return true if successful, false if we need to fall back to digitalWrite
bool AnalogWriteHWPWM(const PinDescription& pinDesc, float ulValue, uint16_t freq, Pin pin) noexcept
    pre(0.0 <= ulValue; ulValue <= 1.0)
    pre((pinDesc.ulPinAttribute & PIN_ATTR_PWM) != 0)
{

    //Is this pin configured for HW PWM ?
    if(pinDesc.ulPWMChannel == NOT_ON_PWM) return false;
    
    
    const uint8_t pwmChannel = (uint8_t) pinDesc.ulPWMChannel;
    if(UsedHardwarePWMChannel[pwmChannel] == NoPin) return false; //Pin PWM capable, but not configured as PWM
    
    if(freq != HardwarePWMFrequency) return false; //HW PWM not configured at the requested frequency

    
    if(!PWMEnabled)
    {
        //NOTE: Manual states LPC pwm pins all share the same period!
        //NOTE: pclk set to 1/4 in system_LPC17xx.c

        //Enable and Setup HW PWM
        Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_PWM1); //enable power and clocking
        
        LPC_PWM1->PR = 0; // no pre-scale
        LPC_PWM1->IR = 0;// Disable all interrupt flags for PWM
        LPC_PWM1->MCR = 1 << 1; // Single PWMMode -> reset TC on match 0

        LPC_PWM1->TCR = PWM_TCR_RESET; //set reset

        const unsigned int pwm_clock_mhz = SystemCoreClock / 4000000;
        uint32_t ticks = pwm_clock_mhz * (1000000/HardwarePWMFrequency);
        LPC_PWM1->MR0 = ticks; //Set the period (for ALL channels)
        LPC_PWM1->LER|= PWM_LER0_EN;
        
        // enable counter and pwm, clear reset
        LPC_PWM1->TCR = PWM_TCR_CNT_EN | PWM_TCR_PWM_EN;

        PWMEnabled = true;
    }

    uint32_t v = (uint32_t)((float)(LPC_PWM1->MR0) * ulValue); //calculate duty cycle
    if (v == LPC_PWM1->MR0) v++; //ensure not equal to MR0

    PWM_Set(pin, v); //set the duty cycle for the pin

    return true;
}

bool ReleaseHWPWMPin(Pin pin) noexcept
{
    for(uint8_t i=0; i<NumPwmChannels; i++)
    {
        if(UsedHardwarePWMChannel[i] == pin)
        {
            //stop PWM
            PWM_Clear(pin);
            UsedHardwarePWMChannel[i] = NoPin;
            return true;
        }
    }
    return false;
}

bool CanDoHWPWM(Pin pin) noexcept
{
    for(uint8_t i=0; i<size(PinMap_PWM); i++)
    {
        if(PinMap_PWM[i].pinNumber == pin)
        {
            //some PWM pins share the same pwm channel, so check another pin on same channel is not in use
            if(UsedHardwarePWMChannel[PinMap_PWM[i].pwmChannelNumber] == NoPin  //channel unused
               || UsedHardwarePWMChannel[PinMap_PWM[i].pwmChannelNumber])       //or this pin is already configured as PWM
            {
                return true;
            }
        }
    }
    return false;
}


bool ConfigurePinForHWPWM(Pin pin, bool outputHigh) noexcept
{
    if(pin == NoPin || pin > NumTotalPins) return false;

    //Check for HW Pin
    for(uint8_t i=0; i<size(PinMap_PWM); i++)
    {
        if(PinMap_PWM[i].pinNumber == pin)
        {
            if(UsedHardwarePWMChannel[PinMap_PWM[i].pwmChannelNumber] == pin)
            {
                return true; //pin already configured
            }
            //some PWM pins share the same pwm channel, so check another pin on same channel is not in use
            if(UsedHardwarePWMChannel[PinMap_PWM[i].pwmChannelNumber] == NoPin)
            {
                UsedHardwarePWMChannel[PinMap_PWM[i].pwmChannelNumber] = pin; //Pin will use HW PWM
                return true;
            }
        }
    }
    return false; //Pin unable to do HW PWM
}


bool IsServoCapable(Pin pin)
{
    const uint8_t port = (pin >> 5);
    if(pin > NumTotalPins || port > 4) return false;
    
    //First see if the pin can use the HWPWM
    if(HardwarePWMFrequency == 50 && CanDoHWPWM(pin)) return true; //HWPWM configured at servo freq and is PWM capable
    // can we use software PWM?
    return IsPwmCapable(pin);
}

void ReleaseServoPin(Pin pin)
{    
    //First check if pin was running on HWPWM
    if(ReleaseHWPWMPin(pin)) return; //Servo was running on HWPWM and was released
    // Must be software PWM
    AnalogOut::ReleasePWMPin(pin);
}


bool ConfigurePinForServo(Pin pin, bool outputHigh)
{
    const uint8_t port = (pin >> 5);
    
    if (pin == NoPin || pin > NumTotalPins || port > 4) return false;
    
    
    //First try HW PWM for servo
    if(ConfigurePinForHWPWM(pin, outputHigh))
    {
        return true; //Pin was configured to use HWPWM
    }
    return ConfigurePinForPWM(pin, outputHigh);
}

bool AnalogWriteServo(float ulValue, uint16_t freq, Pin pin)
pre(0.0 <= ulValue; ulValue <= 1.0)
{

    //Is the pin configured as HW PWM
    const PinDescription& pinDesc = g_APinDescription[pin];
    const uint32_t attr = pinDesc.ulPinAttribute;
    if ((attr & PIN_ATTR_PWM) != 0)
    {
        if (AnalogWriteHWPWM(pinDesc, ulValue, freq, pin))
        {
            return true;
        }
    }
  
    return AnalogWriteSoftwarePWM(ulValue, freq, pin);
}
