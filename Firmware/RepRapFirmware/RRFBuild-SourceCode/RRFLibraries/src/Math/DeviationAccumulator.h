/*
 * DeviationAccumulator.h
 *
 *  Created on: 9 Nov 2020
 *      Author: David
 */

#ifndef SRC_MATH_DEVIATIONACCUMULATOR_H_
#define SRC_MATH_DEVIATIONACCUMULATOR_H_

// Class to represent an accumulator for calculating deviation of a set of points from the ideal
class DeviationAccumulator
{
public:
	DeviationAccumulator() noexcept;

	void Clear() noexcept;
	void Add(float value) noexcept;

	float GetMean() const noexcept { return (numValues == 0) ? 0.0 : sum/(float)numValues; }
	float GetDeviation() const noexcept;
	unsigned int GetNumSamples() const noexcept { return numValues; }
	bool DeviationFractionWithin(float f) const noexcept;

private:
	unsigned int numValues;
	float sum;
	float sumOfSquares;
};

#endif /* SRC_MATH_DEVIATIONACCUMULATOR_H_ */
