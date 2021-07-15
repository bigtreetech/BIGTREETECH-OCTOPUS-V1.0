/******************************************************************************
 * @file:
 * @purpose: CMSIS Cortex-M3 Core Device Startup File
 * @version: V1.01
 * @date:    4. Feb. 2009
 *----------------------------------------------------------------------------
 *
 * Copyright (C) 2009 ARM Limited. All rights reserved.
 *
 * ARM Limited (ARM) is supplying this software for use with Cortex-Mx
 * processor based microcontrollers.  This file can be freely distributed
 * within development tools that are supporting such ARM based processors.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/
#include "chip.h"
#include "core_cm3.h"

//*****************************************************************************
//
// This is the code that gets called when the processor receives an unexpected
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************

void OtherFault_Handler(void);// defined in RRF

void Default_Handler(void)
{
    //rather then got into a while(1) loop, call the OtherFault_Handler which is
    //already handled in RRF to produce a SoftwareReset with a stack dump.
    OtherFault_Handler();
}


//*****************************************************************************
//
// Forward declaration of the default fault handlers.
//
//*****************************************************************************

/* System exception vector handler */
void Reset_Handler      (void) __attribute__((__interrupt__));
void NMI_Handler        (void) __attribute__ ((weak));                                   /* NMI Handler */
void HardFault_Handler  (void) __attribute__ ((weak));                                   /* Hard Fault Handler */
void MemManage_Handler  (void) __attribute__ ((weak));                                   /* MPU Fault Handler */
void BusFault_Handler   (void) __attribute__ ((weak));                                   /* Bus Fault Handler */
void UsageFault_Handler (void) __attribute__ ((weak));                                   /* Usage Fault Handler */
void SVC_Handler        (void) __attribute__ ((weak));                                   /* SVCall Handler */
void DebugMon_Handler   (void) __attribute__ ((weak));                                   /* Debug Monitor Handler */
void PendSV_Handler     (void) __attribute__ ((weak));                                   /* PendSV Handler */
void SysTick_Handler    (void) __attribute__ ((weak));                                   /* SysTick Handler */

/* External interrupt vector handler */
void WDT_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));         /* Watchdog Timer */
void TIMER0_IRQHandler  (void) __attribute__ ((weak, alias("Default_Handler")));         /* Timer0 */
void TIMER1_IRQHandler  (void) __attribute__ ((weak, alias("Default_Handler")));         /* Timer1 */
void TIMER2_IRQHandler  (void) __attribute__ ((weak, alias("Default_Handler")));         /* Timer2 */
void TIMER3_IRQHandler  (void) __attribute__ ((weak, alias("Default_Handler")));         /* Timer3 */
void UART0_IRQHandler   (void) __attribute__ ((weak, alias("Default_Handler")));         /* UART0 */
void UART1_IRQHandler   (void) __attribute__ ((weak, alias("Default_Handler")));         /* UART1 */
void UART2_IRQHandler   (void) __attribute__ ((weak, alias("Default_Handler")));         /* UART2 */
void UART3_IRQHandler   (void) __attribute__ ((weak, alias("Default_Handler")));         /* UART3 */
void PWM1_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));         /* PWM1 */
void I2C0_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));         /* I2C0 */
void I2C1_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));         /* I2C1 */
void I2C2_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));         /* I2C2 */
void SPI_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));         /* SPI */
void SSP0_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));         /* SSP0 */
void SSP1_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));         /* SSP1 */
void PLL0_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));         /* PLL0 (Main PLL) */
void RTC_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));         /* Real Time Clock */
void EINT0_IRQHandler   (void) __attribute__ ((weak, alias("Default_Handler")));         /* External Interrupt 0 */
void EINT1_IRQHandler   (void) __attribute__ ((weak, alias("Default_Handler")));         /* External Interrupt 1 */
void EINT2_IRQHandler   (void) __attribute__ ((weak, alias("Default_Handler")));         /* External Interrupt 2 */
void EINT3_IRQHandler   (void) __attribute__ ((weak, alias("Default_Handler")));         /* External Interrupt 3 */
void ADC_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));         /* A/D Converter */
void BOD_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));         /* Brown Out Detect */
void USB_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));         /* USB */
void CAN_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));         /* CAN */
void DMA_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));         /* GP DMA */
void I2S_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));         /* I2S */
void ENET_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));         /* Ethernet */
void RIT_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));         /* Repetitive Interrupt Timer */
void MCPWM_IRQHandler   (void) __attribute__ ((weak, alias("Default_Handler")));         /* Motor Control PWM */
void QEI_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));         /* Quadrature Encoder Interface */
void PLL1_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));         /* PLL1 (USB PLL) */



/* Exported types --------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
extern unsigned long __etext;
extern unsigned long __sidata;		/* start address for the initialization values of the .data section. defined in linker script */
extern unsigned long __data_start__;		/* start address for the .data section. defined in linker script */
extern unsigned long __data_end__;		/* end address for the .data section. defined in linker script */

extern unsigned long __bss_start__;			/* start address for the .bss section. defined in linker script */
extern unsigned long __bss_end__;			/* end address for the .bss section. defined in linker script */

extern uint32_t _sfixed;
extern void _estack(void);
extern void __StackTop(void);



/* Private typedef -----------------------------------------------------------*/
/* function prototypes ------------------------------------------------------*/
extern int main(void);
extern void _CPUregTestPOST (void);

/******************************************************************************
*
* The minimal vector table for a Cortex M3.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/


__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) =
{
        (void *)&__StackTop,           // The initial stack pointer
        Reset_Handler,             /* Reset Handler */
        NMI_Handler,               /* NMI Handler */
        HardFault_Handler,         /* Hard Fault Handler */
        MemManage_Handler,         /* MPU Fault Handler */
        BusFault_Handler,          /* Bus Fault Handler */
        UsageFault_Handler,        /* Usage Fault Handler */
        0,                         /* Reserved */
        0,                         /* Reserved */
        0,                         /* Reserved */
        0,                         /* Reserved */
        SVC_Handler,               /* SVCall Handler */
        DebugMon_Handler,          /* Debug Monitor Handler */
        0,                         /* Reserved */
        PendSV_Handler,            /* PendSV Handler */
        SysTick_Handler,           /* SysTick Handler */

		// External Interrupts
        WDT_IRQHandler,            /* Watchdog Timer */
        TIMER0_IRQHandler,         /* Timer0 */
        TIMER1_IRQHandler,         /* Timer1 */
        TIMER2_IRQHandler,         /* Timer2 */
        TIMER3_IRQHandler,         /* Timer3 */
        UART0_IRQHandler,          /* UART0 */
        UART1_IRQHandler,          /* UART1 */
        UART2_IRQHandler,          /* UART2 */
        UART3_IRQHandler,          /* UART3 */
        PWM1_IRQHandler,           /* PWM1 */
        I2C0_IRQHandler,           /* I2C0 */
        I2C1_IRQHandler,           /* I2C1 */
        I2C2_IRQHandler,           /* I2C2 */
        SPI_IRQHandler,            /* SPI */
        SSP0_IRQHandler,           /* SSP0 */
        SSP1_IRQHandler,           /* SSP1 */
        PLL0_IRQHandler,           /* PLL0 (Main PLL) */
        RTC_IRQHandler,            /* Real Time Clock */
        EINT0_IRQHandler,          /* External Interrupt 0 */
        EINT1_IRQHandler,          /* External Interrupt 1 */
        EINT2_IRQHandler,          /* External Interrupt 2 */
        EINT3_IRQHandler,          /* External Interrupt 3 */
        ADC_IRQHandler,            /* A/D Converter */
        BOD_IRQHandler,            /* Brown Out Detect */
        USB_IRQHandler,            /* USB */
        CAN_IRQHandler,            /* CAN */
        DMA_IRQHandler,            /* GP DMA */
        I2S_IRQHandler,            /* I2S */
        ENET_IRQHandler,           /* Ethernet */
        RIT_IRQHandler,            /* Repetitive Interrupt Timer */
        MCPWM_IRQHandler,          /* Motor Control PWM */
        QEI_IRQHandler,            /* Quadrature Encoder Interface */
        PLL1_IRQHandler,           /* PLL1 (USB PLL) */
};

/*******************************************************************************
* Function Name  : Reset_Handler
* Description    : This is the code that gets called when the processor first starts execution
*		       following a reset event.  Only the absolutely necessary set is performed,
*		       after which the application supplied main() routine is called.
* Input          :
* Output         :
* Return         :
*******************************************************************************/
void Reset_Handler(void)
{
  //  SystemInit();
    unsigned long *pulSrc, *pulDest;

    //
    // Copy the data segment initializers from flash to SRAM in ROM mode
    //
    pulSrc = &__sidata;
    for(pulDest = &__data_start__; pulDest < &__data_end__; )
    {
        *(pulDest++) = *(pulSrc++);
    }

    //
    // Zero fill the bss segment.  This is done with inline assembly since this
    // will clear the value of pulDest if it is not kept in a register.
    //
    __asm("    ldr     r0, =__bss_start__\n"
          "    ldr     r1, =__bss_end__\n"
          "    mov     r2, #0\n"
          "    .thumb_func\n"
          "zero_loop:\n"
          "        cmp     r0, r1\n"
          "        it      lt\n"
          "        strlt   r2, [r0], #4\n"
          "        blt     zero_loop");

    //BSS segment in AHB ram will be zeroed later in main

    //Set the vector table base address
    pulSrc = (uint32_t *) & _sfixed;
    SCB->VTOR = ((uint32_t) pulSrc & SCB_VTOR_TBLOFF_Msk);


    //
    // Call the application's entry point.
    //
    main();
}
