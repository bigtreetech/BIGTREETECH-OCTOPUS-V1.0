//author: sdavi

#include "ConfigurableUART.h"


ConfigurableUART UART_Slot0;
ConfigurableUART UART_Slot1;
ConfigurableUART UART_Slot2;




//Wrapper class around HardwareSerial for configurable Serial in RRF

ConfigurableUART::ConfigurableUART() noexcept
    : serialPort(nullptr) 
{
}


enum uartPinDirection_t:uint8_t
{
    TX = 0,
    RX
};

struct uartPin_t
{
    Pin upin;
    uint8_t uartNumber;
    uartPinDirection_t dir;
    uint8_t pinselFunction;
};

const uartPin_t uartPins[] =
{
    //UART 0
    {P0_2,  0, TX, PINSEL_FUNC_1},
    {P0_3,  0, RX, PINSEL_FUNC_1},
    
#if defined(ENABLE_UART1)
    //UART1
    {P0_15, 1, TX, PINSEL_FUNC_1},
    {P0_16, 1, RX, PINSEL_FUNC_1},
    {P2_0,  1, TX, PINSEL_FUNC_2},
    {P2_1,  1, RX, PINSEL_FUNC_2},
#endif

#if defined(ENABLE_UART2)
    //UART2
    {P0_10, 2, TX, PINSEL_FUNC_1},
    {P0_11, 2, RX, PINSEL_FUNC_1},
    {P2_8,  2, TX, PINSEL_FUNC_2},
    {P2_9,  2, RX, PINSEL_FUNC_2},
#endif

#if defined(ENABLE_UART3)
    //UART3
    {P0_0,  3, TX, PINSEL_FUNC_2},
    {P0_1,  3, RX, PINSEL_FUNC_2},
    {P0_25, 3, TX, PINSEL_FUNC_3},
    {P0_26, 3, RX, PINSEL_FUNC_3},
    {P4_28, 3, TX, PINSEL_FUNC_3},
    {P4_29, 3, RX, PINSEL_FUNC_3},
#endif
};

int8_t ConfigurableUART::GetUARTPortNumber() noexcept
{
    if(serialPort == nullptr) return -1;
    
    if(serialPort == &Serial0) return 0;
#if defined(ENABLE_UART1)
    if(serialPort == &Serial1) return 1;
#endif
#if defined(ENABLE_UART2)
    if(serialPort == &Serial2) return 2;
#endif
#if defined(ENABLE_UART3)
    if(serialPort == &Serial3) return 3;
#endif

    return -1;
}

bool ConfigurableUART::Configure(Pin rx, Pin tx) noexcept
{
    //Find the UART based on the confgured Pins

    uartPin_t *txEntry = nullptr;
    uartPin_t *rxEntry = nullptr;
    
    for(uint8_t i=0; i< ARRAY_SIZE(uartPins); i++)
    {
        uartPin_t *nextExtry = (uartPin_t *)&uartPins[i];
        if(nextExtry->upin == rx && nextExtry->dir == RX)
        {
            //found RX Entry
            rxEntry = nextExtry;
        }

        if(nextExtry->upin == tx && nextExtry->dir == TX)
        {
            //found TX Entry
            txEntry = nextExtry;
        }

        if(txEntry && rxEntry) break;
    }
    
    if(txEntry && rxEntry && txEntry->uartNumber == rxEntry->uartNumber)
    {
        //we have 2 pins that are defined as a rx and tx and are both from the same UART number

        switch (txEntry->uartNumber)
        {
            case 0:
                serialPort = &Serial0;
                break;
#if defined(ENABLE_UART1)
            case 1:
                serialPort = &Serial1;
                break;
#endif
#if defined(ENABLE_UART2)
            case 2:
                serialPort = &Serial2;
                break;
#endif
#if defined(ENABLE_UART3)
            case 3:
                serialPort = &Serial3;
                break;
#endif
            default:
                return false;
        }
                
        //Configure the Pin Functions to UART
        GPIO_PinFunction(txEntry->upin, txEntry->pinselFunction);
        GPIO_PinFunction(rxEntry->upin, rxEntry->pinselFunction);
        
        return true; // success
    }
    
    return false;
    
}

void ConfigurableUART::begin(uint32_t baud) noexcept
{
    if(serialPort != nullptr)
    {
        serialPort->begin(baud);
    }
}

void ConfigurableUART::end(void) noexcept
{
    if(serialPort != nullptr)
    {
        serialPort->end();
    }
}

int ConfigurableUART::read(void) noexcept
{
    if(serialPort != nullptr)
    {
        return serialPort->read();
    }

    return -1;
}

int ConfigurableUART::peek(void) noexcept
{
    if(serialPort != nullptr)
    {
        return serialPort->peek();
    }
    
    return -1;
}

int ConfigurableUART::available(void) noexcept
{
    if(serialPort != nullptr)
    {
        return serialPort->available();
    }
    return 0;
}

int ConfigurableUART::availableForWrite(void) noexcept
{
    if(serialPort != nullptr)
    {
        return serialPort->read();
    }
    
    return 0;
}

size_t ConfigurableUART::canWrite() noexcept
{
    if(serialPort != nullptr)
    {
        return serialPort->canWrite();
    }
    return 0;
}

size_t ConfigurableUART::write(const uint8_t ch) noexcept
{
    if(serialPort != nullptr)
    {
        return serialPort->write(ch);
    }

    return 1;
}


size_t ConfigurableUART::write(const uint8_t *buffer, size_t size) noexcept
{
    if(serialPort != nullptr)
    {
        return serialPort->write(buffer, size);
    }

    return size;
}

void ConfigurableUART::flush(void) noexcept
{
    if(serialPort != nullptr)
    {
        serialPort->flush();
    }
}


void ConfigurableUART::setInterruptPriority(uint32_t priority) noexcept
{
    if(serialPort != nullptr)
    {
        serialPort->setInterruptPriority(priority);
    }
}

uint32_t ConfigurableUART::getInterruptPriority() noexcept
{
    if(serialPort != nullptr)
    {
        return serialPort->getInterruptPriority();
    }
    
    return 0;
}

bool ConfigurableUART::IsConnected() noexcept
{
    if(serialPort != nullptr) return true;
    return false;
}

// FIXME we should probbaly implement the call back for this!
ConfigurableUART::InterruptCallbackFn ConfigurableUART::SetInterruptCallback(InterruptCallbackFn f) noexcept
{
	InterruptCallbackFn ret = interruptCallback;
	interruptCallback = f;
	return ret;
}

// Get and clear the errors
ConfigurableUART::Errors ConfigurableUART::GetAndClearErrors() noexcept
{
	Errors errs;
	std::swap(errs, errors);
	return errs;
}

