//SD

#ifndef NVMEMULATION_H_
#define NVMEMULATION_H_

#include "Core.h"
#include "iap.h"


void NVMEmulationRead(void *data, uint32_t dataLength);
bool NVMEmulationErase();
bool NVMEmulationWrite(const void *data, uint32_t dataLength);

//Compatibility
inline void EraseAndReset(){};


#endif /* SOFTWARERESETDATA_H_ */
