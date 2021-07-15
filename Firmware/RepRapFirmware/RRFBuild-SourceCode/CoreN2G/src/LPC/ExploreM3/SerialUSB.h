
#ifndef _USB_SERIAL_H_
#define _USB_SERIAL_H_

#include "Stream.h"
#include "USBSerial.h"
#include "gpio.h"


#if defined(ENABLE_DFU)
//# include "DFU/DFU.h"
#endif


//SD: Wrapper around USBSerial to behave like arduino Serial
class SerialUSB : public Stream {

private:
    USBSerial *usbSerial;
    bool isConnected;

public:
    SerialUSB() noexcept;

    void begin(uint32_t baud) noexcept;
    void end() noexcept;
    
    int available() noexcept;
    int peek() noexcept;
    int read() noexcept;
    
    void flush() noexcept;
    size_t write(uint8_t) noexcept;
    size_t write(const uint8_t *buffer, size_t size) noexcept;
    size_t write(const char *buffer, size_t size) noexcept { return write((const uint8_t *)buffer, size); }

    size_t canWrite() noexcept;

    void setInterruptPriority(uint32_t priority) noexcept;
    uint32_t getInterruptPriority() noexcept;

    bool IsConnected() noexcept;
    
};

extern SerialUSB Serial;

#endif

