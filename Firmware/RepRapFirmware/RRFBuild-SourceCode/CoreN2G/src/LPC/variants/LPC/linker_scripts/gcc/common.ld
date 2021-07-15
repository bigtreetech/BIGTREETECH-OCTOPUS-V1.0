
/* Linker script to place sections and symbol values. Should be used together
 * with other linker script that defines memory regions FLASH and RAM.
 * It references following symbols, which must be defined in code:
 *   Reset_Handler : Entry of reset handler
 * 
 * It defines following symbols, which code can use without definition:
 *   __exidx_start
 *   __exidx_end
 *   __etext
 *   __data_start__
 *   __preinit_array_start
 *   __preinit_array_end
 *   __init_array_start
 *   __init_array_end
 *   __fini_array_start
 *   __fini_array_end
 *   __data_end__
 *   __bss_start__
 *   __bss_end__
 *   __end__
 *   end
 *   __HeapLimit
 *   __StackLimit
 *   __StackTop
 *   __stack
 *GROUP(libgcc.a libg.a libc.a  libm.a  libnosys.a )
 */
GROUP(libgcc.a 
      libg.a 
      libc.a  
      libm.a  
      libnosys.a )

ENTRY(Reset_Handler)



SECTIONS
{

	/* Code can explicitly ask for data to be 
       placed in these higher RAM banks where
       they will be left uninitialized. 
    */
    .AHBSRAM0 (NOLOAD):
    {
        Image$$RW_IRAM2$$Base = . ;
        PROVIDE(__AHB0_block_start = .);
        *(AHBSRAM0)

        /* Manually define variables to be also placed into AHB RAM */
        *(.bss.*DataTransfer*)

        *(.bss.reprap)
        *(.bss._*heaterTask)
        *(.bss._*mainTask)
        *(.bss.*IdleTaskStack)
        *(.bss.*TimerTaskStack)
        *(.bss.*tcpPlusTask)
        *(.bss._time_locale)
        *(.bss.*Mutex*)
        *(.bss.*Queue*)
        *(.bss.*TCB)
        *(.bss.xNetworkBuffers)
        *(.bss.*networkTask)
        *(.bss.*descriptors*)
        *(.bss.*HttpResponder*)
        *(.bss.*emacTask)
        *(.bss.*idleTask)
        *(.bss.xARPCache)
        *(.bss.xDHCPData)
        *(.bss.*assembleConfigDescriptor*)
        *(.bss.*bufferIn)
        *(.bss.*bufferOut)
        *(.bss.*infoParser)
        *(.bss.*info)
        *(.bss.*files)
	
        Image$$RW_IRAM2$$ZI$$Limit = .;
        PROVIDE(__AHB0_dyn_start = .);
        PROVIDE(__AHB0_end = ORIGIN(AHB_RAM) + LENGTH(AHB_RAM));
		
    } > AHB_RAM

    .text :
    {
	    _sfixed = .;
        KEEP(*(.isr_vector))
        *(.text*)

       KEEP(*freertos*/tasks.o(.rodata*)) /* FreeRTOS Debug Config */

        KEEP(*(.init))
        KEEP(*(.fini))

        /* .ctors */
        *crtbegin.o(.ctors)
        *crtbegin?.o(.ctors)
        *(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
        *(SORT(.ctors.*))
        *(.ctors)

        /* .dtors */
        *crtbegin.o(.dtors)
        *crtbegin?.o(.dtors)
        *(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
        *(SORT(.dtors.*))
        *(.dtors)

        *(.rodata*)

        KEEP(*(.eh_frame*))
    } > FLASH

    .ARM.extab : 
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > FLASH

    __exidx_start = .;
    .ARM.exidx :
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > FLASH
    __exidx_end = .;

    __etext = .;
    __sidata = __etext;
        
    .data : AT (__etext)
    {
        __data_start__ = .;
        *(vtable)
        *(.data*)

        . = ALIGN(4);
        /* preinit data */
        PROVIDE (__preinit_array_start = .);
        KEEP(*(.preinit_array))
        PROVIDE (__preinit_array_end = .);

        . = ALIGN(4);
        /* init data */
        PROVIDE (__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE (__init_array_end = .);


        . = ALIGN(4);
        /* finit data */
        PROVIDE (__fini_array_start = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
        PROVIDE (__fini_array_end = .);

        . = ALIGN(4);
        /* All data end */
        __data_end__ = .;

    } > RAM

    .bss ALIGN(4):
    {
        __bss_start__ = .;
        
        /* 
        	Ensure that xDelayedTaskList1 is immediately after pxReadyTasksLists
		   	so that FreeRTOS Priorities is detected in pyOCD and can enable thread debugging 
		*/
        KEEP(*(.bss.pxReadyTasksLists))
        KEEP(*(.bss.xDelayedTaskList1))
        KEEP(*(.bss.xDelayedTaskList2))

        *(.bss*)
        *(COMMON)
        __bss_end__ = .;
    } > RAM
     . = ALIGN(4);
    _end = . ;
    end = _end;

/*    .heap : {
       __heap_start__ = heap;

       KEEP(*(.heap))
       end = __heap_start__;
        __heap_end__ = .;
        _end = __heap_end__;
        __HeapLimit = __heap_end__ - __heap_start__;
    } > RAM
*/
    /* .stack_dummy section doesn't contains any symbols. It is only
     * used for linker to calculate size of stack sections, and assign
     * values to stack symbols later */
    .stack_dummy :
    {
        *(.stack)
    } > RAM

    /* Set stack top to end of RAM, and stack limit move down by
     * size of stack_dummy section */
    __StackTop = ORIGIN(RAM) + LENGTH(RAM);
    __StackLimit = __StackTop - SIZEOF(.stack_dummy);
    PROVIDE(__stack = __StackTop);
    PROVIDE(_estack = __StackTop);    
    /* Check if data + heap + stack exceeds RAM limit */
    /*ASSERT(__StackLimit >= __HeapLimit, "region RAM overflowed with
     * stack")*/



	/* Check if everything fits into FLASH */
    __dataSectionSize = __data_end__ - __data_start__;
    __textSectionSize = __etext - ORIGIN(FLASH);
    ASSERT( __dataSectionSize + __textSectionSize <= LENGTH(FLASH), "FLASH overflowed")



}





