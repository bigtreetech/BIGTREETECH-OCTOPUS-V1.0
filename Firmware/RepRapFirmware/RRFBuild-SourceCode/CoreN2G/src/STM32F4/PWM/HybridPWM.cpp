/*
 * Povide PWM based output using either Hardware or Software PWM.
 * GA 14/8/2020
 */

#include "HybridPWM.h"
extern "C" void debugPrintf(const char* fmt, ...) __attribute__ ((format (printf, 1, 2)));
HybridPWMPin PWMPins[MaxPWMChannels];

HybridPWMPin::HybridPWMPin() noexcept : pin(NoPin), value(-1.0f), freq(0), pwm(nullptr)
{

}

HybridPWMPin* HybridPWMPin::find(Pin pin) noexcept
{
    for(uint32_t i = 0; i < MaxPWMChannels; i++)
        if (PWMPins[i].pin == pin)
            return &PWMPins[i];
    return nullptr;
}


HybridPWMPin* HybridPWMPin::allocate(Pin pin, float value) noexcept
{
    // find a free channel and allocate it

    if (find(pin))
    {
        debugPrintf("Pin is already allocated as pwm %x\n", static_cast<int>(pin));
        return nullptr;
    }
    HybridPWMPin *ret = find(NoPin);
    if (ret == nullptr)
    {
        debugPrintf("No PWM channels available for %x\n", static_cast<int>(pin));
        return nullptr;
    }
    ret->pin = pin;
    ret->value = value;
    ret->pwm = nullptr;
    ret->freq = 0;
    // set initial state
    pinMode(pin, (value < 0.5) ? OUTPUT_LOW : OUTPUT_HIGH);
    // grab the hardware if we can
    //ret->pwm = HybridPWMBase::allocate(ret, pin, 0, value);
    return ret;
}

void HybridPWMPin::free() noexcept
{
    pinMode(pin, OUTPUT_LOW);
    if (pwm) pwm->free();
    pin = NoPin;
    freq = 0;
    value = -1.0f;
    pwm = nullptr;
}

void HybridPWMPin::set(float value, uint32_t freq) noexcept
{
    if (this->freq != freq)
    {
        if (pwm) pwm->free();
        if (freq != 0)
        {
            pwm = HybridPWMBase::allocate(this, pin, freq, value);
            this->value = value;
        }
        else
        {
            pwm = nullptr;
            this->value = -1.0f;
        }
        this->freq = freq;
    }
    if (this->value != value)
    {
        if (pwm) 
            pwm->setValue(value);
        else
            pinMode(pin, (value < 0.5) ? OUTPUT_LOW : OUTPUT_HIGH);
        this->value = value;
    }
}

void HybridPWMPin::appendStatus(const StringRef& reply) noexcept
{
    if (pin == NoPin) return;
    reply.catf(" Pin %c.%d freq %d value %f", (pin >> 4) + 'A', static_cast<int>(pin) & 0xf, static_cast<int>(freq), (double)value);
    if (pwm) pwm->appendStatus(reply);
}

HybridPWMBase::HybridPWMBase() noexcept : pwmPin(nullptr)
{
}


HybridPWMBase *HybridPWMBase::allocate(HybridPWMPin *p, Pin pin, uint32_t freq, float value) noexcept
{
    HybridPWMBase *ret = HardwarePWM::allocate(pin, freq, value);
    if (!ret)
        ret = SoftwarePWM::allocate(pin, freq, value);
    if (ret)
        ret->pwmPin = p;
    return ret;
}
