/*
 * StringBuffer.h
 *
 *  Created on: 8 Jan 2020
 *      Author: David
 */

#ifndef SRC_GENERAL_STRINGBUFFER_H_
#define SRC_GENERAL_STRINGBUFFER_H_

#include "StringRef.h"

// Class to define a buffer that can hold multiple strings
class StringBuffer
{
public:
	StringBuffer(char *pp, size_t pl) noexcept : p(pp), len(pl), used(0) { *p = 0; }

	// Get a StringRef to the latest string in the buffer
	StringRef GetRef() const noexcept { return StringRef(p + used, len - used); }

	// Get a c-style string pointer to the latest string
	const char *LatestCStr() const noexcept { return p + used; }

	// Clear the current string
	void ClearLatest() noexcept { p[used] = 0; }

	// Finish working on the latest string and start a new one. Return true if insufficient space.
	bool Fix() noexcept;

	// Concatenate two strings, placing the result at the end of the buffer. Return true if insufficient space.
	// One or both strings may already be in the buffer, and we don't need to keep them intact. Optimise storage where possible.
	bool Concat(const char *s1, const char *s2) noexcept;

	// Say that we have finished using a string, which may be in the buffer. If it is the last string in the buffer, we can delete it.
	void FinishedUsing(const char *s) noexcept;

	// Reset the buffer to be empty
	void Reset() noexcept { used = 0; }

private:
	char *p;				// pointer to the storage
	size_t len;				// number of characters in the storage, must be at least 1
	size_t used;			// how much of the buffer we have used so far

	// invariant(used < len)
};

#endif /* SRC_GENERAL_STRINGBUFFER_H_ */
