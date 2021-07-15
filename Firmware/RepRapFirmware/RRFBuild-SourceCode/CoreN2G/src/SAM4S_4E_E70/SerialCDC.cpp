/*
 * SerialCDC.cpp
 *
 *  Created on: 18 Mar 2016
 *      Author: David
 */

#if SUPPORT_USB
#include <SerialCDC.h>
#include <Interrupts.h>
#include "conf_usb.h"		// include this to check that the signatures of the callback functions are correct
#include "udi_cdc.h"		// Atmel CDC module
#include "udc.h"

// Pointer to the serial USB device. Currently we support only one.
static SerialCDC *serialUSBDevice = nullptr;

void core_vbus_off(CallbackParameter) noexcept;

// SerialCDC members

SerialCDC::SerialCDC() noexcept : /* _cdc_tx_buffer(), */ txBufsize(1), isConnected(false), vBusPin(NoPin)
{
}

void SerialCDC::Start(Pin p_vBusPin) noexcept
{
	vBusPin = p_vBusPin;
	udc_start();

	if (vBusPin != NoPin)
	{
		pinMode(vBusPin, INPUT);
		attachInterrupt(vBusPin, core_vbus_off, InterruptMode::falling, nullptr);
	}

	serialUSBDevice = this;
}

void SerialCDC::end() noexcept
{
	serialUSBDevice = nullptr;
	isConnected = false;
	udc_stop();
}

int SerialCDC::available() noexcept
{
	return (isConnected) ? udi_cdc_multi_get_nb_received_data(0) : 0;
}

int SerialCDC::read() noexcept
{
	return (udi_cdc_multi_is_rx_ready(0)) ? udi_cdc_multi_getc(0) : -1;
}

size_t SerialCDC::readBytes(char *buffer, size_t length) noexcept
{
	return (isConnected) ? udi_cdc_multi_read_no_polling(0, buffer, length) : 0;
}

void SerialCDC::flush(void) noexcept
{
	while (isConnected && udi_cdc_multi_get_free_tx_buffer(0) < txBufsize) {}
}

size_t SerialCDC::write(uint8_t c) noexcept
{
	if (isConnected)
	{
		udi_cdc_multi_putc(0, c);
	}
	return 1;
}

// Non-blocking write to USB. Returns number of bytes written. If we are not connected, pretend that all bytes have been written.
size_t SerialCDC::write(const uint8_t *buffer, size_t size) noexcept
{
	if (isConnected && size != 0)
	{
		const size_t remaining = udi_cdc_multi_write_buf(0, buffer, size);
		return size - remaining;
	}
	return size;
}

size_t SerialCDC::canWrite() noexcept
{
	return (isConnected) ? udi_cdc_multi_get_free_tx_buffer(0) : 0;
}

bool SerialCDC::IsConnected() const noexcept
{
	return isConnected;
}

void SerialCDC::cdcSetConnected(bool b) noexcept
{
	isConnected = b;
}

void SerialCDC::cdcRxNotify() noexcept
{
	// nothing here until we use a Rx buffer
}

void SerialCDC::cdcTxEmptyNotify() noexcept
{
	// If we haven't yet found out how large the transmit buffer is, find out now
	if (txBufsize == 1)
	{
		txBufsize = udi_cdc_multi_get_free_tx_buffer(0);
	}
}

// Callback glue functions, all called from the USB ISR

// This is called when we are plugged in and connect to a host
extern "C" bool core_cdc_enable(uint8_t port) noexcept
{
	if (serialUSBDevice != nullptr)
	{
		serialUSBDevice->cdcSetConnected(true);
		return true;
	}
	return false;
}

// This is called when we get disconnected from the host
extern "C" void core_cdc_disable(uint8_t port) noexcept
{
	if (serialUSBDevice != nullptr)
	{
		serialUSBDevice->cdcSetConnected(false);
	}
}

// This is called when data has been received
extern "C" void core_cdc_rx_notify(uint8_t port) noexcept
{
	if (serialUSBDevice != nullptr)
	{
		serialUSBDevice->cdcRxNotify();
	}
}

// This is called when the transmit buffer has been emptied
extern "C" void core_cdc_tx_empty_notify(uint8_t port) noexcept
{
	if (serialUSBDevice != nullptr)
	{
		serialUSBDevice->cdcTxEmptyNotify();
	}
}

// On the SAM4E and SAM4S we use a GPIO pin available to monitor the VBUS state
void core_vbus_off(CallbackParameter) noexcept
{
	if (serialUSBDevice != nullptr)
	{
		serialUSBDevice->cdcSetConnected(false);
	}
}

#endif

// End
