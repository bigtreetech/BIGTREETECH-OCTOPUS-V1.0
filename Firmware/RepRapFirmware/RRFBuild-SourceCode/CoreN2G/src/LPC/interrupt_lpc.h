
#ifndef INTERRUPT_LPC_H
#define INTERRUPT_LPC_H

#include <stdbool.h>
#include <stdint.h>
#include "chip.h"




#ifdef __cplusplus

// Functions to change the base priority, to shut out interrupts up to a priority level

// From section 3.12.7 of http://infocenter.arm.com/help/topic/com.arm.doc.dui0553b/DUI0553.pdf:
// When you write to BASEPRI_MAX, the instruction writes to BASEPRI only if either:
// - Rn is non-zero and the current BASEPRI value is 0
// - Rn is non-zero and less than the current BASEPRI value
__attribute__( ( always_inline ) ) __STATIC_INLINE void __set_BASEPRI_MAX(uint32_t value)
{
  __ASM volatile ("MSR basepri_max, %0" : : "r" (value) : "memory");
}

#endif

#endif /* INTERRUPT_LPC_H */
