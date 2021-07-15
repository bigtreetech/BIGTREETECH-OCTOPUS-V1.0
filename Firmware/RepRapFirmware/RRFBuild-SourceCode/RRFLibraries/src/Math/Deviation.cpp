/*
 * Deviation.cpp
 *
 *  Created on: 13 Jan 2020
 *      Author: David
 */

#include "Deviation.h"
#include "../General/SimpleMath.h"
#include <cmath>

Deviation::Deviation() noexcept : mean(0.0), deviationFromMean(0.0)
{
}

void Deviation::Set(float sumOfSquares, float sum, size_t numPoints) noexcept
{
	// Use: average sum of squares = average sum of squares of difference from mean + mean squared
	if (numPoints == 0)
	{
		mean = deviationFromMean = 0.0;
	}
	else
	{
		mean = sum/numPoints;
		const float square = sumOfSquares/numPoints - fsquare(mean);
		// 'square' can be slightly less than 0 due to rounding error
		deviationFromMean = (square <= 0) ? 0.0 : fastSqrtf(square);
	}
}

// End
