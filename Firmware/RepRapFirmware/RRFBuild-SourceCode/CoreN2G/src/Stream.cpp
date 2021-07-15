/*
 * Stream.cpp
 *
 *  Created on: 12 Jul 2020
 *      Author: David
 *  License: GNU GPL version 3
 */

#include "Stream.h"

size_t Stream::readBytes(char *buffer, size_t length) noexcept
{
	size_t count = 0;
	while (count < length)
	{
		int c = read();
		if (c < 0)
		{
			break;
		}
		*buffer++ = (char)c;
		count++;
	}
	return count;
}

// End
