/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung.
 * Copyright (c) 2011, 2012 LeafLabs, LLC.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

/**
 * @file wirish/HardwareSerial.cpp
 * @brief Wirish serial port implementation.
 */
#include "CoreImp.h"
#include "chip.h"
#include "lpc_types.h"
#include "HardwareSerial.h"
#include "usart.h"
//#include "interrupt_lpc.h"

constexpr uint32_t MaxBaudRate = 460800;

HardwareSerial Serial0(USART0);

#if defined(ENABLE_UART1)
    HardwareSerial Serial1(USART1);
#endif

#if defined(ENABLE_UART2)
    HardwareSerial Serial2(USART2);
#endif

#if defined(ENABLE_UART3)
    HardwareSerial Serial3(USART3);
#endif

HardwareSerial::HardwareSerial(const usart_dev *usart_device, uint16_t rxRingBufferSize, uint16_t txRingBufferSize) noexcept
{
    initialised = false;
    this->usart_device = usart_device;
    
    rxBufferSize = rxRingBufferSize;
    txBufferSize = txRingBufferSize;
    
    rxDataBuffer = nullptr;
    txDataBuffer = nullptr;
    
}

void HardwareSerial::SetRingBufferSizes(uint16_t rxRingBufferSize, uint16_t txRingBufferSize) noexcept
{
    rxBufferSize = rxRingBufferSize;
    txBufferSize = txRingBufferSize;
}

void HardwareSerial::begin(uint32_t baud)
{
    if(initialised == false)
    {
        initialised = true;

        rxDataBuffer = new uint8_t[rxBufferSize];
        txDataBuffer = new uint8_t[txBufferSize];
        
        //Setup RingBuffers
        RingBuffer_Init(&this->rxRingBuffer, rxDataBuffer, 1, rxBufferSize);
        RingBuffer_Init(&this->txRingBuffer, txDataBuffer, 1, txBufferSize);
    }
    
    //Reset Ringbuffers
    RingBuffer_Flush(&this->rxRingBuffer);
    RingBuffer_Flush(&this->txRingBuffer);
    
    if (baud > MaxBaudRate)
    {
       return;
    }

    usart_init(this->usart_device, baud, true);
}

void HardwareSerial::end(void) noexcept
{
    NVIC_DisableIRQ(this->usart_device->irq_NUM);
    Chip_UART_IntDisable(this->usart_device->UARTx, (UART_IER_RBRINT | UART_IER_RLSINT));
}

int HardwareSerial::read(void) noexcept
{
    //read from the Ring Buffer
    int data;
    if(RingBuffer_Pop(&this->rxRingBuffer, &data))
    {
        return data;
    }
    else
    {
        return -1;
    }
}

int HardwareSerial::peek(void) noexcept
{
    int data;
    if(RingBuffer_Peek(&this->rxRingBuffer, &data))
    {
        return data;
    }
    return -1;
}

int HardwareSerial::available(void) noexcept
{
    irqflags_t flags = IrqSave();
    int avail = RingBuffer_GetCount(&this->rxRingBuffer);
    IrqRestore(flags);
    return avail;
}

int HardwareSerial::availableForWrite(void) noexcept
{
    //return number for free items in the txRingBuffer
    irqflags_t flags = IrqSave();
    int avail = RingBuffer_GetFree(&this->txRingBuffer);
    IrqRestore(flags);
    return avail;
}

size_t HardwareSerial::canWrite() noexcept
{
    irqflags_t flags = IrqSave();
    int avail = RingBuffer_GetFree(&this->txRingBuffer);
    IrqRestore(flags);
    return avail;
}

size_t HardwareSerial::write(const uint8_t ch) noexcept
{
    // spin until there is room
    while (Chip_UART_SendRB(this->usart_device->UARTx, &this->txRingBuffer, &ch, 1) == 0) {}
    return 1;
}


size_t HardwareSerial::write(const uint8_t *buffer, size_t size) noexcept
{
    size_t ret = size;
    while (size != 0)
    {
        size_t written = Chip_UART_SendRB(this->usart_device->UARTx, &this->txRingBuffer, buffer, size);
        buffer += written;
        size -= written;
    }
    return ret;

}

void HardwareSerial::flush(void) noexcept
{
    while(RingBuffer_GetFree(&this->txRingBuffer) > 0); //wait for the ring buffer to empty
    //TODO:: should wait for the fifo to empty too
}

void HardwareSerial::IRQHandler() noexcept
{
    //call the LPCOpen Interrupt Handler
    Chip_UART_IRQRBHandler(this->usart_device->UARTx, &this->rxRingBuffer, &this->txRingBuffer);
}



//compat with RRF
void HardwareSerial::setInterruptPriority(uint32_t priority) noexcept
{
    NVIC_SetPriority(this->usart_device->irq_NUM, priority);
}

uint32_t HardwareSerial::getInterruptPriority() noexcept
{
    return NVIC_GetPriority(this->usart_device->irq_NUM);
}

