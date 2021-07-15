//Author sdavi

#include "SoftwarePWM.h"
#include "SoftwarePWMTimer.h"


SoftwarePWM::SoftwarePWM(Pin softPWMPin) noexcept:
        pwmRunning(false),
        pin(softPWMPin),
        gpioPort((LPC_GPIO_T*)(LPC_GPIO0_BASE + ((softPWMPin & 0xE0)))),
        gpioPortPinBitPosition( 1 << (softPWMPin & 0x1f) ),
        period(0),
        onTime(0),
        timerChan(-1)

{
    pinMode(pin, OUTPUT_LOW);
}

void SoftwarePWM::AttachTimer() noexcept
{
    if (timerChan < 0)
        timerChan = softwarePWMTimer.enable(this, onTime, period - onTime);
}

void SoftwarePWM::ReleaseTimer() noexcept
{
    if (timerChan >= 0)
        softwarePWMTimer.disable(timerChan);
    timerChan = -1;
}

void SoftwarePWM::Enable() noexcept
{
    pwmRunning = true;
    AttachTimer();
}

void SoftwarePWM::Disable() noexcept
{
    pwmRunning = false;
    pinMode(pin, OUTPUT_LOW);
    ReleaseTimer();
}

void SoftwarePWM::AnalogWrite(float ulValue, uint16_t freq, Pin pin) noexcept
{
    //Note: AnalogWrite gets called repeatedly by RRF for heaters
    
    const uint32_t newPeriod = (freq!=0)?(1000000/freq):0;
    const uint32_t newOnTime = CalculateDutyCycle(ulValue, newPeriod);

    //Common Frequnecies used in RRF:
    //Freq:   10Hz,     250Hz  and 500Hz
    //Period: 100000us, 4000us and 2000us
    //Typically 10Hz are used for Heat beds 250Hz is used for Hotends/fans and some fans may need up to 500Hz
    

    //if enforcing a minimum on/off time to prevent the same channel firing in rapid succession, we get:
    // 100us = Min Duty:   0.1%,  2.5%  and 5%
    // 50us  = Min Duty:   0.05%, 1.25% and 2.5%
    // 10us  = Min Duty:   0.01%, 0.25% and 0.5%
    constexpr uint16_t MinimumTime = 100; //microseconds

    if(onTime < MinimumTime){ onTime = 0; }
    if(onTime > (period-MinimumTime)){ onTime = period; }
    
    if(newOnTime != onTime || newPeriod != period)
    {
        //Frequency or duty has changed, requires update
        if (newPeriod != period)
            ReleaseTimer();            
        period = newPeriod;
        onTime = newOnTime;
        
        //check for 100% on or 100% off, no need for interrupts
        if(onTime == 0)
        {
            Disable();
            SetLow(); //Pin Low
        }
        else if(onTime == period)
        {
            ReleaseTimer();
            SetHigh(); //Pin High
            pwmRunning = true; //flag pwm "running" but interrupts are off
        }
        else
        {
            //Enable and use interrupts to generate the PWM signal
            Enable();
            softwarePWMTimer.adjustOnOffTime(timerChan, onTime, period - onTime);
        }
    }
    else
    {
        //PWM not changed
        
        if(pwmRunning == false)
        {
            // this pwm is not running, keep setting to zero as a precaution incase the same pin has accidently been used elsewhere
            SetLow(); //Pin Low
        }
    }
}

uint32_t SoftwarePWM::CalculateDutyCycle(float newValue, uint32_t newPeriod) noexcept
{
    uint32_t ot = (uint32_t) (newPeriod * newValue);
    if(ot > newPeriod) ot = newPeriod;
    return ot;
}
