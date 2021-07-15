/*
 Print.cpp - members of Print class
 */

#include "Print.h"
#include <General/SafeVsnprintf.h>
#include <cstdarg>

// This default implementation may be overridden in derived classes for optimisation purposes
size_t Print::write(const uint8_t *buffer, size_t size) noexcept
{
	size_t n = 0;
	while (size--)
	{
		n += write(*buffer++);
	}
	return n;
}

int Print::printf(const char *fmt, ...) noexcept
{
	va_list vargs;
	va_start(vargs, fmt);
	const int ret = printf(fmt, vargs);
	va_end(vargs);
	return ret;
}

int Print::printf(const char *fmt, va_list vargs) noexcept
{
	return vuprintf([this](char c)->bool
					{
						return c == 0 || write(c) >= 0;
					},
					fmt, vargs);
}

// End
