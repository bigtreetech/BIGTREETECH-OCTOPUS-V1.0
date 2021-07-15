//Author: sdavi

#ifndef _CONFIGURABLEUART_H_
#define _CONFIGURABLEUART_H_


#include "Core.h"
#include "HardwareSerial.h"
#include "Stream.h"
#include "Print.h"




class ConfigurableUART : public Stream
{

public:
	typedef void (*InterruptCallbackFn)(ConfigurableUART*) noexcept;
	struct Errors
	{
		uint32_t uartOverrun,
				 framing,
				 bufferOverrun;

		Errors() noexcept : uartOverrun(0), framing(0), bufferOverrun(0)  {  }
	};



    ConfigurableUART() noexcept;

    bool Configure(Pin rx, Pin tx) noexcept;
    
    void begin(uint32_t baud) noexcept;
    void end() noexcept;

    size_t write(const uint8_t *buffer, size_t size) noexcept override;
    size_t write(uint8_t) noexcept override;

    int available(void) noexcept;
    int availableForWrite(void) noexcept;
    
    int peek(void) noexcept;
    int read(void) noexcept;
    void flush(void) noexcept;
    using Print::write;
    size_t canWrite() noexcept;

    bool IsConnected() noexcept;

    int8_t GetUARTPortNumber() noexcept;

    void setInterruptPriority(uint32_t priority) noexcept;
    uint32_t getInterruptPriority() noexcept;

    InterruptCallbackFn SetInterruptCallback(InterruptCallbackFn f) noexcept;

	// Get and clear the errors
	Errors GetAndClearErrors() noexcept;

private:
    HardwareSerial *serialPort;
    InterruptCallbackFn interruptCallback;
    Errors errors;
};

extern ConfigurableUART UART_Slot0;
extern ConfigurableUART UART_Slot1;
extern ConfigurableUART UART_Slot2;


#endif
