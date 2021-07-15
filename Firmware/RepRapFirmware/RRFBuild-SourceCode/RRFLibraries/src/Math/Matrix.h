/*
 * Matrix.h
 *
 *  Created on: 31 Mar 2015
 *      Author: David
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <cstddef>		// for size_t
#include "../General/ecv.h"

// Base class for matrices, allows us to write functions that work with any size matrix
template<class T> class MathMatrix
{
public:
	virtual size_t rows() const noexcept = 0;
	virtual size_t cols() const noexcept = 0;
	virtual T& operator() (size_t r, size_t c) noexcept = 0;
	virtual const T& operator() (size_t r, size_t c) const noexcept = 0;
	virtual ~MathMatrix() noexcept { }		// to keep Eclipse code analysis happy
};

// Fixed size matrix class
template<class T, size_t ROWS, size_t COLS> class FixedMatrix : public MathMatrix<T>
{
public:
	size_t rows() const noexcept override { return ROWS; }
	size_t cols() const noexcept override { return COLS; }

	// Indexing operator, non-const version
	T& operator() (size_t r, size_t c) noexcept override
	pre(r < ROWS; c < COLS)
	{
		return data[r][c];
	}

	// Indexing operator, const version
	const T& operator() (size_t r, size_t c) const noexcept override
	pre(r < ROWS; c < COLS)
	{
		return data[r][c];
	}

	void SwapRows(size_t i, size_t j, size_t numCols = COLS) noexcept
	pre(i < ROWS; j < ROWS)
	;

	bool GaussJordan(size_t numRows, size_t numCols) noexcept
	pre(numRows <= ROWS; numRows < numCols; numCols <= COLS)
	;

	// Return a pointer to a specified row, non-const version
	T* GetRow(size_t r) noexcept
	pre(r < ROWS)
	{
		return data[r];
	}

	// Return a pointer to a specified row, const version
	const T* GetRow(size_t r) const noexcept
	pre(r < ROWS)
	{
		return data[r];
	}

	// Set all elements to a specified value
	void Fill(T val) noexcept;

private:
	T data[ROWS][COLS];
};

// Swap 2 rows of a matrix
template<class T, size_t ROWS, size_t COLS> inline void FixedMatrix<T, ROWS, COLS>::SwapRows(size_t i, size_t j, size_t numCols) noexcept
{
	if (i != j)
	{
		for (size_t k = 0; k < numCols; ++k)
		{
			T temp = data[i][k];
			data[i][k] = data[j][k];
			data[j][k] = temp;
		}
	}
}

// Perform Gauss-Jordan elimination on a N x (N+M) matrix. Return true if successful, false if not possible.
template<class T, size_t ROWS, size_t COLS> bool FixedMatrix<T, ROWS, COLS>::GaussJordan(size_t numRows, size_t numCols) noexcept
{
	for (size_t i = 0; i < numRows; ++i)
	{
		// Swap the rows around for stable Gauss-Jordan elimination
		float vmax = fabsf(data[i][i]);
		for (size_t j = i + 1; j < numRows; ++j)
		{
			const float rmax = fabsf(data[j][i]);
			if (rmax > vmax)
			{
				SwapRows(i, j, numCols);
				vmax = rmax;
			}
		}

		// Use row i to eliminate the element in the ith column from previous and subsequent rows
		const T v = data[i][i];
		if (v == (T)0.0)
		{
			return false;
		}

		for (size_t j = 0; j < i; ++j)
		{
			const T factor = data[j][i]/v;
			data[j][i] = (T)0.0;
			for (size_t k = i + 1; k < numCols; ++k)
			{
				data[j][k] -= data[i][k] * factor;
			}
		}

		for (size_t j = i + 1; j < numRows; ++j)
		{
			const T factor = data[j][i]/v;
			data[j][i] = (T)0.0;
			for (size_t k = i + 1; k < numCols; ++k)
			{
				data[j][k] -= data[i][k] * factor;
			}
		}
	}

	for (size_t r = 0; r < numRows; ++r)
	{
		const T val = data[r][r];
		for (size_t c = numRows; c < numCols; ++c)
		{
			data[r][c] /= val;
		}
		data[r][r] = (T)1.0;
	}

	return true;
}

// Set all elements to a specified value
template<class T, size_t ROWS, size_t COLS>void FixedMatrix<T, ROWS, COLS>::Fill(T val) noexcept
{
	for (size_t i = 0; i < ROWS; ++i)
	{
		for (size_t j = 0; j < COLS; ++j)
		{
			data[i][j] = val;
		}
	}
}

#endif /* MATRIX_H_ */
