/*
 * SafeVsnprintf.h
 *
 *  Created on: 8 Apr 2018
 *      Author: David
 */

#ifndef SRC_GENERAL_SAFEVSNPRINTF_H_
#define SRC_GENERAL_SAFEVSNPRINTF_H_

#include <cstdarg>
#include <cstddef>
#include "function_ref.h"

typedef function_ref<bool(char) /*noexcept*/ > PutcFunc_t;

// These functions are like vprintf and printf but each character to print is sent through a function
// The putc function must behave as follows:
// If the character passed is not zero: if possible, send or store the character and return true; else store a terminator if necessary and return false to terminate the vuprintf call.
// If the character passed is zero, this signals the last character being printed at this time, so store a terminator if necessary. The return value is unimportant.
// NOTE: whenever a format specifier of exactly "%.s" is encountered, the string argument is JSON-escaped.
int vuprintf(PutcFunc_t putc, const char *format, va_list args) noexcept;
int uprintf(PutcFunc_t putc, const char *format, ...) noexcept __attribute__ ((format (printf, 2, 3)));

int SafeVsnprintf(char *buffer, size_t maxLen, const char *format, va_list args) noexcept;
int SafeSnprintf(char* buffer, size_t maxLen, const char* format, ...) noexcept __attribute__ ((format (printf, 3, 4)));

extern "C" [[deprecated("use SafeSnprintf instead of snprintf")]] int snprintf(char * s, size_t n, const char * format, ...);
extern "C" [[deprecated("use SafeVsnprintf instead of vsnprintf")]] int vsnprintf(char * s, size_t n, const char * format, va_list arg);

#endif /* SRC_GENERAL_SAFEVSNPRINTF_H_ */
