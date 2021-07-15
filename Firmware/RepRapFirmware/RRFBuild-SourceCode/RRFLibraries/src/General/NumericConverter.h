/*
 * NumericConverter.h
 *
 *  Created on: 26 Apr 2020
 *      Author: David
 */

#ifndef SRC_GENERAL_NUMERICCONVERTER_H_
#define SRC_GENERAL_NUMERICCONVERTER_H_

#include <cstdint>
#include "function_ref.h"

// Class to read fixed and floating point numbers
class NumericConverter
{
public:
	// Values that may be or'ed together in the options parameter to Accumulate
	typedef uint8_t OptionsType;
	static constexpr OptionsType AcceptOnlyUnsignedDecimal = 0;						// what it says
	static constexpr OptionsType AcceptNegative = 0x01;								// allow a leading plus or minus sign (else not allowed)
	static constexpr OptionsType AcceptFloat = 0x02;								// allow decimal floating point numbers (else integer only)
	static constexpr OptionsType AcceptHex = 0x04;									// allow 0x followed by hex digits, or 0B follows by binary digits
	static constexpr OptionsType DefaultHex = 0x08;									// always interpret the number as in hex. Not compatible with AcceptFloat.
	static constexpr OptionsType AcceptSignedFloat = AcceptNegative | AcceptFloat;

	NumericConverter() noexcept {}
	bool Accumulate(char c, OptionsType options, function_ref<char() /*noexcept*/> NextChar) noexcept;
	bool FitsInInt32() const noexcept;
	bool FitsInUint32() const noexcept;
	int32_t GetInt32() const noexcept;
	uint32_t GetUint32() const noexcept;
	float GetFloat() const noexcept;
	unsigned int GetDigitsAfterPoint() const noexcept;
	bool IsNegative() const noexcept { return isNegative; }

private:
	uint32_t lvalue;
	int fives;
	int twos;
	bool hadDecimalPoint;
	bool hadExponent;
	bool isNegative;
};

#endif /* SRC_GENERAL_NUMERICCONVERTER_H_ */
