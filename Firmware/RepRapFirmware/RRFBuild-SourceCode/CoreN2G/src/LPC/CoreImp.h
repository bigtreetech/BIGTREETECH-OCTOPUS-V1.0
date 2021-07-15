#ifndef CORE_IMP_H
#define CORE_IMP_H
#include <Core.h>
#ifdef __cplusplus
#include <CoreIO.h>
#endif
#include <General/SimpleMath.h>
#include "chip.h"
#include "stdutils.h"
#include "pwm_176x.h"
#include "HardwareSerial.h"

constexpr uint8_t NumADCChannels = 8;
constexpr uint8_t MaxNumberSoftwarePWMPins = 7;
constexpr uint16_t HardwarePWMFrequency = 50; //50Hz for Servos
// Pin Attributes to be OR-ed
constexpr uint8_t PIN_ATTR_NONE = 0;
constexpr uint8_t PIN_ATTR_COMBO = 1 << 0;
constexpr uint8_t PIN_ATTR_ANALOG = 1 << 1;
constexpr uint8_t PIN_ATTR_DIGITAL = 1 << 2;
constexpr uint8_t PIN_ATTR_PWM = 1 << 3;
constexpr uint8_t PIN_ATTR_TIMER = 1 << 4;
constexpr uint8_t PIN_ATTR_DAC = 1 << 5;

struct PinDescription
{
    uint8_t pPort;
    uint8_t ulPinAttribute;
    AnalogChannelNumber ulADCChannelNumber; // ADC or DAC channel number
    EPWMChannel ulPWMChannel;
};
extern const PinDescription g_APinDescription[NumTotalPins];
void ConfigurePin(const PinDescription& pinDesc) noexcept;

//void AnalogOut(Pin pin, float ulValue, uint16_t freq = 1000) noexcept;
bool IsPwmCapable(Pin pin) noexcept;
bool ConfigurePinForPWM(Pin pin, bool outputHigh) noexcept;
//void ReleasePWMPin(Pin pin) noexcept;


bool IsServoCapable(Pin pin) noexcept;
bool ConfigurePinForServo(Pin pin, bool outputHigh) noexcept;
void ReleaseServoPin(Pin pin) noexcept;
bool AnalogWriteServo(float ulValue, uint16_t freq, Pin pin) noexcept;

bool AnalogWriteSoftwarePWM(float ulValue, uint16_t freq, Pin pin) noexcept;
bool CanDoSoftwarePWM(Pin pin) noexcept;
bool ConfigurePinForSoftwarePWM(Pin pin) noexcept;
void ReleaseSoftwarePWMPin(Pin pin) noexcept;

extern Pin UsedHardwarePWMChannel[NumPwmChannels];
class SoftwarePWM; //fwd decl
extern SoftwarePWM* softwarePWMEntries[MaxNumberSoftwarePWMPins];
#endif