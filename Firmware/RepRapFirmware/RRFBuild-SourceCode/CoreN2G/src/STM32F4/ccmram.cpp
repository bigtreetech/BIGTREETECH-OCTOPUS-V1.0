#include "CoreImp.h"

// extern char _sccmram;					// defined in linker script
// extern char _eccmram;					// defined in linker script
// extern char _ccmramend;					// defined in linker script

// const char *ccmHeapLimit = &_ccmramend;
// char *ccmHeapTop = &_eccmram;

// [[noreturn]] void OutOfMemoryHandler() noexcept;

// /**
//  * \brief Allocate memory permanently. In multi-threaded environments, take the malloc mutex before calling this.
//  */
// void *CoreAllocCCMRAMPermanent(size_t sz, std::align_val_t align) noexcept
// {
// 	char * const newHeapLimit = reinterpret_cast<char *>(reinterpret_cast<uint32_t>(ccmHeapLimit - sz) & ~((uint32_t)align - 1));
// 	if (newHeapLimit < ccmHeapTop)
// 	{
// 		OutOfMemoryHandler();
// 	}
// 	ccmHeapLimit = newHeapLimit;
// 	return newHeapLimit;
// }
