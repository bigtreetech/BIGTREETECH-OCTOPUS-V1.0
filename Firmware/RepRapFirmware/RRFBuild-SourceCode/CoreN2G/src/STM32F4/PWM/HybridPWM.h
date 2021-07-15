/*
 * Povide PWM based output using either Hardware or Software PWM.
 * GA 14/8/2020
 */
#ifndef SRC_HYBRIDPWM_H_
#define SRC_HYBRIDPWM_H_
#include "Core.h"
#include "General/StringRef.h"
#include "HardwareTimer.h"
constexpr uint32_t MaxPWMChannels = 16;

class HybridPWMPin;
class HybridPWMBase
{
    public:
        HybridPWMBase() noexcept;
        virtual void free() noexcept = 0;
        virtual void setValue(float val) noexcept = 0;
        virtual void appendStatus(const StringRef& reply) noexcept = 0;
        static HybridPWMBase *allocate(HybridPWMPin *p, Pin pin, uint32_t freq, float value) noexcept;

    protected:
        HybridPWMPin *pwmPin;
};

class HybridPWMPin
{
    public:
        HybridPWMPin() noexcept;
        static HybridPWMPin *allocate(Pin pin, float value) noexcept;
        static HybridPWMPin *find(Pin pin) noexcept;
        void free() noexcept;
        void set(float value, uint32_t freq) noexcept;
        void appendStatus(const StringRef& reply) noexcept;

        Pin pin;
        float value;
        uint32_t freq;

    private:
        HybridPWMBase *pwm;
};

class HardwarePWM : HybridPWMBase
{
    public:
        HardwarePWM() noexcept;
        virtual void free() noexcept;
        virtual void setValue(float val) noexcept;
        virtual void appendStatus(const StringRef& reply) noexcept;
        static HybridPWMBase *allocate(Pin pin, uint32_t freq, float value) noexcept;
    private:
        HardwareTimer *timer;
        uint32_t channel;
};

class SoftwarePWM : HybridPWMBase
{
    public:
        SoftwarePWM() noexcept;
        virtual void free() noexcept;
        virtual void setValue(float val) noexcept;
        virtual void appendStatus(const StringRef& reply) noexcept;
        static HybridPWMBase *allocate(Pin pin, uint32_t freq, float value) noexcept;
    private:
        void setValue(Pin pin, float value) noexcept;
        int32_t channel;
        uint32_t period;
};

extern HybridPWMPin PWMPins[MaxPWMChannels];
#endif