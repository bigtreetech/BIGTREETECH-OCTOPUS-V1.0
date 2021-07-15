/*
 * NamedEnum.cpp
 *
 *  Created on: 7 Mar 2020
 *      Author: David
 */

#include "NamedEnum.h"
#include <cstddef>
#include <cstring>

// Function to search the table of names for a match. Returns numNames if not found.
unsigned int NamedEnumLookup(const char *s, const char * const names[], size_t numNames) noexcept
{
	unsigned int low = 0, high = numNames;
	while (high > low)
	{
		const size_t mid = (high - low)/2 + low;
		const int t = strcmp(s, SkipLeadingUnderscore(names[mid]));
		if (t == 0)
		{
			return mid;
		}
		if (t > 0)
		{
			low = mid + 1u;
		}
		else
		{
			high = mid;
		}
	}
	return (low < numNames && strcmp(s, SkipLeadingUnderscore(names[low])) == 0) ? low : numNames;
}

// End
