/*
  Copyright (c) 2015 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _USBSERIAL_H_
#define _USBSERIAL_H_

#if defined (USBCON) && defined(USBD_USE_CDC)
#include "Stream.h"
#include "usbd_core.h"

//================================================================================
// Serial over CDC
class USBSerial : public Stream {
  public:
    void begin(void) noexcept;
    void begin(uint32_t) noexcept;
    void begin(uint32_t, uint8_t) noexcept;
    void end(void) noexcept;

    virtual int available(void) noexcept;
    virtual int availableForWrite(void) noexcept;
    virtual size_t canWrite() noexcept { return availableForWrite(); }
    virtual int peek(void) noexcept;
    virtual int read(void) noexcept;
    virtual size_t readBytes(char *buffer, size_t length) noexcept;  // read chars from stream into buffer
    virtual void flush(void) noexcept;
    virtual size_t write(uint8_t) noexcept;
    virtual size_t write(const uint8_t *buffer, size_t size) noexcept;
    using Print::write; // pull in write(str) from Print
    operator bool(void) noexcept;
    bool IsConnected() noexcept;

    // These return the settings specified by the USB host for the
    // serial port. These aren't really used, but are offered here
    // in case a sketch wants to act on these settings.
    uint32_t baud() noexcept;
    uint8_t stopbits() noexcept;
    uint8_t paritytype() noexcept;
    uint8_t numbits() noexcept;
    bool dtr() noexcept;
    bool rts() noexcept;
    enum {
      ONE_STOP_BIT = 0,
      ONE_AND_HALF_STOP_BIT = 1,
      TWO_STOP_BITS = 2,
    };
    enum {
      NO_PARITY = 0,
      ODD_PARITY = 1,
      EVEN_PARITY = 2,
      MARK_PARITY = 3,
      SPACE_PARITY = 4,
    };
};

extern USBSerial SerialUSB;
#endif /* USBCON */
#endif /* _USBSERIAL_H_ */
