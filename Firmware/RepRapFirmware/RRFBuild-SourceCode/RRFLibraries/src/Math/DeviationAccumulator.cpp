/*
 * DeviationAccumulator.cpp
 *
 *  Created on: 9 Nov 2020
 *      Author: David
 */

#include "DeviationAccumulator.h"
#include "../General/SimpleMath.h"

DeviationAccumulator::DeviationAccumulator() : numValues(0), sum(0.0), sumOfSquares(0.0)
{
}

void DeviationAccumulator::Clear() noexcept
{
	numValues= 0;
	sum = sumOfSquares = 0.0;
}

void DeviationAccumulator::Add(float value) noexcept
{
	++numValues;
	sum += value;
	sumOfSquares += fsquare(value);
}

float DeviationAccumulator::GetDeviation() const noexcept
{
	if (numValues == 0)
	{
		return 0.0;
	}
	const float square = sumOfSquares/numValues - fsquare(sum/numValues);
	// 'square' can be slightly less than 0 due to rounding error if all the values added were equal
	return (square <= 0) ? 0.0 : fastSqrtf(square);
}

// Return true if the deviation is within the specified fraction of the value. Only valid for positive values e.g. times.
bool DeviationAccumulator::DeviationFractionWithin(float f) const noexcept
{
	return GetDeviation() <= f * GetMean();
}

// End
