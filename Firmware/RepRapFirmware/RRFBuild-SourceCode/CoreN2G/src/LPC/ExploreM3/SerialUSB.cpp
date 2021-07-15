/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2015 ExploreEmbedded.com
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


#include "chip.h"
#include "SerialUSB.h"

SerialUSB Serial;

constexpr uint16_t vendor_id = 0x1d50;
constexpr uint16_t product_id = 0x6015;
constexpr uint16_t product_release = 0x0001;

SerialUSB::SerialUSB() noexcept
{
    this->usbSerial = new USBSerial(true, vendor_id, product_id, product_release);
    
#if defined(ENABLE_DFU)
//    this->dfu = new DFU(this->usb);
#endif

}



void SerialUSB::begin(uint32_t baud) noexcept
{
    (void)baud;
}

void SerialUSB::end(void) noexcept
{
 
}

int SerialUSB::available(void) noexcept
{
    if (usbSerial->connected())
    {
        return usbSerial->available();
    }
    return 0;
}


int SerialUSB::peek(void) noexcept
{
    return -1;// Not Supported
}


int SerialUSB::read(void) noexcept
{
    if (usbSerial->connected())
    {
        uint8_t c;
        uint32_t cnt;
        usbSerial->receive_nb(&c, 1,  &cnt);
        if (cnt == 0)
            return -1;
        else
            return (int)c;
    }
    return -1;
}



void SerialUSB::flush(void) noexcept
{
    if (usbSerial->connected())
    {
        usbSerial->flush();
    }
}


size_t SerialUSB::canWrite() noexcept
{
    return usbSerial->writeable();
}

bool SerialUSB::IsConnected() noexcept
{
    return usbSerial->connected();
}


size_t SerialUSB::write(uint8_t c) noexcept
{
    if (usbSerial->connected())
    {
        write(&c, 1);
    }
    return 1;
}


size_t SerialUSB::write(const uint8_t *buffer, size_t size) noexcept
{
    size_t ret = size;
    while (usbSerial->connected() && size != 0)
    {
        uint32_t written = 0;
        usbSerial->send_nb(const_cast<uint8_t*>(buffer), size, &written);
        buffer += written;
        size -= written;
    }
    return ret;
}



void SerialUSB::setInterruptPriority(uint32_t priority) noexcept
{
    NVIC_SetPriority(USB_IRQn, priority);
}

uint32_t SerialUSB::getInterruptPriority() noexcept
{
    return NVIC_GetPriority(USB_IRQn);
}
