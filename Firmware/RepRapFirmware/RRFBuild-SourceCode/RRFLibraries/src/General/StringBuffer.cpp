/*
 * StringBuffer.cpp
 *
 *  Created on: 8 Jan 2020
 *      Author: David
 */

#include "StringBuffer.h"

// Finish working on the latest string and start a new one. Return true if insufficient space.
bool StringBuffer::Fix() noexcept
{
	const size_t slen = strlen(p + used);
	if (used + slen + 1 < len)
	{
		used += slen + 1;
		p[used] = 0;
		return false;
	}
	return true;
}

// Concatenate two strings, placing the result at the end of the buffer. Return true if insufficient space.
// One or both strings may already be in the buffer, and we don't need to keep them intact. Optimise storage where possible.
bool StringBuffer::Concat(const char *s1, const char *s2) noexcept
{
	const size_t s2LenPlusOne = strlen(s2) + 1;
	const size_t s1Len = strlen(s1);
	if (s2 + s2LenPlusOne == p + used)
	{
		// s2 is the last fixed string in the buffer. If s1 is the previous string, we can just slide s2 down one place.
		if (s1 + s1Len + 1 == s2)
		{
			memmove(const_cast<char *>(s1 + s1Len), s2, s2LenPlusOne);
			used -= (s1Len + 1 + s2LenPlusOne);
			return false;
		}
	}
	else if (s1 + s1Len + 1 == p + used)
	{
		// s1 is the last string in the buffer
		used -= s1Len + 1;
		return GetRef().cat(s2);
	}

	// No optimisation possible
	return GetRef().copy(s1) || GetRef().cat(s2);
}

// The is called when we have finished using a string, which may be in the buffer. If it is the last string in the buffer, we can delete it.
void StringBuffer::FinishedUsing(const char *s) noexcept
{
	const size_t len = strlen(s) + 1;
	if (s + len == p + used)
	{
		used -= len;
		p[used] = 0;
	}
}

// End
