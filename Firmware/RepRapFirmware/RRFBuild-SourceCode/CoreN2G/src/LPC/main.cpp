
#define ARDUINO_MAIN

#include "CoreImp.h"
#include <FreeRTOS.h>
#include "systick.h"
#include <syscalls.h>
extern "C" void UrgentInit();
extern "C" void __libc_init_array(void);
extern void init( void ) noexcept;
extern char _end;								// defined by the linker script
extern char _estack;


//How much memory to reserve when allocating the heap space.
//Stack size + 256 bytes pagesize for any other code that uses malloc
constexpr uint32_t reserveMemory = SystemStackSize + (256);

__attribute__ ((used)) uint8_t *ucHeap;


// these are defined in the linker script
extern uint8_t __AHB0_block_start;
extern uint8_t __AHB0_dyn_start;
extern uint8_t __AHB0_end;

extern "C" char *sbrk(int i);

int main( void )
{

    SystemInit();
    
    // zero the data sections in AHB0 SRAM
    memset(&__AHB0_block_start, 0, &__AHB0_dyn_start - &__AHB0_block_start);

    //Determine the size of free memory in Main RAM
    const char * const ramend = (const char *)&_estack;
    const char * const heapend = sbrk(0);
    const uint32_t freeRam = (ramend - heapend) - reserveMemory;
    ucHeap = (uint8_t *) sbrk(freeRam); //allocate the memory so any other code using malloc etc wont corrupt our heapregion
    
    //Determine the size of free memory in AHB RAM
    const uint32_t ahb0_free = (uint32_t)&__AHB0_end - (uint32_t)&__AHB0_dyn_start;

    
    //Setup the FreeRTOS Heap5 management to use for Dynamic Memory
    //Heap5 allows us to span heap memory across non-contigious blocks of memory.
    const HeapRegion_t xHeapRegions[] =
    {
        { ( uint8_t * ) ucHeap, freeRam }, //ucHeap will be placed in main memory
        { ( uint8_t * ) &__AHB0_dyn_start, ahb0_free }, //fill the rest of AHBRAM
        { NULL, 0 } /* Terminates the array. */
    };
    /* Pass the array into vPortDefineHeapRegions(). */
    vPortDefineHeapRegions( xHeapRegions );
    
    //now init all static constructors etc ...
    __libc_init_array();
 
    
    init(); // Defined in variant.cpp

    SysTick_Init(); 
    
    #if defined(__MBED__)
        //configure UART0 pins for MBED
        GPIO_PinFunction(P0_2, PINSEL_FUNC_1);
        GPIO_PinFunction(P0_3, PINSEL_FUNC_1);
    #endif
    AppInit();
    AppMain();

    return 0;
}
