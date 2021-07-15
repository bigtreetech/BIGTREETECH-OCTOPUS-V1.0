
#ifndef _EXPLORE_M3_USART_H_
#define _EXPLORE_M3_USART_H_


#ifdef __cplusplus
extern "C" {
#endif
#include "chip.h"
#include "uart_17xx_40xx.h"
    
#include "stdint.h"
#include "gpio.h"


#include "ring_buffer.h"

typedef struct usart_dev
{
    LPC_USART_T *UARTx;
    IRQn_Type irq_NUM;  
} usart_dev;

void usart_init(const usart_dev *dev, uint32_t baud_rate, bool enableInts) noexcept;


extern const usart_dev *USART0;
extern const usart_dev *USART1;
extern const usart_dev *USART2;
extern const usart_dev *USART3;



#ifdef __cplusplus
}
#endif



#endif

