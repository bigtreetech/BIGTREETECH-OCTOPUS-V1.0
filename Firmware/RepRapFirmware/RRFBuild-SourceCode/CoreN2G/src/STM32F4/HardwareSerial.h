/*
  HardwareSerial.h - Hardware serial library for Wiring
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Modified 28 September 2010 by Mark Sproul
  Modified 14 August 2012 by Alarus
  Modified 3 December 2013 by Matthijs Kooijman
*/

#ifndef HardwareSerial_h
#define HardwareSerial_h

#include <inttypes.h>

#include "Stream.h"
#include "uart.h"

// Define config for Serial.begin(baud, config);
// below configs are not supported by STM32
//#define SERIAL_5N1 0x00
//#define SERIAL_5N2 0x08
//#define SERIAL_5E1 0x20
//#define SERIAL_5E2 0x28
//#define SERIAL_5O1 0x30
//#define SERIAL_5O2 0x38
//#define SERIAL_6N1 0x02
//#define SERIAL_6N2 0x0A

#ifdef UART_WORDLENGTH_7B
#define SERIAL_7N1 0x04
#define SERIAL_7N2 0x0C
#define SERIAL_6E1 0x22
#define SERIAL_6E2 0x2A
#define SERIAL_6O1 0x32
#define SERIAL_6O2 0x3A
#endif
#define SERIAL_8N1 0x06
#define SERIAL_8N2 0x0E
#define SERIAL_7E1 0x24
#define SERIAL_8E1 0x26
#define SERIAL_7E2 0x2C
#define SERIAL_8E2 0x2E
#define SERIAL_7O1 0x34
#define SERIAL_8O1 0x36
#define SERIAL_7O2 0x3C
#define SERIAL_8O2 0x3E

class HardwareSerial : public Stream {
  protected:
    unsigned char _rx_buffer[SERIAL_RX_BUFFER_SIZE];
    unsigned char _tx_buffer[SERIAL_TX_BUFFER_SIZE];

    serial_t _serial;

  public:
    HardwareSerial(uint32_t _rx, uint32_t _tx) noexcept;
    HardwareSerial(PinName _rx, PinName _tx) noexcept;
    HardwareSerial(void *peripheral) noexcept;
    void begin(unsigned long baud) noexcept
    {
      begin(baud, SERIAL_8N1);
    }
    void begin(unsigned long, uint8_t) noexcept;
    void end() noexcept;
    virtual int available(void) noexcept;
    virtual int peek(void) noexcept;
    virtual int read(void) noexcept;
    int availableForWrite(void) noexcept;
	  virtual size_t canWrite() noexcept { return availableForWrite(); }
    virtual void flush(void) noexcept;
    virtual size_t write(uint8_t) noexcept;
    inline size_t write(unsigned long n) noexcept
    {
      return write((uint8_t)n);
    }
    inline size_t write(long n) noexcept
    {
      return write((uint8_t)n);
    }
    inline size_t write(unsigned int n) noexcept
    {
      return write((uint8_t)n);
    }
    inline size_t write(int n) noexcept
    {
      return write((uint8_t)n);
    }

    size_t write(const uint8_t *buffer, size_t size) noexcept override;

    using Print::write; // pull in write(str) and write(buf, size) from Print
    operator bool() noexcept
    {
      return true;
    }

    void setRx(uint32_t _rx) noexcept;
    void setTx(uint32_t _tx) noexcept;
    void setRx(PinName _rx) noexcept;
    void setTx(PinName _tx) noexcept;
    void setInterruptPriority(uint32_t priority) noexcept;
    uint32_t getInterruptPriority() noexcept;
    friend class STM32LowPower;
    friend class ConfigurableUART;
  private:
    uint8_t _config;
    unsigned long _baud;
    void init(void) noexcept;
    void configForLowPower(void) noexcept;
    size_t writeBlock(const uint8_t *buffer, size_t size) noexcept;
};

extern HardwareSerial Serial1;
extern HardwareSerial Serial2;
extern HardwareSerial Serial3;
extern HardwareSerial Serial4;
extern HardwareSerial Serial5;
extern HardwareSerial Serial6;
extern HardwareSerial Serial7;
extern HardwareSerial Serial8;
extern HardwareSerial Serial9;
extern HardwareSerial Serial10;
extern HardwareSerial SerialLP1;

#endif
