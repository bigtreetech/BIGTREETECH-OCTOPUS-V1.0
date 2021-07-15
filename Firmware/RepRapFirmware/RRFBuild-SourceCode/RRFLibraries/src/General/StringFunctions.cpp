/*
 * StringFunctions.cpp
 *
 *  Created on: 8 Jul 2019
 *      Author: David
 */

#include "StringFunctions.h"
#include <cstring>
#include <cctype>

bool StringEndsWithIgnoreCase(const char* string, const char* ending) noexcept
{
	const size_t j = strlen(string);
	const size_t k = strlen(ending);
	return k <= j && StringEqualsIgnoreCase(&string[j - k], ending);
}

bool StringEqualsIgnoreCase(const char* s1, const char* s2) noexcept
{
	size_t i = 0;
	while (s1[i] != 0 && s2[i] != 0)
	{
		if (tolower(s1[i]) != tolower(s2[i]))
		{
			return false;
		}
		i++;
	}

	return s1[i] == 0 && s2[i] == 0;
}

bool ReducedStringEquals(const char* s1, const char* s2) noexcept
{
	while (*s1 != 0 && *s2 != 0)
	{
		if (*s1 == '-' || *s1 == '_')
		{
			++s1;
		}
		else if (*s2 == '-' || *s2 == '_')
		{
			++s2;
		}
		else if (tolower(*s1) != tolower(*s2))
		{
			return false;
		}
		else
		{
			++s1;
			++s2;
		}
	}

	return *s1 == 0 && *s2 == 0;
}

bool StringStartsWith(const char* string, const char* starting) noexcept
{
	const size_t j = strlen(string);
	const size_t k = strlen(starting);
	if (k > j)
	{
		return false;
	}

	for (size_t i = 0; i < k; i++)
	{
		if (string[i] != starting[i])
		{
			return false;
		}
	}

	return true;
}

bool StringStartsWithIgnoreCase(const char* string, const char* starting) noexcept
{
	const size_t j = strlen(string);
	const size_t k = strlen(starting);
	if (k > j)
	{
		return false;
	}

	for (size_t i = 0; i < k; i++)
	{
		if (tolower(string[i]) != tolower(starting[i]))
		{
			return false;
		}
	}

	return true;
}

int StringContains(const char* string, const char* match) noexcept
{
	int i = 0;
	int count = 0;

	while (string[i] != 0)
	{
		if (string[i++] == match[count])
		{
			count++;
			if (match[count] == 0)
			{
				return i - count;
			}
		}
		else
		{
			count = 0;
		}
	}

	return -1;
}

// Version of strncpy that ensures the result is null terminated
void SafeStrncpy(char *dst, const char *src, size_t length) noexcept
{
	strncpy(dst, src, length);
	dst[length - 1] = 0;
}

// Version of strcat that takes the original buffer size as the limit and ensures the result is null terminated
void SafeStrncat(char *dst, const char *src, size_t length) noexcept
{
	dst[length - 1] = 0;
	const size_t index = strlen(dst);
	strncat(dst + index, src, length - index);
	dst[length - 1] = 0;
}

// End
