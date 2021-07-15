/*
 * StringFunctions.h
 *
 *  Created on: 8 Jul 2019
 *      Author: David
 */

#ifndef SRC_GENERAL_STRINGFUNCTIONS_H_
#define SRC_GENERAL_STRINGFUNCTIONS_H_

#include "ecv.h"
#undef array

#include <cstdint>
#include <cstddef>

bool StringEndsWithIgnoreCase(const char* string, const char* ending) noexcept;
bool StringStartsWith(const char* string, const char* starting) noexcept;
bool StringStartsWithIgnoreCase(const char* string, const char* starting) noexcept;
bool StringEqualsIgnoreCase(const char* s1, const char* s2) noexcept;
bool ReducedStringEquals(const char* s1, const char* s2) noexcept;
int StringContains(const char* string, const char* match) noexcept;
void SafeStrncpy(char *dst, const char *src, size_t length) noexcept pre(length != 0);
void SafeStrncat(char *dst, const char *src, size_t length) noexcept pre(length != 0);

#endif /* SRC_GENERAL_STRINGFUNCTIONS_H_ */
