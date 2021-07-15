/*
 * Cache.h
 *
 *  Created on: 22 Nov 2019
 *      Author: David
 */

#ifndef SRC_CACHE_H_
#define SRC_CACHE_H_

#include <CoreIO.h>

namespace Cache
{
	void Init() noexcept;
	void Enable() noexcept;
	bool Disable() noexcept;			// disable the cache, return true if it was enabled
	void Flush(const volatile void *start, size_t length) noexcept;
	void Invalidate(const volatile void *start, size_t length) noexcept;

	inline void FlushBeforeDMAReceive(const volatile void *start, size_t length) noexcept { Flush(start, length); }
	inline void InvalidateAfterDMAReceive(const volatile void *start, size_t length) noexcept { Invalidate(start, length); }
	inline void FlushBeforeDMASend(const volatile void *start, size_t length) noexcept { Flush(start, length); }

#if SAM4E || SAME5x
	uint32_t GetHitCount() noexcept;
#endif
};

// Entry points that can be called from ASF C code
extern "C" void CacheFlushBeforeDMAReceive(const volatile void *start, size_t length) noexcept;
extern "C" void CacheInvalidateAfterDMAReceive(const volatile void *start, size_t length) noexcept;
extern "C" void CacheFlushBeforeDMASend(const volatile void *start, size_t length) noexcept;

#if SAM4S || SAMC21 || STM32F4 || LPC17xx

// These processors have no cache
inline void Cache::Init() noexcept { __DSB(); }
inline void Cache::Enable() noexcept { }
inline bool Cache::Disable() noexcept { return false; }
inline void Cache::Flush(const volatile void *start, size_t length) noexcept { __DSB(); }
inline void Cache::Invalidate(const volatile void *start, size_t length) noexcept { __DSB(); }

#elif SAM4E || SAME5x

# if SAME5x
// The SAME5x version of this cache controller allows us to disable data caching
// Caching instructions only increases the time taken by the ADC ISR from 700ns to 750ns, so we don't do it
#  define	CACHE_INSTRUCTIONS_ONLY		(0)
# endif

# if SAME5x && CACHE_INSTRUCTIONS_ONLY
inline void Cache::Invalidate(const volatile void *start, size_t length) noexcept { __DSB(); }
# endif

// The SAM4E and SAME5x cache is write-through, so no need to flush it
inline void Cache::Flush(const volatile void *start, size_t length) noexcept { __DSB(); }

#endif

#endif /* SRC_CACHE_H_ */
