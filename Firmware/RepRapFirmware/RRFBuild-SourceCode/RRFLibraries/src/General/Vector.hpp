/*
 * Vector.hpp
 *
 * Created: 09/11/2014 09:50:41
 *  Author: David
 */


#ifndef SRC_GENERAL_VECTOR_H_
#define SRC_GENERAL_VECTOR_H_

#include "ecv.h"
#undef array
#undef result
#undef value
#include <cstddef>					// for size_t
#include "function_ref.h"

// Bounded vector class
template<class T, size_t N> class Vector
{
public:
	Vector() noexcept : filled(0) { }

	Vector(const size_t n, const T& fill) noexcept;

	bool Full() const noexcept { return filled == N; }

	constexpr size_t Capacity() const noexcept { return N; }

	size_t Size() const noexcept { return filled; }

	bool IsEmpty() const noexcept { return filled == 0; }

	const T& operator[](size_t index) const noexcept pre(index < N) { return storage[index]; }

	T& operator[](size_t index) noexcept pre(index < N) { return storage[index]; }

	bool Add(const T& x) noexcept;

	bool Add(const T* _ecv_array p, size_t n) noexcept;

	void Erase(size_t pos, size_t count = 1) noexcept;

	void Truncate(size_t pos) noexcept pre(pos <= filled);

	void Clear() noexcept { filled = 0; }

	const T* _ecv_array c_ptr() noexcept { return storage; }

	void Sort(function_ref<bool(T, T) /*noexcept*/ > sortfunc) noexcept;

	bool Replace(T oldVal, T newVal) noexcept;

	bool IterateWhile(function_ref<bool(T&, size_t) /*noexcept*/ > func, size_t startAt = 0) noexcept;

	bool IterateWhile(function_ref<bool(const T&, size_t) /*noexcept*/ > func, size_t startAt = 0) const noexcept;

protected:
	T storage[N];
	size_t filled;
};

template<class T, size_t N> Vector<T, N>::Vector(const size_t n, const T& fill) noexcept
	: filled(n)
{
	for (size_t i = 0; i < n; ++i)
	{
		storage[i] = fill;
	}
}

template<class T, size_t N> bool Vector<T, N>::Add(const T& x) noexcept
{
	if (filled < N)
	{
		storage[filled++] = x;
		return true;
	}
	return false;
}

template<class T, size_t N> bool Vector<T, N>::Add(const T* _ecv_array p, size_t n) noexcept
{
	while (n != 0)
	{
		if (filled == N)
		{
			return false;
		}
		storage[filled++] = *p++;
		--n;
	}
	return true;
}

// The sort function has to return true if the first element is greater than the second element
template<class T, size_t N> void Vector<T, N>::Sort(function_ref<bool(T, T) /*noexcept*/ > sortfunc) noexcept
{
	for (size_t i = 1; i < filled; ++i)
	{
		for (size_t j = 0; j < i; ++j)
		{
			if (sortfunc(storage[j], storage[i]))
			{
				T temp = storage[i];
				// Insert element i just before element j
				for (size_t k = i; k > j; --k)
				{
					storage[k] = storage[k - 1];
				}
				storage[j] = temp;
			}
		}
	}
}

template<class T, size_t N> void Vector<T, N>::Erase(size_t pos, size_t count) noexcept
{
	while (pos + count < filled)
	{
		storage[pos] = storage[pos + count];
		++pos;
	}
	if (pos < filled)
	{
		filled = pos;
	}
}

template<class T, size_t N> void Vector<T, N>::Truncate(size_t pos) noexcept
{
	if (pos < filled)
	{
		filled = pos;
	}
}

template<class T, size_t N> bool Vector<T, N>::Replace(T oldVal, T newVal) noexcept
{
	for (size_t i = 0; i < filled; ++i)
	{
		if (storage[i] == oldVal)
		{
			storage[i] = newVal;
			return true;
		}
	}
	return false;
}


template<class T, size_t N> bool Vector<T, N>::IterateWhile(function_ref<bool(T&, size_t) /*noexcept*/ > func, size_t startAt) noexcept
{
	const size_t totalElements = Size();
	if (startAt >= totalElements)
	{
		return true;
	}
	size_t count = 0;
	for (size_t i = startAt; i < totalElements; ++i)
	{
		if(!func(storage[i], count))
		{
			return false;
		}
		++count;
	}
	return true;
}

template<class T, size_t N> bool Vector<T, N>::IterateWhile(function_ref<bool(const T&, size_t) /*noexcept*/ > func, size_t startAt) const noexcept
{
	const size_t totalElements = Size();
	if (startAt >= totalElements)
	{
		return true;
	}
	size_t count = 0;
	for (size_t i = startAt; i < totalElements; ++i)
	{
		if(!func(storage[i], count))
		{
			return false;
		}
		++count;
	}
	return true;
}

#endif /* SRC_GENERAL_VECTOR_H_ */
