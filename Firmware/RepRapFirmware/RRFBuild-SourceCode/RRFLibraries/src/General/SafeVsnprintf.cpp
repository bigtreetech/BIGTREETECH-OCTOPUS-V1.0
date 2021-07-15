/*
 * vsnprintf.cpp
 *
 *  Created on: 8 Apr 2018

	Original copyright 2001, 2002 Georges Menie (www.menie.org)
	stdarg version contributed by Christian Ettinger
	Converted to C++ and adapted to support floating point formats by D. Crocker

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	Changes for the FreeRTOS ports:

	- The dot in "%-8.8s"
	- The specifiers 'l' (long) and 'll' (long long)
	- The specifier 'u' for unsigned
	- Dot notation for IP addresses:
	  sprintf("IP = %xip\n", 0xC0A80164);
      will produce "IP = 192.168.1.100\n"
	  sprintf("IP = %pip\n", pxIPv6_Address);
*/

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cmath>

#include "Strnlen.h"
#include "SafeVsnprintf.h"

// The following should be enough for 32-bit int/long and 64-bit long long
constexpr size_t MaxLongDigits = 10;	// to print 4294967296
constexpr size_t MaxUllDigits = 20;		// to print 18446744073709551616

struct xPrintFlags
{
	int base;
	int width;
	int printLimit;
	union
	{
		struct
		{
			uint32_t
				letBase : 8,
				padZero : 1,
				padRight : 1,
				signOrSpace : 1,
				forceSign : 1,
				isSigned : 1,
				isNumber : 1,
				isString : 1,
				long32 : 1,
				long64 : 1,
				hash : 1;
		};
		uint32_t allFlags;
	};

	bool NeedPrefix() const noexcept
	{
		return hash && (base == 16 || base == 8);
	}
};

class FormattedPrinter
{
public:
	FormattedPrinter(const PutcFunc_t& pcf) noexcept;
	int Print(const char *format, va_list args) noexcept;

private:
	PutcFunc_t putchar;
	int curLen;
	xPrintFlags flags;

	void Init() noexcept;
	bool PutString(const char *apString) noexcept;
	bool PutJson(const char *apString) noexcept;
	bool PrintLL(long long i) noexcept;
	bool PrintI(int i) noexcept;
	bool PrintFloat(double d, char formatLetter) noexcept;
	bool PutChar(char c) noexcept;
	bool PutStringWithSign(char *s, bool isNegative) noexcept;
	bool DoPrefix() noexcept;
};

FormattedPrinter::FormattedPrinter(const PutcFunc_t& pcf) noexcept
	: putchar(pcf), curLen(0)
{
	Init();
}

void FormattedPrinter::Init() noexcept
{
	flags.base = flags.width = 0;
	flags.printLimit = -1;
	flags.allFlags = 0;
}

bool FormattedPrinter::PutChar(char c) noexcept
{
	const bool ret = putchar(c) && c != 0;
	if (ret)
	{
		++curLen;
	}
	return ret;
}

/*-----------------------------------------------------------*/

// Print the string s to the string buffer adding any necessary padding
bool FormattedPrinter::PutString(const char *apString) noexcept
{
	int count;
	if (flags.printLimit > 0 && flags.isString)
	{
		// It's a string so printLimit is the max number of characters to print from the string.
		// Don't call strlen on it because it might not be null terminated, use Strnlen instead.
		count = (int)Strnlen(apString, flags.printLimit);
	}
	else
	{
		count = (int)strlen(apString);
	}

	int rightSpacesNeeded = 0;
	const bool hasMinimumDigits = (flags.isNumber && flags.printLimit > 0);
	if (hasMinimumDigits || flags.width > 0)
	{
		// We may have some padding to do
		int leftSpacesNeeded = 0, leftZerosNeeded = 0;
		if (hasMinimumDigits && count < flags.printLimit)
		{
			leftZerosNeeded = flags.printLimit - count;
		}
		if (count + leftZerosNeeded < flags.width)
		{
			const int remainingPaddingNeeded = flags.width - (count + leftZerosNeeded);
			if (flags.padRight)
			{
				rightSpacesNeeded = remainingPaddingNeeded;
			}
			else if (flags.padZero)
			{
				leftZerosNeeded += remainingPaddingNeeded;
			}
			else
			{
				leftSpacesNeeded = remainingPaddingNeeded;
			}
		}

		// Do the left padding
		while (leftSpacesNeeded > 0)
		{
			if (!PutChar(' '))
			{
				return false;
			}
			--leftSpacesNeeded;
		}
		while (leftZerosNeeded > 0)
		{
			if (!PutChar('0'))
			{
				return false;
			}
			--leftZerosNeeded;
		}
	}

	// Now print the actual string
	while (count > 0)
	{
		if (!PutChar(*apString++))
		{
			return false;
		}
		--count;
	}

	// Now the right padding
	while (rightSpacesNeeded > 0)
	{
		if (!PutChar(' '))
		{
			return false;
		}
		--rightSpacesNeeded;
	}

	return true;
}

// Write a string in JSON format returning true if successful. Width specifiers are ignored.
bool FormattedPrinter::PutJson(const char *apString) noexcept
{
	bool ok = true;
	while (ok)
	{
		const char c = *apString;
		char esc;
		switch (c)
		{
		case '\0':
			return true;
		case '\r':
			esc = 'r';
			break;
		case '\n':
			esc = 'n';
			break;
		case '\t':
			esc = 't';
			break;
		case '"':
		case '\\':
#if 1
		// Escaping '/' is optional in JSON, although doing so so confuses PanelDue (fixed in PanelDue firmware version 1.15 and later). As it's optional, we don't do it.
#else
		case '/':
#endif
			esc = c;
			break;
		default:
			esc = 0;
			break;
		}

		if (esc != 0)
		{
			ok = PutChar('\\') && PutChar(esc);
		}
		else
		{
			ok = PutChar(c);
		}
		++apString;
	}
	return false;
}

// Output the string representation of the number to be printed, with a sign uf necessary, padded as required
// 's' is the string representation of the number to be printed, with space for a sign to be added at the front
bool FormattedPrinter::PutStringWithSign(char *s, bool isNegative) noexcept
{
	const char sign = (isNegative) ? '-'
						: flags.forceSign ? '+'
							: flags.signOrSpace ? ' '
								: 0;
	if (sign != 0)
	{
		if (flags.width != 0 && flags.padZero)
		{
			if (!PutChar(sign))
			{
				return false;
			}
			--flags.width;
		}
		else
		{
			*--s = sign;
		}
	}

	return PutString(s);
}

// Output the 0x or 0X or 0 prefix if necessary, returning true if successful or on prefix needed
bool FormattedPrinter::DoPrefix() noexcept
{
	if (flags.NeedPrefix())
	{
		if (!PutChar('0'))
		{
			return false;
		}
		if (flags.base == 16)
		{
			return PutChar(flags.letBase + ('X' - 'A'));
		}
	}
	return true;
}

/*-----------------------------------------------------------*/

bool FormattedPrinter::PrintLL(long long i) noexcept
{
	flags.isNumber = true;	/* Parameter for prints */
	if (i == 0LL)
	{
		return PutString("0");
	}

	if (!DoPrefix())
	{
		return false;
	}

	bool neg = false;
	unsigned long long u = i;
	if ((flags.isSigned) && (flags.base == 10) && (i < 0LL))
	{
		neg = true;
		u = -i;
	}

	char print_buf[MaxUllDigits + 2];
	char *s = print_buf + sizeof print_buf - 1;
	*s = '\0';
	while (u != 0)
	{
		unsigned int t = u % (unsigned int)flags.base;
		u /= (unsigned int)flags.base;
		if (t >= 10)
		{
			t += flags.letBase - '0' - 10;
		}
		*--s = t + '0';
	}

	return PutStringWithSign(s, neg);
}

/*-----------------------------------------------------------*/

bool FormattedPrinter::PrintI(int i) noexcept
{
	flags.isNumber = true;	/* Parameter for prints */

	if (i == 0)
	{
		return PutString("0");
	}

	if (!DoPrefix())
	{
		return false;
	}

	bool neg = false;
	unsigned int u = i;
	unsigned base = flags.base;
	if ((flags.isSigned) && (base == 10) && (i < 0))
	{
		neg = true;
		u = -i;
	}

	char print_buf[MaxLongDigits + 2];
	char *s = print_buf + sizeof print_buf - 1;
	*s = '\0';

	switch (base)
	{
	case 16:
		while (u != 0)
		{
			unsigned int t = u & 0xF;
			if (t >= 10)
			{
				t += flags.letBase - '0' - 10;
			}
			*--s = t + '0';
			u >>= 4;
		}
		break;

	case 8:
	case 10:
		// GCC compiles very efficient
		while (u != 0)
		{
			const unsigned int t = u % base;
			*--s = t + '0';
			u /= base;
		}
		break;
#if 0
	// The generic case, not yet in use
	default:
		while (u != 0)
		{
			const unsigned int t = u % base;
			if (t >= 10)
			{
				t += flags.letBase - '0' - 10;
			}
			*--s = t + '0';
			u /= base;
		}
		break;
#endif
	}

	return PutStringWithSign(s, neg);
}

/*-----------------------------------------------------------*/

#ifndef NO_PRINTF_FLOAT

// Print a number in scientific format
// flags.printLimit is the number of decimal digits required
bool FormattedPrinter::PrintFloat(double d, char formatLetter) noexcept
{
	if (std::isnan(d))
	{
		return PutString("nan");
	}
	if (std::isinf(d))
	{
		return PutString("inf");
	}

	double ud = fabs(d);
	if (ud > (double)LONG_LONG_MAX && (formatLetter == 'f' || formatLetter == 'F'))
	{
		--formatLetter;			// number is too big to print easily in fixed point format, so use exponent format
	}

	int exponent = 0;
	if (formatLetter == 'e' || formatLetter == 'E' || formatLetter == 'g' || formatLetter == 'G')
	{
		// Using exponent format, so calculate the exponent and normalise ud to be >=1.0 but <=10.0
		// The following loops are inefficient, however we don't expect to print very large or very small numbers
		while (ud > (double)100000.0)
		{
			ud /= (double)100000.0;
			exponent += 5;
		}
		while (ud > (double)10.0)
		{
			ud /= (double)10.0;
			++exponent;
		}
		if (ud != (double)0.0)
		{
			while (ud < (double)0.00001)
			{
				ud *= (double)100000.0;
				exponent -= 5;
			}
			while (ud < (double)1.0)
			{
				ud *= (double)10.0;
				--exponent;
			}
		}
		// ud is now at least 1.0 but less than 10.0 and exponent is the exponent
	}

	if (flags.printLimit < 0)
	{
		flags.printLimit = 6;					// set the default number of decimal digits
	}

	if (formatLetter == 'g' || formatLetter == 'G')
	{
		// Convert G format to E or F format
	    if (exponent > -4 && exponent <= flags.printLimit)
	    {
	    	formatLetter -= 1;					// change g to f
	    	ud = fabs(d);						// restore original value of ud
	    }
	    else
	    {
	    	formatLetter -= 2;					// change g to e
	    }
	}

	// Multiply ud by 10 to the power of the number of decimal digits required, or until it becomes too big to print easily
	int digitsAfterPoint = 0;
	long limit = 10;
	while (digitsAfterPoint < flags.printLimit && ud < LONG_LONG_MAX/10 && limit <= LONG_LONG_MAX/10)
	{
		ud *= (double)10.0;
		limit *= 10;
		 ++digitsAfterPoint;
	}

	char print_buf[MaxUllDigits + MaxLongDigits + 5];
	char *s = print_buf + sizeof print_buf - 1;
	*s = '\0';

	long long u = llrint(ud);

	if (formatLetter == 'e' || formatLetter == 'E')
	{
		// Rounding ud may have caused 9.99999... to become 10
		if (ud >= limit)
		{
			ud /= 10;
			++exponent;
		}

		// Store the exponent
		int iexp = abs(exponent);
		do
		{
			*--s = (iexp % 10) + '0';
			iexp = iexp/10;
		} while (iexp != 0);
		*--s = (exponent < 0) ? '-' : '+';
		*--s = formatLetter;
	}

	// Store the non-exponent part
	if (digitsAfterPoint == 0 && !flags.hash)
	{
		--digitsAfterPoint;				// make digitsAfterPoint negative to suppress the decimal point
	}

	do
	{
		if (digitsAfterPoint == 0)
		{
			*--s = '.';
		}
		--digitsAfterPoint;

		const lldiv_t lldiv_result = lldiv(u, 10);
		*--s = (char)((unsigned int)lldiv_result.rem + '0');
		u = lldiv_result.quot;
	}
	while (u != 0 || digitsAfterPoint >= 0);

	return PutStringWithSign(s, d < (double)0.0);
}

#endif

/*-----------------------------------------------------------*/

int FormattedPrinter::Print(const char *format, va_list args) noexcept
{
	for (;;)
	{
		char ch;
		while ((ch = *format++) != '%')
		{
			if (!PutChar(ch))
			{
				return curLen;
			}
		}

		// If we get here then ch == '%'. Get the next character.
		ch = *format++;
		if (ch == '\0')
		{
			break;
		}
		if (ch == '%')
		{
			if (!PutChar(ch))
			{
				return curLen;
			}
			continue;
		}

		Init();

		// Process flag characters
		for (;;)
		{
			switch (ch)
			{
			case '#':
				flags.hash = true;
				break;
			case '-':
				flags.padRight = true;
				break;
			case '0':
				flags.padZero = true;
				break;
			case '+':
				flags.forceSign = true;
				break;
			case ' ':
				flags.signOrSpace = true;
				break;
			default:
				goto doneFlags;
			}
			ch = *format++;
		}
	doneFlags:
		if (ch == '*')
		{
			ch = *format++;
			flags.width = va_arg(args, int);
		}
		else
		{
			while (ch >= '0' && ch <= '9')
			{
				flags.width *= 10;
				flags.width += ch - '0';
				ch = *format++;
			}
		}
		if (ch == '.')
		{
			ch = *format++;
			if (ch == '*')
			{
				flags.printLimit = va_arg(args, int);
				ch = *format++;
			}
			else
			{
				flags.printLimit = 0;
				while (ch >= '0' && ch <= '9')
				{
					flags.printLimit *= 10;
					flags.printLimit += ch - '0';
					ch = *format++;
				}
			}
		}

#ifndef NO_PRINTF_FLOAT
		if (ch == 'f' || ch == 'e' || ch == 'g' || ch == 'F' || ch == 'E' || ch == 'G')
		{
			if (!PrintFloat(va_arg(args, double), ch))
			{
				break;
			}
			continue;
		}
#endif

		// For non-floating point formats, treat a precision of 0 the same as unlimited
		if (flags.printLimit == 0)
		{
			flags.printLimit = -1;		// -1: make it unlimited
		}

		if (ch == 's')
		{
			const char *s = va_arg(args, const char *);
			flags.isString = true;
			// RRF extension: if the current format specifier is exactly "%.s" then perform JSON escaping.
			// We would like to use "%j" instead, but that gives rise to gcc warnings about unrecognised format specifiers and extra arguments.
			if (*(format - 2) == '.' && *(format - 3) == '%')
			{
				if (s != nullptr && !PutJson(s))
				{
					break;
				}
			}
			else if (!PutString((s != nullptr) ? s : "<null>"))
			{
				break;
			}
			continue;
		}

		if (ch == 'c')
		{
			// char are converted to int then pushed on the stack
			const char c2 = (char)va_arg(args, int);
			if (c2 != 0)				// don't print it if it is null
			{
				if (!PutChar(c2))
				{
					return curLen;
				}
			}

			continue;
		}
		if (ch == 'l')
		{
			ch = *format++;
			if (ch == 'l')
			{
				ch = *format++;
				flags.long64 = 1;
			}
			else
			{
				flags.long32 = 1;
			}
		}

		flags.base = 10;
		flags.letBase = 'a';

		if (ch == 'd' || ch == 'u' || ch == 'i')
		{
			flags.isSigned = (ch != 'u');
			if (flags.long64)
			{
				if (!PrintLL(va_arg(args, long long)))
				{
					break;
				}
			}
			else if (!PrintI(va_arg(args, int)))
			{
				break;
			}
			continue;
		}

		flags.base = 16;		// from here all hexadecimal or octal
		if (ch == 'x' || ch == 'X' || ch == 'p' || ch == 'o')
		{
			if (ch == 'X')
			{
				flags.letBase = 'A';
			}
			else if (ch == 'o')
			{
				flags.base = 8;
			}
			if (flags.long64)
			{
				if (!PrintLL(va_arg(args, long long)))
				{
					break;
				}
			}
			else if (!PrintI(va_arg(args, int)))
			{
				break;
			}
			continue;
		}
	}
	PutChar('\0');
	return curLen;
}

/*-----------------------------------------------------------*/

int vuprintf(PutcFunc_t putc, const char *format, va_list args) noexcept
{
	FormattedPrinter fp(putc);
	return fp.Print(format, args);
}

int uprintf(PutcFunc_t putc, const char *format, ...) noexcept
{
	va_list vargs;
	va_start(vargs, format);
	FormattedPrinter fp(putc);
	const int ret = fp.Print(format, vargs);
	va_end(vargs);
	return ret;
}

int SafeVsnprintf(char *buffer, size_t maxLen, const char *format, va_list args) noexcept
{
	// Declare the lambda function separately from declaring the FormattedPrinter so that it doesn't go out of scope before the FormattedPrinter does
	auto lambda = [&buffer, &maxLen](char c) noexcept -> bool
					{
						if (c != 0 && maxLen > 1)
						{
							*buffer++ = c;
							--maxLen;
							return true;
						}
						return false;
					};
	FormattedPrinter fp(lambda);
	const int ret = fp.Print(format, args);
	*buffer = 0;
	return ret;
}

int SafeSnprintf(char* buffer, size_t buf_size, const char* format, ...) noexcept
{
	va_list vargs;
	va_start(vargs, format);
	const int ret = SafeVsnprintf(buffer, buf_size, format, vargs);
	va_end(vargs);
	return ret;
}

// End
