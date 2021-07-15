/*
 * Deviation.h
 *
 *  Created on: 13 Jan 2020
 *      Author: David
 */

#ifndef SRC_MATH_DEVIATION_H_
#define SRC_MATH_DEVIATION_H_

#include <cstdlib>

// Class to represent a deviation of a set of points from the ideal
class Deviation
{
public:
	Deviation() noexcept;

	void Set(float sumOfSquares, float sum, size_t numPoints) noexcept;

	float GetMean() const noexcept { return mean; }
	float GetDeviationFromMean() const noexcept { return deviationFromMean; }

private:
	float mean;
	float deviationFromMean;
};

#endif /* SRC_MATH_DEVIATION_H_ */
