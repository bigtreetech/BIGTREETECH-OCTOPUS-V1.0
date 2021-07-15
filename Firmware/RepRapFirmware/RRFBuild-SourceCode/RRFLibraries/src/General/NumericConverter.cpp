/*
 * NumericConverter.cpp
 *
 *  Created on: 26 Apr 2020
 *      Author: David
 */

#include "NumericConverter.h"
#include <limits>
#include <cmath>
#include <cctype>

// Function to read an unsigned integer or real literal and store the values in this object
// On entry, 'c' is the first character to consume and NextChar is the function to get another character
// Returns true if a valid number was found. If it returns false then characters may have been consumed.
// On return the value parsed is: lvalue * 2^twos * 5^fives
bool NumericConverter::Accumulate(char c, OptionsType options, function_ref<char()> NextChar) noexcept
{
	hadDecimalPoint = hadExponent = isNegative = false;
	bool hadDigit = false;
	unsigned int base = ((options & DefaultHex) != 0) ? 16 : 10;
	lvalue = 0;
	fives = twos = 0;

	// 1. Skip white space
	while (c == ' ' || c == '\t')
	{
		c = NextChar();
	}

	// 2. Check for a sign
	if (c == '+')
	{
		c = NextChar();
	}
	else if (c == '-')
	{
		if ((options & AcceptNegative) == 0)
		{
			return false;
		}
		isNegative = true;
		c = NextChar();
	}

	// If hex allowed, check for leading 0x
	if (c == '0' && (options & AcceptHex) != 0)
	{
		hadDigit = true;
		c = NextChar();
		if (toupper(c) == 'X')
		{
			base = 16;
			options &= ~AcceptFloat;
			c = NextChar();
		}
		else if (toupper(c) == 'B')
		{
			base = 2;
			options &= ~AcceptFloat;
			c = NextChar();
		}
	}

	// Skip leading zeros, but count the number of them after the decimal point
	for (;;)
	{
		if (c == '0')
		{
			hadDigit = true;
			if (hadDecimalPoint)
			{
				--fives;
				--twos;
			}
		}
		else if (c == '.' && !hadDecimalPoint && (options & AcceptFloat) != 0)
		{
			hadDecimalPoint = true;
		}
		else
		{
			break;
		}
		c = NextChar();
	}

	// Read digits and allow a decimal point if we haven't already had one
	bool overflowed = false;
	for (;;)
	{
		if (isxdigit(c))
		{
			const unsigned int digit = (c <= '9') ? c - '0' : (toupper(c) - 'A') + 10;
			if (digit >= base)
			{
				break;
			}

			hadDigit = true;

			switch (base)
			{
			case 2:
				if (overflowed)
				{
					++twos;
				}
				else if (lvalue <= std::numeric_limits<uint32_t>::max()/2)
				{
					lvalue = (lvalue << 1u) + digit;
				}
				else
				{
					overflowed = true;
					++twos;
				}
				break;

			case 10:
				if (overflowed)
				{
					if (!hadDecimalPoint)
					{
						++fives;
						++twos;
					}
				}
				else if (   lvalue <= (std::numeric_limits<uint32_t>::max() - 9u)/10u		// avoid slow division if we can
						 || lvalue <= (std::numeric_limits<uint32_t>::max() - digit)/10u
					    )
				{
					lvalue = (lvalue * 10u) + digit;
					if (hadDecimalPoint)
					{
						--fives;
						--twos;
					}
				}
				else
				{
					overflowed = true;
					const unsigned int fivesDigit = (digit + 1u)/2u;
					if (lvalue <= (std::numeric_limits<uint32_t>::max() - fivesDigit)/5u)
					{
						lvalue = (lvalue * 5u) + fivesDigit;
						if (hadDecimalPoint)
						{
							--fives;
						}
						else
						{
							++twos;
						}
					}
					else
					{
						const unsigned int twosDigit = (digit + 4u)/5u;
						if (lvalue <= (std::numeric_limits<uint32_t>::max() - twosDigit)/2u)
						{
							lvalue = (lvalue * 2u) + twosDigit;
							if (hadDecimalPoint)
							{
								--twos;
							}
							else
							{
								++fives;
							}
						}
						else if (!hadDecimalPoint)
						{
							++fives;
							++twos;
						}
					}
				}
				break;

			case 16:
				if (overflowed)
				{
					twos += 4;
				}
				else if (lvalue <= std::numeric_limits<uint32_t>::max()/16)
				{
					lvalue = (lvalue << 4u) + digit;
				}
				else
				{
					overflowed = true;
					if (lvalue <= std::numeric_limits<uint32_t>::max()/8)
					{
						lvalue = (lvalue << 3u) | ((digit + 1u) >> 1u);
						++twos;
					}
					else if (lvalue <= std::numeric_limits<uint32_t>::max()/4)
					{
						lvalue = (lvalue << 2u) | ((digit + 2u) >> 2u);
						twos += 2;
					}
					else if (lvalue <= std::numeric_limits<uint32_t>::max()/2)
					{
						lvalue = (lvalue << 1u) | ((digit + 4u) >> 3u);
						twos += 3;
					}
					else
					{
						twos += 4;
					}
				}
				break;
			}
		}
		else if (c == '.' && !hadDecimalPoint && (options & AcceptFloat) != 0)
		{
			hadDecimalPoint = true;
		}
		else
		{
			break;
		}
		c = NextChar();
	}

	if (!hadDigit)
	{
		return false;
	}

	// Check for an exponent
	if ((options & AcceptFloat) != 0 && toupper(c) == 'E')
	{
		c = NextChar();

		// 5a. Check for signed exponent
		const bool expNegative = (c == '-');
		if (expNegative || c == '+')
		{
			c = NextChar();
		}

		if (!isdigit(c))
		{
			return false;								// E or e not followed by a number
		}

		// 5b. Read exponent digits
		hadExponent = true;
		unsigned int exponent = 0;
		while (isdigit(c))
		{
			exponent = (10u * exponent) + (c - '0');		// could overflow, but anyone using such large numbers is being very silly
			c = NextChar();
		}

		if (expNegative)
		{
			twos -= exponent;
			fives -= exponent;
		}
		else
		{
			twos += exponent;
			fives += exponent;
		}
	}

	return true;
}

// Return true if the number fits in an int32 and wasn't specified with a decimal point or an exponent
// Note, we don't allow the value to be the most negative int32_t available
bool NumericConverter::FitsInInt32() const noexcept
{
	return !hadDecimalPoint && !hadExponent && twos == 0 && fives == 0 && lvalue <= (uint32_t)std::numeric_limits<int32_t>::max();
}

// Return true if the number fits in a uint32 and wasn't specified with a decimal point or an exponent
bool NumericConverter::FitsInUint32() const noexcept
{
	return !hadDecimalPoint && !hadExponent && (!isNegative || lvalue == 0) && twos == 0 && fives == 0;
}

// Given that FitsInInt32() returns true, return the number as an int32_t
int32_t NumericConverter::GetInt32() const noexcept
{
	return (isNegative) ? -(int32_t)lvalue : (int32_t)lvalue;
}

// Given that FitsInUint32() returns true, return the number as a uint32_t
uint32_t NumericConverter::GetUint32() const noexcept
{
	return lvalue;
}

// We need a table of double-precision constants, but we compile with -fsingle-precision-constant.
// This macro lets us use a double precision constant, by declaring it as a long double one and then casting it to double.
#define DOUBLE(_x) ((double)( _x ## L ))

static constexpr double inversePowersOfTen[] =
{
	DOUBLE(0.1),
	DOUBLE(0.01),
	DOUBLE(0.001),
	DOUBLE(0.0001),
	DOUBLE(0.00001),
	DOUBLE(0.000001),
	DOUBLE(0.0000001),
	DOUBLE(0.00000001),
	DOUBLE(0.000000001),
	DOUBLE(0.0000000001),
	DOUBLE(0.00000000001),
	DOUBLE(0.000000000001)
};


// Return the value as a float
float NumericConverter::GetFloat() const noexcept
{
	// The common cases are when we have zero to ~12 decimal places and no exponent, so optimise these
	double dvalue = (double)lvalue;
	const int tens = (twos < fives) ? twos : fives;
	if (tens != 0)
	{
		if (tens < 0 && tens >= -(int)(sizeof(inversePowersOfTen)/sizeof(inversePowersOfTen[0])))
		{
			dvalue *= inversePowersOfTen[-tens - 1];
		}
		else
		{
			dvalue *= pow(DOUBLE(10.0), tens);
		}
	}

	// Fives may be one greater than twos if the base was 10, and twos may be many more than fives
	if (fives > twos)
	{
		dvalue *= 5;
	}
	else
	{
		for (int n = fives; n < twos; ++n)
		{
			dvalue *= 2;
		}
	}

	return (isNegative) ? -(float)dvalue : (float)dvalue;
}

// Get the number of decimal digits that might be worth displaying after the decimal point when we print this.
// the caller must limit the return value to a sensible value for the float or double type used.
unsigned int NumericConverter::GetDigitsAfterPoint() const noexcept
{
	const int digits = (fives < twos) ? fives : twos;
	return (digits < 0) ? (unsigned int)-digits : 0;
}

// End
