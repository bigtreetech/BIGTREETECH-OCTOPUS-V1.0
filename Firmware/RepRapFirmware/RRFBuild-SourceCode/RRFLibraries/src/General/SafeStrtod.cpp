/*
 * strtod.cpp
 *
 *  Created on: 4 Apr 2018
 *      Author: David
 *
 * This is a replacement for strtof() in the C standard library. That version has two problems:
 * 1. It is not reentrant. We can make it so by defining configUSE_NEWLIB_REENTRANT in FreeRTOS, but that makes the tasks much bigger.
 * 2. It allocates and releases heap memory, which is not nice.
 *
 * Limitations of this versions
 * 1. Rounding to nearest float might possibly not always be correct.
 * 2. Does not handle overflow for stupidly large numbers correctly.
 */

#include <cstdint>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <limits>

#include "SafeStrtod.h"
#undef strtoul		// Undo the macro definition of strtoul in SafeStrtod.h so that we can call it in this file

#include "NumericConverter.h"

float SafeStrtof(const char *s, const char **endptr) noexcept
{
	// Save the end pointer in case of failure
	if (endptr != nullptr)
	{
		*endptr = s;
	}

	// Parse the number
	NumericConverter conv;
	if (conv.Accumulate(*s, NumericConverter::AcceptSignedFloat, [&s]()->char { ++s; return *s; } ))
	{
		if (endptr != nullptr)
		{
			*endptr = s;
		}
		return conv.GetFloat();
	}

	return 0.0f;
}

static uint32_t StrToU32Opt(const char *s, const char **endptr, NumericConverter::OptionsType options) noexcept
{
	// Save the end pointer in case of failure
	if (endptr != nullptr)
	{
		*endptr = s;
	}

	// Parse the number
	NumericConverter conv;
	if (conv.Accumulate(*s, options, [&s]()->char { ++s; return *s; } ))
	{
		if (endptr != nullptr)
		{
			*endptr = s;
		}
		return (conv.FitsInUint32()) ? conv.GetUint32() : std::numeric_limits<uint32_t>::max();
	}

	return 0;
}

uint32_t StrToU32(const char *s, const char **endptr) noexcept
{
	return StrToU32Opt(s, endptr, NumericConverter::AcceptOnlyUnsignedDecimal);
}

uint32_t StrOptHexToU32(const char *s, const char **endptr) noexcept
{
	return StrToU32Opt(s, endptr, NumericConverter::AcceptHex);
}

uint32_t StrHexToU32(const char *s, const char **endptr) noexcept
{
	return StrToU32Opt(s, endptr, NumericConverter::DefaultHex);
}

int32_t StrToI32(const char *s, const char **endptr) noexcept
{
	// Save the end pointer in case of failure
	if (endptr != nullptr)
	{
		*endptr = s;
	}

	// Parse the number
	NumericConverter conv;
	if (conv.Accumulate(*s, NumericConverter::AcceptNegative, [&s]()->char { ++s; return *s; } ))
	{
		if (endptr != nullptr)
		{
			*endptr = s;
		}
		return (conv.FitsInInt32()) ? conv.GetInt32()
				: (conv.IsNegative()) ? std::numeric_limits<int32_t>::min()
					: std::numeric_limits<int32_t>::max();
	}

	return 0;
}

unsigned long SafeStrtoul(const char *s, const char **endptr, int base) noexcept
{
	// strtoul() accepts a leading minus-sign, which we don't want to allow
	while (*s == ' ' || *s == '\t')
	{
		++s;
	}
	if (*s == '-')
	{
		if (endptr != nullptr)
		{
			*endptr = s;
		}
		return 0;
	}
	return strtoul(s, const_cast<char**>(endptr), base);
}

// End
