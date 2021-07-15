/**
 * @file CoreIO.h
 * @brief Header file declaring types, functions etc. usable from both C and C++
 *
 * This file contains basic CPU and I/O pin support for the SAME5x (also works with SAMD5x) and SAMC21
 * Use it where we can't include the full CoreIO.h file, for example in C source files
 */

/*
 *  Created on: 28 May 2020
 *      Author: David
 */

#ifndef SRC_HARDWARE_SAME5X_COREIO_H_
#define SRC_HARDWARE_SAME5X_COREIO_H_

#include "Core.h"

#include <General/SimpleMath.h>

// Exported memory control variables. These are defined in file syscalls.h which must be included by exactly one client file.
extern char *heapTop;
extern const char *heapLimit;
extern const char *sysStackLimit;

// Define NumTotalPins as the pin number at and beyond which it is not safe to access the corresponding port registers on this processor family.
// This may be greater than the number of I/O pins actually on the particular device we are running on.
#if SAME5x
constexpr unsigned int NumTotalPins = (3 * 32) + 22;	// SAME54P20A goes up to PD21
#elif SAMC21
constexpr unsigned int NumTotalPins = 2 * 32;			// SAMC21J goes up to PB31. We don't support the SAMC21N.
#elif SAM4E
constexpr unsigned int NumTotalPins = (4 * 32) + 6;		// SAM4E8E goes up to PE5
#elif SAM4S
constexpr unsigned int NumTotalPins = 3 * 32;			// SAM4S8C goes up to PC31
#elif SAME70
constexpr unsigned int NumTotalPins = (4 * 32) + 6;		// SAME70 goes up to PE5
#elif STM32F4 || LPC17xx
constexpr int NumTotalPins = P_END;
#else
# error Unsupported processor
#endif

#if STM32F4
inline uint32_t GpioPortNumber(Pin p) { return STM_PORT(p);}
inline constexpr uint32_t GpioPinNumber(Pin p) { return STM_PIN(p); }
inline constexpr uint32_t GpioMask(Pin p) { return (uint32_t)STM_GPIO_PIN(p); }
#elif LPC17xx
inline uint32_t GpioPortNumber(Pin p) { return p >> 5;}
inline constexpr uint32_t GpioPinNumber(Pin p) { return p & 0x1f; }
inline constexpr uint32_t GpioMask(Pin p) { return (uint32_t)1 << GpioPinNumber(p); }
#else
inline uint32_t GpioPortNumber(Pin p) { return p >> 5; }
inline constexpr uint32_t GpioPinNumber(Pin p) { return p & 0x1F; }
inline constexpr uint32_t GpioMask(Pin p) { return (uint32_t)1 << GpioPinNumber(p); }
#endif

#if SAME70 || SAM4E || SAM4S
inline Pio *GpioPort(Pin p) { return (Pio*)((uint32_t)PIOA + GpioPortNumber(p) * 0x200); }
#endif

#if !STM32F4 && !LPC17xx
/**
 * @brief Return the global pin number for a Port A pin
 *
 * @param n The bit number of the pin on Port A
 * @return The global pin number
 */
inline constexpr Pin PortAPin(unsigned int n) noexcept { return n; }

/**
 * @brief Return the global pin number for a Port B pin
 *
 * @param n The bit number of the pin on Port B
 * @return The global pin number
 */
inline constexpr Pin PortBPin(unsigned int n) noexcept { return 32+n; }

#if SAME5x || SAM4E || SAM4S || SAME70

/**
 * @brief Return the global pin number for a Port C pin
 *
 * @param n The bit number of the pin on Port C
 * @return The global pin number
 */
inline constexpr Pin PortCPin(unsigned int n) noexcept { return 64+n; }

#endif

#if SAME5x || SAM4E || SAME70

/**
 * @brief Return the global pin number for a Port D pin
 *
 * @param n The bit number of the pin on Port D
 * @return The global pin number
 */
inline constexpr Pin PortDPin(unsigned int n) noexcept { return 96+n; }

#endif

#if SAM4E || SAME70

/**
 * @brief Return the global pin number for a Port E pin
 *
 * @param n The bit number of the pin on Port E
 * @return The global pin number
 */
inline constexpr Pin PortEPin(unsigned int n) noexcept { return 128+n; }

#endif

/**
 * @brief Pin function numbers for calls to SetPinFunction
 *
 */
enum class GpioPinFunction : uint8_t
{
	A = 0, B, C, D,
#if SAME5x || SAMC21
	E, F, G, H, I, J, K, L, M, N
#endif
};

/**
 * @brief Set the function of an I/O pin
 *
 * @param p The pin number
 * @param f The required pin function
 */
void SetPinFunction(Pin p, GpioPinFunction f) noexcept;

/**
 * @brief Set a pin back to ordinary digital I/O
 *
 * @param p The pin number
 */
void ClearPinFunction(Pin p) noexcept;
#endif
// Enable or disable the pullup[ resistor
void SetPullup(Pin p, bool on) noexcept;

// Enable the pullup resistor
void EnablePullup(Pin p) noexcept;

// Disable the pullup resistor
void DisablePullup(Pin p) noexcept;

// Set the mode of a pin with optional debouncing
void SetPinMode(Pin pin, enum PinMode mode, uint32_t debounceCutoff) noexcept;

#if SAME5x || SAMC21

// GCLK management

/**
 * @brief Possible sources for a GCLK
 *
 */
enum class GclkSource : uint8_t
{
#if SAME5x
	xosc0 = 0,
	xosc1,
	gclkIn,
	gclk1,
	oscUlp32k,
	xosc32k,
	dfll,
	dpll0,
	dpll1
#elif SAMC21
	xosc = 0, /**< xosc */
	gclkIn,   /**< gclkIn */
	gclk1,    /**< gclk1 */
	oscUlp32k,/**< oscUlp32k */
	osc32k,   /**< osc32k */
	xosc32k,  /**< xosc32k */
	osc48m,   /**< osc48m */
	dpll      /**< dpll */
#else
# error Unsupported processor
#endif
};

/**
 * @brief Configure and enable a GCLK
 *
 * @param index The GCLK number
 * @param source The source oscillator
 * @param divisor The division factor
 * @param enableOutput Whether we want to enable output to a pin
 */
void ConfigureGclk(unsigned int index, GclkSource source, uint16_t divisor, bool enableOutput = false) noexcept;

#endif

// Optimised version of memcpy for use when the source and destination are known to be 32-bit aligned and a whole number of 32-bit words is to be copied
void memcpyu32(uint32_t *dst, const uint32_t *src, size_t numWords) noexcept;

// memcpy for int32_t arrays
inline void memcpyi32(int32_t *dst, const int32_t *src, size_t numWords) noexcept
{
	static_assert(sizeof(int32_t) == sizeof(uint32_t));
	static_assert(alignof(int32_t) == alignof(uint32_t));
	memcpyu32(reinterpret_cast<uint32_t*>(dst), reinterpret_cast<const uint32_t*>(src), numWords);
}

// memcpy for float arrays
inline void memcpyf(float *dst, const float *src, size_t numFloats) noexcept
{
	static_assert(sizeof(float) == sizeof(uint32_t));
	static_assert(alignof(float) == alignof(uint32_t));
	memcpyu32(reinterpret_cast<uint32_t*>(dst), reinterpret_cast<const uint32_t*>(src), numFloats);
}


// Atomic section locker, alternative to InterruptCriticalSectionLocker (is safe to call from within an ISR, and may be faster)
/**
 * @brief This class is an alternative to InterruptCriticalSectionLocker. It is safe to call from within an ISR, and may be faster.
 *
 */
class AtomicCriticalSectionLocker
{
public:
	AtomicCriticalSectionLocker() : flags(IrqSave())
	{
	}

	~AtomicCriticalSectionLocker()
	{
		IrqRestore(flags);
	}

private:
	irqflags_t flags;
};

#if SAME5x || SAM4E || SAM4S || SAME70 || STM32F4 || LPC17xx		// SAMC21 doesn't support these

// Functions to change the base priority, to shut out interrupts up to a priority level

// Get the base priority and shut out interrupts lower than or equal to a specified priority
inline uint32_t ChangeBasePriority(uint32_t prio)
{
	const uint32_t oldPrio = __get_BASEPRI();
	__set_BASEPRI_MAX(prio << (8 - __NVIC_PRIO_BITS));
	return oldPrio;
}

// Restore the base priority following a call to ChangeBasePriority
inline void RestoreBasePriority(uint32_t prio)
{
	__set_BASEPRI(prio);
}

// Set the base priority when we are not interested in the existing value i.e. definitely in non-interrupt code
inline void SetBasePriority(uint32_t prio)
{
	__set_BASEPRI(prio << (8 - __NVIC_PRIO_BITS));
}

#endif

/**
 * @brief Type used as the parameter to a standard callback function
 *
 */
union CallbackParameter
{
	void *vp;
	uint32_t u32;
	int32_t i32;

	CallbackParameter(void *pp) noexcept : vp(pp) { }
	CallbackParameter(uint32_t pp) noexcept : u32(pp) { }
	CallbackParameter(unsigned int p) noexcept { u32 = p; }
	CallbackParameter(int32_t pp) noexcept : i32(pp) { }
	CallbackParameter(int p) noexcept { i32 = p; }
	CallbackParameter() noexcept : u32(0) { }
};

/**
 * @brief Standard callback function type
 *
 * @param The parameter to the callback function
 */
typedef void (*StandardCallbackFunction)(CallbackParameter) noexcept;

/**
 * @brief Initialise the watchdog
 *
 */
void WatchdogInit() noexcept;

/**
 * @brief Kick the watchdog. This should be called from within the tick ISR.
 *
 */
void WatchdogReset() noexcept;

#if STM32F4
void WatchdogDisable() noexcept;
#endif


#if SAM4E || SAME70

/**
 * @brief Kick the secondary watchdog. This should be called from within the tick ISR.
 *
 */
void WatchdogResetSecondary() noexcept;

#endif

/**
 * @brief Timekeeping function. Call this from within the tick ISR.
 *
 */
void CoreSysTick() noexcept;

/**
 * @brief Call this from the application to initialise the DMA controller, interrupt system etc.
 *
 */
void CoreInit() noexcept;

// Random numbers

/**
 * @brief Return a random or pseudo-random number
 *
 * @param howbig Upper limit
 * @return The number, in the range 0 to (howbig - 1)
 */
static inline int32_t random(uint32_t howbig) noexcept
{
	return (howbig == 0) ? 0 : random32() % howbig;
}

/**
 * @brief  Return a random or pseudo-random number
 *
 * @param howsmall Lower limit
 * @param howbig Upper limit
 * @return The number, in the range howsmall to (howbig - 1)
 */
static inline uint32_t random(uint32_t howsmall, uint32_t howbig) noexcept
{
	return random(howbig - howsmall) + howsmall;
}

#if STM32F4
// Set a pin high with no error checking
#ifdef __cplusplus
[[gnu::always_inline, gnu::optimize("O3")]] static inline void fastDigitalWriteHigh(const Pin pin) noexcept
#else
static inline void fastDigitalWriteHigh(const Pin pin) noexcept
#endif
{
	WRITE_REG(GPIOPort[STM_PORT(pin)]->BSRR, STM_GPIO_PIN(pin));
}

// Set a pin low with no error checking
#ifdef __cplusplus
[[gnu::always_inline, gnu::optimize("O3")]] static inline void fastDigitalWriteLow(const Pin pin) noexcept
#else
static inline void fastDigitalWriteLow(const Pin pin) noexcept
#endif
{
	WRITE_REG(GPIOPort[STM_PORT(pin)]->BSRR, STM_GPIO_PIN(pin) << 16);
}

// Read a pin with no error checking
#ifdef __cplusplus
[[gnu::always_inline, gnu::optimize("O3")]] static inline int fastDigitalRead(const Pin pin) noexcept
#else
static inline bool fastDigitalRead(const Pin pin) noexcept
#endif
{
	return READ_BIT(GPIOPort[STM_PORT(pin)]->IDR, STM_GPIO_PIN(pin)) != 0;
}
#elif LPC17xx
// Set a pin high with no error checking
static inline void fastDigitalWriteHigh(const Pin pin) noexcept
{
    LPC_GPIO_T *LPC_GPIO_PORT = (LPC_GPIO_T*)(LPC_GPIO0_BASE + (pin & ~0x1f));
    LPC_GPIO_PORT->SET = 1 << (pin & 0x1f); 
}

// Set a pin low with no error checking
static inline void fastDigitalWriteLow(const Pin pin) noexcept
{
    LPC_GPIO_T *LPC_GPIO_PORT = (LPC_GPIO_T*)(LPC_GPIO0_BASE + (pin & ~0x1f));
    LPC_GPIO_PORT->CLR = 1 << (pin & 0x1f);    
}

static inline bool fastDigitalRead(const Pin pin) noexcept
{
    LPC_GPIO_T * LPC_GPIO_PORT = (LPC_GPIO_T*)(LPC_GPIO0_BASE + ((pin) & ~0x1f));    
    return (LPC_GPIO_PORT->PIN & (1 << (pin & 0x1f))) != 0;
}
#else
/**
 * @brief Set a pin high with no error checking
 *
 * @param pin The pin to set high
 */
inline void fastDigitalWriteHigh(uint32_t pin) noexcept
{
#if SAME5x || SAMC21
	PORT->Group[GpioPortNumber(pin)].OUTSET.reg = GpioMask(pin);
#elif SAME70 || SAM4E || SAM4S
	GpioPort(pin)->PIO_SODR = GpioMask(pin);
#else
# error Unsupported processor
#endif
}

/**
 * @brief Set a pin low with no error checking
 *
 * @param pin The pin to set low
 */
inline void fastDigitalWriteLow(uint32_t pin) noexcept
{
#if SAME5x || SAMC21
	PORT->Group[GpioPortNumber(pin)].OUTCLR.reg = GpioMask(pin);
#elif SAME70 || SAM4E || SAM4S
	GpioPort(pin)->PIO_CODR = GpioMask(pin);
#else
# error Unsupported processor
#endif
}

/**
 * @brief Read a pin with no error checking
 *
 * @param pin The pin to read
 */
inline bool fastDigitalRead(uint32_t pin) noexcept
{
#if SAME5x || SAMC21
	return PORT->Group[GpioPortNumber(pin)].IN.reg & GpioMask(pin);
#elif SAME70 || SAM4E || SAM4S
	return GpioPort(pin)->PIO_PDSR & GpioMask(pin);
#else
# error Unsupported processor
#endif
}
#endif

/**
 * @brief Reset the microcontroller
 *
 */
[[noreturn]] void Reset() noexcept;

#if !STM32F4 && !LPC17xx
/**
 * @brief TC output identifiers used in pin tables
 * These encode the TC number, the output number from that TC, and the peripheral number
 */
enum class TcOutput : uint8_t
{
#if SAME5x || SAMC21
	// TC devices, on peripheral E for both SAME5x and SAMC21. Bottom bit is the output number, remaining bits are the TC number.
	tc0_0 = 0, tc0_1,
	tc1_0, tc1_1,
	tc2_0, tc2_1,
	tc3_0, tc3_1,
	tc4_0, tc4_1,
# if SAME5x
	tc5_0, tc5_1,
	tc6_0, tc6_1,
	tc7_0, tc7_1,
# endif
#elif SAME70 || SAM4E || SAM4S
	// TIO devices. Bottom bit is the output number, next 4 bits are the TIO number, bits 5 and 6 are the peripheral number
	tioa0 = 0x20 + (0u << 1), tiob0, tioa1, tiob1, tioa2, tiob2, tioa3, tiob3, tioa4, tiob4,	// TIO 0-10 are on peripheral B
	tioa5, tiob5,
# if SAME70 || SAM4E
	tioa6, tiob6, tioa7, tiob7, tioa8, tiob8,
# endif
# if SAME70
	tioa9, tiob9, tioa10, tiob10,
	tioa11 = 0x40 + (11u << 1), tiob11,															// TIO11 is on peripheral C
# endif
#endif

	none = 0xFF,
};

/**
 * @brief Extract the TC number
 *
 * @param tc The TcOutput value
 * @return The TC number of tc
 */
static inline constexpr unsigned int GetDeviceNumber(TcOutput tc) noexcept
{
#if SAME5x || SAMC21
	return (uint8_t)tc >> 1;
#elif SAME70 || SAM4E || SAM4S
	return ((uint8_t)tc >> 1) & 0x0F;
#endif
}

/**
 * @brief Extract the output number
 *
 * @param tc The TcOutput value
 * @return The output number of tc
 */
static inline constexpr unsigned int GetOutputNumber(TcOutput tc) noexcept
{
	return (uint8_t)tc & 1;
}

/**
 * @brief Get the peripheral function that a TC output is on
 *
 * @param tc the TC output
 * @return The peripheral function identifier
 */
static inline constexpr GpioPinFunction GetPeriNumber(TcOutput tc) noexcept
{
#if SAME5x || SAMC21
	return GpioPinFunction::E;		// all TCs are on peripheral E for both the SAME5x and the SAMC21
#elif SAME70 || SAM4E || SAM4S
	return (GpioPinFunction)((uint8_t)tc >> 5);
#else
# error Unsupported processor
#endif
}

/**
 * @brief Initialise a TC clock
 *
 * @param tcNumber The TC number that needs a clock
 * @param gclkNum The GCLK number to use
 */
void EnableTcClock(unsigned int tcNumber, unsigned int gclkNum) noexcept;

#if SAME5x || SAMC21

/**
 * @brief TCC output identifiers used in pin tables
 * These encode the TCC number, the output number from that TCC, and the peripheral number that the output is on
 */
enum class TccOutput : uint8_t
{
#if SAME5x
	// TCC devices on peripheral F
	tcc0_0F = 0x00, tcc0_1F, tcc0_2F, tcc0_3F, tcc0_4F, tcc0_5F,
	tcc1_0F = 0x08, tcc1_1F, tcc1_2F, tcc1_3F, tcc1_4F, tcc1_5F, tcc1_6F,
	tcc2_0F = 0x10, tcc2_1F, tcc2_2F,
	tcc3_0F = 0x18, tcc3_1F,
	tcc4_0F = 0x20, tcc4_1F,

	// TCC devices on peripheral G
	tcc0_0G = 0x80, tcc0_1G, tcc0_2G, tcc0_3G, tcc0_4G, tcc0_5G, tcc0_6G, tcc0_7G,
	tcc1_0G = 0x88, tcc1_1G, tcc1_2G, tcc1_3G, tcc1_4G, tcc1_5G,
	tcc2_0G = 0x90, tcc2_1G, tcc2_2G,
	tcc3_0G = 0x98, tcc3_1G,
	tcc4_0G = 0xA0, tcc4_1G,
#endif

#if SAMC21
	// TCC devices on peripheral E
	tcc0_0E = 0x00, tcc0_1E,
	tcc1_0E = 0x08, tcc1_1E,
	tcc2_0E = 0x10, tcc2_1E,
	// TCC devices on peripheral F
	tcc0_0F = 0x80, tcc0_1F, tcc0_2F, tcc0_3F, tcc0_4F, tcc0_5F, tcc0_6F, tcc0_7F,
	tcc1_0F = 0x88, tcc1_1F,		// TCC1 also has outputs 2 and 3, but they are not available for PWM because they don't have corresponding compare registers
#endif

	none = 0xFF
};

/**
 * @brief Extract the TCC number
 *
 * @param tcc The TcOutput value
 * @return The TCC number of tcc
 */
static inline constexpr unsigned int GetDeviceNumber(TccOutput tcc) noexcept { return ((uint8_t)tcc & 0x7F) >> 3; }

/**
 * @brief Extract the output number
 *
 * @param tcc The TccOutput value
 * @return The output number of tcc
 */
static inline constexpr unsigned int GetOutputNumber(TccOutput tcc) noexcept { return (uint8_t)tcc & 7; }

/**
 * @brief Get the peripheral function that a TCC output is on
 *
 * @param tcc the TCC output
 * @return The peripheral function identifier
 */
static inline constexpr GpioPinFunction GetPeriNumber(TccOutput tcc) noexcept
{
#if SAME5x
	return ((uint8_t)tcc >= 0x80) ? GpioPinFunction::G : GpioPinFunction::F;		// peripheral G or F
#elif SAMC21
	return ((uint8_t)tcc >= 0x80) ? GpioPinFunction::F : GpioPinFunction::E;		// peripheral F or E
#endif
}

/**
 * @brief Initialise a TCC clock
 *
 * @param tccNumber The TCC number that needs a clock
 * @param gclkNumThe GCLK number to use
 */
void EnableTccClock(unsigned int tccNumber, unsigned int gclkNum) noexcept;

#elif SAME70 || SAM4E || SAM4S

enum class PwmOutput : uint8_t
{
	pwm0l0_a = 0x00, pwm0h0_a, pwm0l1_a, pwm0h1_a, pwm0l2_a, pwm0h2_a, pwm0l3_a, pwm0h3_a,
	pwm0l0_b = 0x20, pwm0h0_b, pwm0l1_b, pwm0h1_b, pwm0l2_b, pwm0h2_b, pwm0l3_b, pwm0h3_b,
	pwm0l0_c = 0x40, pwm0h0_c, pwm0l1_c, pwm0h1_c, pwm0l2_c, pwm0h2_c, pwm0l3_c, pwm0h3_c,
	pwm0l0_d = 0x60, pwm0h0_d, pwm0l1_d, pwm0h1_d, pwm0l2_d, pwm0h2_d, pwm0l3_d, pwm0h3_d,
#if SAME70
	pwm1l0_a = 0x08, pwm1h0_a, pwm1l1_a, pwm1h1_a, pwm1l2_a, pwm1h2_a, pwm1l3_a, pwm1h3_a,
	pwm1l0_b = 0x28, pwm1h0_b, pwm1l1_b, pwm1h1_b, pwm1l2_b, pwm1h2_b, pwm1l3_b, pwm1h3_b,
	pwm1l0_c = 0x48, pwm1h0_c, pwm1l1_c, pwm1h1_c, pwm1l2_c, pwm1h2_c, pwm1l3_c, pwm1h3_c,
	pwm1l0_d = 0x68, pwm1h0_d, pwm1l1_d, pwm1h1_d, pwm1l2_d, pwm1h2_d, pwm1l3_d, pwm1h3_d,
#endif

	none = 0xFF,
};

/**
 * @brief Extract the PWM channel number
 *
 * @param tcc The PwmOutput value
 * @return The PWM channel number, 0 to 7. On the SAME70, channels 0-3 are on PWM0, 4-7 are on PWM1.
 */
static inline constexpr unsigned int GetChannelNumber(PwmOutput pwm) noexcept
{
	return ((uint8_t)pwm >> 1) & 0x07;
}

/**
 * @brief Extract the output number, PWML or PWMH
 *
 * @param pwm The PwmOutput value
 * @return 1 for PWMH, 0 for PWML
 */
static inline constexpr unsigned int GetOutputNumber(PwmOutput pwm) noexcept
{
	return (uint8_t)pwm & 1;
}

/**
 * @brief Get the peripheral function that a PWM output is on
 *
 * @param tcc The PwmOutput value
 * @return The peripheral function identifier
 */
static inline constexpr GpioPinFunction GetPeriNumber(PwmOutput pwm) noexcept
{
	return (GpioPinFunction)((uint8_t)pwm >> 5);
}

#endif
#endif
#if STM32F4
typedef uint32_t AdcInput;
typedef AdcInput AnalogChannelNumber;
constexpr AnalogChannelNumber NO_ADC = (AnalogChannelNumber)0xffffffff;
#elif LPC17xx
enum AnalogChannelNumber : int8_t
{
    NO_ADC=-1,
    ADC0=0,
    ADC1,
    ADC2,
    ADC3,
    ADC4,
    ADC5,
    ADC6,
    ADC7
};
typedef AnalogChannelNumber AdcInput;
#else
/**
 * @brief ADC input identifiers, encoding both the ADC device and the ADC input number within the device.
 * On the SAMC21 we only support the first ADC and the SDADC. On the SAME5x, SAM4S and SAmE70 we support both ADCs.
 * SAM4S only has one ADC.
 *
 */
enum class AdcInput : uint8_t
{
	adc0_0 = 0x00, adc0_1, adc0_2, adc0_3, adc0_4, adc0_5, adc0_6, adc0_7, adc0_8, adc0_9,
#if SAMC21
	adc0_10, adc0_11,
	sdadc_0 = 0x10, sdadc_1,
#endif
#if SAM4E || SAM4S
	adc0_10, adc0_11, adc0_12, adc0_13, adc0_14,
# if SAM4E
	adc1_0 = 0x10, adc1_1, adc1_2, adc1_3, adc1_4, adc1_5, adc1_6, adc1_7,
# endif
	dac0 = 0x20, dac1,
#endif
#if SAME5x
	adc0_10, adc0_11, adc0_12, adc0_13, adc0_14, adc0_15,
	adc1_0 = 0x10, adc1_1, adc1_2, adc1_3, adc1_4, adc1_5, adc1_6, adc1_7,
	adc1_8, adc1_9, adc1_10, adc1_11, adc1_12, adc1_13, adc1_14, adc1_15,
#endif
#if SAME70
	adc1_0 = 0x10, adc1_1, adc1_2, adc1_3, adc1_4, adc1_5, adc1_6, adc1_7,
	adc1_8, adc1_9, adc1_10, adc1_11,
#endif

	none = 0xFF			// this must give an out-of-range device number when passed to GetDeviceNumber
};

typedef AdcInput AnalogChannelNumber;						///< for backwards compatibility
constexpr AnalogChannelNumber NO_ADC = AdcInput::none;		///< for backwards compatibility
#endif

#if !STM32F4 && !LPC17xx
/**
 * @brief Get the ADC number that an ADC input is on
 *
 * @param ain The AdcInput value
 * @return The ADC number. If the input value was AdcInput::none then an out-of-range ADC number is returned.
 */
static inline constexpr unsigned int GetDeviceNumber(AdcInput ain) noexcept { return (uint8_t)ain >> 4; }

/**
 * @brief Get the ADC input number that an ADC input is on
 *
 * @param ain The AdcInput
 * @return The input number within the ADC
 */
static inline constexpr unsigned int GetInputNumber(AdcInput ain) noexcept { return (uint8_t)ain & 0x0F; }
#endif
/**
 * @brief Return the AdcInput that is attached to a pin
 *
 * @param p The pin number
 * @return The AdcInput, or AdcInput::none
 */
AdcInput PinToAdcChannel(Pin p) noexcept;

#if SAMC21

/**
 * @brief Return the SdAdcInput that is attached to a pin
 *
 * @param p The pin number
 * @return The AdcInput, or AdcInput::none
 */
AnalogChannelNumber PinToSdAdcChannel(Pin p) noexcept;

#endif

#if !STM32F4 && !LPC17xx
/**
 * @brief SERCOM identifier. This encodes a SERCOM number and the peripheral that it is on.
 *
 */
enum class SercomIo : uint8_t
{
	// SERCOM pins on peripheral C
	sercom0c = 0x00,
	sercom1c, sercom2c, sercom3c, sercom4c, sercom5c,
#if SAME5x
	sercom6c, sercom7c,
#endif

	// SERCOM pins on peripheral D
	sercom0d = 0x80,
	sercom1d, sercom2d, sercom3d, sercom4d, sercom5d,
#if SAME5x
	sercom6d, sercom7d,
#endif

	none = 0xFF
};

/**
 * @brief get the SERCOM number
 *
 * @param sercom The SercomIo
 * @return the SERCOM number
 */
static inline constexpr unsigned int GetDeviceNumber(SercomIo sercom) noexcept { return (uint8_t)sercom & 7; }

/**
 * @brief Get the peripheral ID
 *
 * @param sercom The SercomIo
 * @return The peripheral ID
 */
static inline constexpr GpioPinFunction GetPeriNumber(SercomIo sercom) noexcept { return ((uint8_t)sercom >= 0x80) ? GpioPinFunction::D : GpioPinFunction::C; }

// Addresses of unique ID dwords
#if SAME5x
constexpr uint32_t SerialNumberAddresses[4] = { 0x008061FC, 0x00806010, 0x00806014, 0x00806018 };
#elif SAMC21
constexpr uint32_t SerialNumberAddresses[4] = { 0x0080A00C, 0x0080A040, 0x0080A044, 0x0080A048 };
#endif

/**
 * @section AppInterface Functions that must be provided by the application project
 */

/**
 * @brief Layout of an entry in the pin table. The client project may add additional fields by deriving from this.
 */
struct PinDescriptionBase
{
#if SAME5x || SAMC21

	TcOutput tc;					///< The TC output that is connected to this pin and available for PWM generation, or TcOutput::none
	TccOutput tcc;					///< The TCC output that is connected to this pin and available for PWM generation, or TccOutput::none
	AdcInput adc;					///< The ADC input that is connected to this pin and available, or AdcInput::none
#if SAMC21
	AdcInput sdadc;					///< The SDADC input that is connected to this pin and available, or AdcInput::none
#endif
	SercomIo sercomIn;				///< The Sercom input that is connected to this pin and available, or SercomIo::none
	SercomIo sercomOut;				///< The Sercom output that is connected to this pin and available, or SercomIo::none
	ExintNumber exintNumber;		///< The EXINT number that is allocated exclusively for use by this pin, or Nx if none available

#elif SAME70 || SAM4E || SAM4S

	TcOutput tc;					///< The Timer output that is connected to this pin and available for PWM generation, or TcOutput::none
	PwmOutput pwm;					///< The PWM output that is connected to this pin and available for PWM generation, or PwmOutput::none
	AdcInput adc;					///< The ADC input that is connected to this pin and available, or AdcInput::none

#endif
};
#endif
class MicrosecondsTimer
{
public:
	MicrosecondsTimer() noexcept;
	void Reset() noexcept;
	uint32_t Read() noexcept;
private:
	uint32_t startMillis;
	uint32_t startCycles;
};

/**
 * @brief Initialise the application. Called after the main clocks have been set up.
 * You can use delayMicroseconds() in this function but not delay().
 */
extern void AppInit() noexcept;

/**
 * @brief Run the application. Must not return.
 */
[[noreturn]] extern void AppMain() noexcept;

#if !STM32F4 && !LPC17xx
/**
 * @brief Get the frequency in MHz of the crystal connected to the MCU. Should be 12, 16 or 25.
 * @return Frequency in MHz
 */
extern unsigned int AppGetXoscFrequency() noexcept;

#if SAME5x

/**
 * @brief Get the MCU oscillator number whose pins the crystal is connected to
 * @return XOSC number, 0 or 1
 */
extern unsigned int AppGetXoscNumber() noexcept;

#endif

/**
 * @brief Get a pin table entry
 * @param p Pin number
 * @return Pointer to the pin table entry for that pin, or nullptr if the pin does not exist
 */
extern const PinDescriptionBase *AppGetPinDescription(Pin p) noexcept;

#if SAME5x

/**
 * @brief Return the frequency of the SDHC peripheral clock. Only needs to be provided if the SDHC subsystem is used.
 * @return Frequency in Hz
 */
extern uint32_t AppGetSdhcClockSpeed() noexcept;

#endif
#endif
#endif /* SRC_HARDWARE_SAME5X_COREIO_H_ */
