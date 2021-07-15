/*
 * SimpleMath.h
 *
 *  Created on: 28 May 2020
 *      Author: David
 */

#ifndef SRC_GENERAL_SIMPLEMATH_H_
#define SRC_GENERAL_SIMPLEMATH_H_

#include <cstdint>
#include <cmath>

template<class X> inline constexpr X min(X _a, X _b) noexcept
{
	return (_a < _b) ? _a : _b;
}

template<class X> inline constexpr X max(X _a, X _b) noexcept
{
	return (_a > _b) ? _a : _b;
}

// Specialisations for float and double to handle NaNs properly
template<> inline constexpr float min(float _a, float _b) noexcept
{
	return (std::isnan(_a) || _a < _b) ? _a : _b;
}

template<> inline constexpr float max(float _a, float _b) noexcept
{
	return (std::isnan(_a) || _a > _b) ? _a : _b;
}

template<> inline constexpr double min(double _a, double _b) noexcept
{
	return (std::isnan(_a) || _a < _b) ? _a : _b;
}

template<> inline constexpr double max(double _a, double _b) noexcept
{
	return (std::isnan(_a) || _a > _b) ? _a : _b;
}

// Note that constrain<float> will return NaN for a NaN input because of the way we define min<float> and max<float>
template<class T> inline constexpr T constrain(T val, T vmin, T vmax) noexcept
{
	return max<T>(min<T>(val, vmax), vmin);
}

inline constexpr float fsquare(float arg) noexcept
{
	return arg * arg;
}

inline constexpr double dsquare(double arg) noexcept
{
	return arg * arg;
}

inline constexpr uint64_t isquare64(int32_t arg) noexcept
{
	return (uint64_t)((int64_t)arg * arg);
}

inline constexpr uint64_t isquare64(uint32_t arg) noexcept
{
	return (uint64_t)arg * arg;
}

// Find the lowest set bit. Returns the lowest set bit number, undefined if no bits are set.
// GCC provides intrinsics, but unhelpfully they are in terms of int, long and long long instead of uint32_t, uint64_t etc.
inline unsigned int LowestSetBitNumber(unsigned int val) noexcept
{
	return (unsigned int)__builtin_ctz(val);
}

static_assert(sizeof(uint32_t) == sizeof(unsigned long));
inline unsigned int LowestSetBitNumber(unsigned long val) noexcept
{
	return (unsigned int)__builtin_ctzl(val);
}

inline unsigned int LowestSetBitNumber(unsigned long long val) noexcept
{
	return (unsigned int)__builtin_ctzll(val);
}

inline constexpr bool Xor(bool a, bool b) noexcept
{
	return (a) ? !b : b;
}

inline constexpr bool XNor(bool a, bool b) noexcept
{
	return (a) ? b : !b;
}

// Built-in square root function that just uses the ARM floating point instruction
// This differs from __builtin_sqrtf by not checking for a negative operand, which is supposed to set error codes
inline float fastSqrtf(float f) noexcept
{
#if (defined(__FPU_USED) && __FPU_USED) || (defined (__VFP_FP__) && !defined(__SOFTFP__))
	float ret;
	asm("vsqrt.f32 %0,%1" : "=t" (ret) : "t" (f));
	return ret;
#else
	return sqrtf(f);
#endif
}

// Macro to give us the number of elements in an array
#ifndef ARRAY_SIZE
# define ARRAY_SIZE(_x)	(sizeof(_x)/sizeof((_x)[0]))
#endif

// Macro to give us the highest valid index into an array i.e. one less than the size
#define ARRAY_UPB(_x)	(ARRAY_SIZE(_x) - 1)


#endif /* SRC_GENERAL_SIMPLEMATH_H_ */
