/*
 * Portability.h
 *
 *  Created on: 30 Aug 2019
 *      Author: David
 */

#ifndef SRC_GENERAL_PORTABILITY_H_
#define SRC_GENERAL_PORTABILITY_H_

#include <cstdint>
#include <cstddef>

// Functions to allow for processor differences, e.g. endianness and alignment requirements

// ARM Cortex M0 doesn't support unaligned memory accesses, neither does SAME70 when accessing non-cached memory

static inline void copy4bytes(const void *s, void *d) noexcept
{
	const char *sc = (const char*)s;
	char *dc = (char*)d;
	dc[0] = sc[0];
	dc[1] = sc[1];
	dc[2] = sc[2];
	dc[3] = sc[3];
}

// Load a uint32 from unaligned memory in little endian format
static inline uint32_t LoadLE32(const void *p) noexcept
{
	const uint8_t * const pp = (const uint8_t *)p;
	return ((uint32_t)pp[3] << 24) | ((uint32_t)pp[2] << 16) | ((uint32_t)pp[1] << 8) | pp[0];
}

// Load a uint16 from unaligned memory in little endian format
static inline uint16_t LoadLE16(const void *p) noexcept
{
	const uint8_t * const pp = (const uint8_t *)p;
	return ((uint16_t)pp[1] << 8) | pp[0];
}

// Load a float from unaligned memory in little endian format
static inline float LoadLEFloat(const void *p) noexcept
{
	float rslt;
	copy4bytes(p, &rslt);
	return rslt;
}

// Store a uint32 into unaligned memory in little endian format
static inline void StoreLE32(void *p, uint32_t val) noexcept
{
	uint8_t * const pp = (uint8_t *)p;
	pp[0] = (uint8_t)val;
	pp[1] = (uint8_t)(val >> 8);
	pp[2] = (uint8_t)(val >> 16);
	pp[3] = (uint8_t)(val >> 24);
}

// Store a uint16 into unaligned memory in little endian format
static inline void StoreLE16(void *p, uint16_t val) noexcept
{
	uint8_t * const pp = (uint8_t *)p;
	pp[0] = (uint8_t)val;
	pp[1] = (uint8_t)(val >> 8);
}

// Store a float into unaligned memory in little endian format
static inline void StoreLEFloat(void *p, const float val) noexcept
{
	copy4bytes(&val, p);
}

// Load a uint32 from unaligned memory in big endian format
static inline uint32_t LoadBE32(const void *p) noexcept
{
	const uint8_t* const bp = (const uint8_t*)p;
	return ((uint32_t)bp[0] << 24) | ((uint32_t)bp[1] << 16) | ((uint32_t)bp[2] << 8) | (uint32_t)bp[3];
}

// Load a uint16 from unaligned memory in big endian format
static inline uint16_t LoadBE16(const void *p) noexcept
{
	const uint8_t* const bp = (const uint8_t*)p;
	return ((uint16_t)bp[0] << 8) | (uint16_t)bp[1];
}

// Store a uint32 into unaligned memory in big endian format
static inline void StoreBE32(void *p, uint32_t val) noexcept
{
	uint8_t* const bp = (uint8_t*)p;
	bp[0] = (uint8_t)(val >> 24);
	bp[1] = (uint8_t)(val >> 16);
	bp[2] = (uint8_t)(val >> 8);
	bp[3] = (uint8_t)val;
}

// Store a uint16 into unaligned memory in big endian format
static inline void StoreBE16(void *p, uint16_t val) noexcept
{
	uint8_t* const bp = (uint8_t*)p;
	bp[0] = (uint8_t)(val >> 8);
	bp[1] = (uint8_t)val;
}

// Template class to declare members as unaligned so as to avoid unaligned memory accesses when reading or writing them
template<class T> class Unaligned
{
public:
	Unaligned(const Unaligned<T>& arg) noexcept;
	Unaligned(const T& arg) noexcept;

	Unaligned<T>& operator=(const T& rhs) noexcept;
	Unaligned<T>& operator=(const Unaligned<T>& rhs) noexcept;

	T Get() const noexcept;

private:
	T val;
};

template<class T> Unaligned<T>::Unaligned(const Unaligned<T>& arg) noexcept
{
	char *p = &arg.val, *q = &val;
	for (size_t i = 0; i < sizeof(T); ++i)
	{
		*q++ = *p++;
	}
}

template<class T> Unaligned<T>::Unaligned(const T& arg) noexcept
{
	char *p = &arg, *q = &val;
	for (size_t i = 0; i < sizeof(T); ++i)
	{
		*q++ = *p++;
	}
}

template<class T> Unaligned<T>& Unaligned<T>::operator=(const T& rhs) noexcept
{
	char *p = &rhs, *q = &val;
	for (size_t i = 0; i < sizeof(T); ++i)
	{
		*q++ = *p++;
	}
	return *this;
}

template<class T> Unaligned<T>& Unaligned<T>::operator=(const Unaligned<T>& rhs) noexcept
{
	char *p = &rhs.val, *q = &val;
	for (size_t i = 0; i < sizeof(T); ++i)
	{
		*q++ = *p++;
	}
	return *this;
}

template<class T> T Unaligned<T>::Get() const noexcept
{
	T ret;
	char *p = &val, *q = &ret;
	for (size_t i = 0; i < sizeof(T); ++i)
	{
		*q++ = *p++;
	}
	return ret;
}

// Pointer to unaligned object
template<class T> class UnalignedPointer
{
public:
	UnalignedPointer(char* pp) noexcept : p(pp) { }

	Unaligned<T>& operator*() noexcept { return *reinterpret_cast<Unaligned<T>*>(p); }

private:
	char *p;
};

#endif /* SRC_GENERAL_PORTABILITY_H_ */
