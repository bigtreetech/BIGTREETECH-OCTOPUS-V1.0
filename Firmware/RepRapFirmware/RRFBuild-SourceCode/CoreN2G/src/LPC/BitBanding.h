#ifndef BITBANDING_H
#define BITBANDING_H


//Defines from ARM Technical Support Knowledge Articles
#define BITBAND_SRAM_REF   0x20000000
#define BITBAND_SRAM_BASE  0x22000000
#define BITBAND_SRAM(a,b) ((BITBAND_SRAM_BASE + (a-BITBAND_SRAM_REF)*32 + (b*4)))  // Convert SRAM address

//Bitband for peripherals
#define BITBAND_PERI_REF   0x40000000
#define BITBAND_PERI_BASE  0x42000000
#define BITBAND_PERI(a,b) ((BITBAND_PERI_BASE + (a-BITBAND_PERI_REF)*32 + (b*4)))  // Convert PERI address

//LPC17xx Bitband memory map:
//  SRAM BB region: 0x20000000 - 0x200FFFFF (1MB)
//  SRAM BB alias:  0x22000000 - 0x23FFFFFF (32MB)

//  Periph BB region: 0x40000000 - 0x400FFFFF (1MB)
//  Periph BB alias:  0x42000000 - 0x43FFFFFF (32MB)

#define BITBAND_SRAM_REF_END    0x200FFFFF
#define BITBAND_PERI_REF_END    0x400FFFFF

inline volatile uint32_t *bb_alias_sram_dword(volatile uint32_t *ptr, uint8_t bit) noexcept
{
    const uint32_t p = (uint32_t) ptr;
    
    if( (uint32_t)p >= BITBAND_SRAM_REF && (uint32_t)p < BITBAND_SRAM_REF_END)
    {
        return (volatile uint32_t *)BITBAND_SRAM(p, bit);
    }
    return NULL;
}
 

inline volatile uint32_t *bb_alias_periph_dword(volatile uint32_t *ptr, uint8_t bit) noexcept
{
    const uint32_t p = (uint32_t) ptr;
    
    if( (uint32_t)p >= BITBAND_PERI_REF && (uint32_t)p < BITBAND_PERI_REF_END)
    {
        return (volatile uint32_t *)BITBAND_PERI(p, bit);
    }
    return NULL;
}



#endif // BITBANDING_H
