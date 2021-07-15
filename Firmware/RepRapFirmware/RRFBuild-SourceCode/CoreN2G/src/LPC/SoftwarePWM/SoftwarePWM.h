//Author: sdavi

#ifndef SOFTWAREPWM_H
#define SOFTWAREPWM_H

#include "Core.h"
#include "SoftwarePWMTimer.h"

class SoftwarePWM
{
public:
    SoftwarePWM(Pin softPWMPin) noexcept;
    
    void Enable() noexcept;
    void Disable() noexcept;
    void AnalogWrite(float ulValue, uint16_t freq, Pin pin) noexcept;

    Pin GetPin() const noexcept { return pin; }
    uint16_t GetFrequency() const noexcept { return (period!=0)?(1000000/period):0; }

    bool IsRunning() noexcept { return pwmRunning; }
    
    void SetLow() noexcept;
    void SetHigh() noexcept;

private:

    volatile bool pwmRunning;
    const Pin pin;
    LPC_GPIO_T * const gpioPort;
    const uint32_t gpioPortPinBitPosition;
    
    volatile uint32_t period;
    volatile uint32_t onTime;
    int timerChan;

    uint32_t CalculateDutyCycle(float newValue, uint32_t newPeriod) noexcept;
    void AttachTimer() noexcept;
    void ReleaseTimer() noexcept;
    
};


//functions called by timer interrupt
inline void SoftwarePWM::SetLow() noexcept
{
    gpioPort->CLR = gpioPortPinBitPosition; //Pin Low
}

inline void SoftwarePWM::SetHigh() noexcept
{
    gpioPort->SET = gpioPortPinBitPosition; //Pin high
}


#endif
