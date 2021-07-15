/*
 * Encapsulate the STM32F4 hardware CRC32 unit
 * Author: GA
 * 
 * The unit does not have a simple way to establish the initial seed value (other than resetting it)
 * so to allow use with multiple buffers we need to adjust things.
 * Based on this post: https://community.st.com/s/question/0D50X00009XkZjC/stm32f4-crc-preload-crcdr
 */


#include "HardwareCRC32.h"
#include "stm32f4xx_hal_crc.h"
#include "stm32f4xx_hal_rcc_ex.h"

// Original code
#if 0
void
reset() 
{ cr = 1; }


void
write( u32 data ) 
{ dr = rbit( data ); }


u32 read() {
return~rbit( dr ); }

u32 calc( u8 data, u32 crc ) // single byte
{
crc = ~crc ^ data;
reset();
write( ~( crc << 24 ) );
return ( crc >> 8 ) ^ read();
}


u32 calc(size_t nwords, u32 wdata[], u32 crc = 0 ) // wordwise
{
if ( nwords == 0 )
return crc;
reset();
write( wdata[0] ^ crc );
for(size_t i = 1; i != nwords; i++ )
write( wdata[i] );
return read();
}


u32 calc(size_t nbytes, u8 data[], u32 crc = 0 )// general
{
if ( nbytes >= 4 ) {
// process 0-3 bytes to make pointer word-aligned
size_t align = -(size_t)data & 3;
nbytes -= align;
while ( align-- )
crc = calc( *data++, crc );
// process bulk of data
size_t nwords = nbytes >> 2;
crc = calc( nwords, (u32 *)data, crc );
data += nwords << 2;
nbytes &= 3;
}
// leftover bytes
while ( nbytes-- )
crc = calc( *data++, crc );
return crc;
}
#endif

static inline uint32_t rbit(uint32_t v) noexcept
{
	uint32_t rslt;
	asm("rbit %0,%1" : "=r" (rslt) : "r" (v));
	return rslt;
}

// Only a single instance of the CRC engine, define it here
HardwareCRC32 HWCRC32(CRC);

HardwareCRC32::HardwareCRC32(CRC_TypeDef *Instance) noexcept : inst(Instance)
{
    // make sure the hardware has power
    __HAL_RCC_CRC_CLK_ENABLE();
}

uint32_t inline HardwareCRC32::Calc(const uint8_t val, const uint32_t crc) noexcept
{
    uint32_t res = ~crc ^ val;
    inst->CR |= CRC_CR_RESET;
    inst->DR = rbit(~(res << 24));
    return (res >> 8) ^ ~rbit(inst->DR);
}


uint32_t HardwareCRC32::CalcCRC32(const uint8_t val, const uint32_t crc) noexcept
{
    return Calc(val, crc);
}


uint32_t HardwareCRC32::CalcCRC32(const uint8_t *vals, const size_t len, const uint32_t crc) noexcept
{
    uint32_t res = crc;
    size_t nbytes = len;
    if (nbytes >= 4)
    {
        // more than one word
        size_t align = -(size_t)vals & 3;
        nbytes -= align;
        // Do unaligned starting bytes
        while (align--)
            res = Calc(*vals++, res);
        // do bulk
        size_t nwords = nbytes >> 2;
        if (nwords > 0)
        {
            uint32_t *wdata = (uint32_t *)vals;
            inst->CR |= CRC_CR_RESET;
            inst->DR = rbit(wdata[0] ^ res);
            for(size_t i = 1; i < nwords; i++)
                inst->DR = rbit(wdata[i]);
            res = ~rbit(inst->DR);
            nbytes &= 3;
            vals += nwords << 2;
        }
    }
    // Do any final bytes
    while (nbytes--)
        res = Calc(*vals++, res);
    return res;
}
