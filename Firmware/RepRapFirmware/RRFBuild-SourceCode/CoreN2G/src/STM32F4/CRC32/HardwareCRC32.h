#ifndef HARDWARECRC32_H
#define HARDWARECRC32_H
#include "stm32f4xx_hal_crc.h"

class HardwareCRC32
{
public:
    HardwareCRC32(CRC_TypeDef *Instance) noexcept;
    uint32_t CalcCRC32(const uint8_t val, const uint32_t crc) noexcept;
    uint32_t CalcCRC32(const uint8_t *vals, const size_t len, const uint32_t crc) noexcept;
private:
    uint32_t inline Calc(const uint8_t val, const uint32_t crc) noexcept __attribute__((always_inline));
    CRC_TypeDef *inst;
};

#endif