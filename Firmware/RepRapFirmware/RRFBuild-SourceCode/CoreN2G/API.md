# Core N2G C API

These functions are declared in file Core.h. C source files shoulld #include this file. C++ source files should #include CoreIO.h (which #includes Core.h) instead.

## Types
### DmaChannel
Represents a DMA chennel number.

### DmaPriority
Represents a DMA priority level. On the SAME5x and SAMC21, priorities range from 0 (highest priority) to 3 (lowest priority).

### Pin
Represents a pin number. Pin numbers 0-31 are the Port A pins, 32-63 are the Port B pins and so on. See also functions PortAPin, PortBPin usw. declared in CoreIO.h.

### ExintNumber
This represents the number of a SAME5x or SAMC21 EXINT. Used in the pin table.

### PwmFrequency
An unsigned integral type that represents a PWM frequency. Typically 16-bits, to 0 to 65536Hz.

### NvicPriority
An unsigned type that represents an interrupt priority. Ranges from 0 to 7 on most procressos, but SAM4S and SAM4E support 0-15.

### enum PinMode
An enumeration that descibes the desired mode of a pin. One of: INPUT, INPUT_PULLUP, INPUT_PULLDOWN, OUTPUT_LOW, OUTPUT_HIGH, AIN, OUTPUT_PWM_LOW, OUTPUT_PWM_HIGH.

### irqflags_t
A type representing whether or not interrupts were or should be enabled.

## Constants
### static const uint32_t SystemCoreClockFreq
The processor clock frequency. Some peripherals may also run at this frequency.

### static const Pin NoPin;
A pin number that never exists.

## Macros
### ARRAY_SIZE(_x)
Returns the number of elements in the array _x.

### UNUSED(_p)
Declares the parameter _p of the currernt function to be unused. Used in some ASF files.

### Assert(_e)
Does nothing; but could be amended to generate a crash dump. Called by some ASF files.

## Functions
### uint32_t millis() noexcept;
Returns a 32-bit count of miliseconds since startup.

### uint64_t millis64() noexcept;
Returns a 64-bit count of miliseconds since startup.

### void delay(uint32_t millis) noexcept;
Delays by the specified number of milliseconds.

### void pinMode(Pin pin, enum PinMode mode) noexcept;
Sets the specified pin to the specified mode, if possible. Safe to call with an invalid pin number such as NoPin.

### bool digitalRead(Pin pin) noexcept;
Reads from the specified pin to the specified mode, if possible. Returns false if called with an invalid pin number such as NoPin.

### void digitalWrite(Pin pin, bool high) noexcept;
Writes to the specified pin to the specified mode, if possible. Safe to call with an invalid pin number such as NoPin.

### uint32_t random32(void) noexcept;
Returns a ransom or pseudo-random 32-bit unsigned integer. Uses the true ramdom number generator peripheral if the MCU has one.

### uint32_t DelayCycles(uint32_t start, uint32_t cycles) noexcept;
Delays until at least the specified number of processor clock cycles after 'start'.

### static inline void delayMicroseconds(uint32_t) noexcept;
Delays for at least the specified number of microseconds.

### static inline void cpu_irq_enable() noexcept;
Enables interrupts.

### static inline void cpu_irq_disable() noexcept;
Disables interrupts.

### static inline bool cpu_irq_is_enabled() noexcept;
Returns true if interrupts are enabled.

### static inline bool cpu_irq_is_enabled_flags(irqflags_t flags) noexcept;
Converts its argument to boolean.

### static inline irqflags_t cpu_irq_save() noexcept;
Disables interrupts and returns the original interrupt state. C++ source files should normally use class AtomicCriticalSectionLocker instead.

### static inline void cpu_irq_restore(irqflags_t flags) noexcept;
Enables interrupts if its argument indicates that they should be enabled. C++ source files should normally use class AtomicCriticalSectionLocker instead.

### static inline bool isDigit(char c) noexcept;
Returns true if the argument represents one of the digits 0 thru 9.

### static inline bool inInterrupt() noexcept;
Returns true when called from an interrupt service routine or exception handler, otherwise false.
