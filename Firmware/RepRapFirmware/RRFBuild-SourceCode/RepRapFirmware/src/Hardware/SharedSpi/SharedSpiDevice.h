/*
 * SharedSpiDevice.h
 *
 *  Created on: 16 Jun 2020
 *      Author: David
 */

#ifndef SRC_HARDWARE_SHAREDSPI_SHAREDSPIDEVICE_H_
#define SRC_HARDWARE_SHAREDSPI_SHAREDSPIDEVICE_H_

#include <RepRapFirmware.h>
#include <RTOSIface/RTOSIface.h>
#include "SpiMode.h"
#if LPC17xx || STM32F4
#include "SPI.h"
#endif

class SharedSpiDevice
{
public:
#if LPC17xx || STM32F4
	SharedSpiDevice(SSPChannel chan) noexcept;
#else
	SharedSpiDevice(uint8_t sercomNum) noexcept;
#endif

	void Disable() const noexcept;
	void Enable() const noexcept;
	void SetClockFrequencyAndMode(uint32_t freq, SpiMode mode) const noexcept;

	// Send and receive data returning true if successful. Caller must already own the mutex and have asserted CS.
	bool TransceivePacket(const uint8_t *tx_data, uint8_t *rx_data, size_t len) const noexcept;

	// Get ownership of this SPI, return true if successful
	bool Take(uint32_t timeout) noexcept { return mutex.Take(timeout); }

	// Release ownership of this SPI
	void Release() noexcept { mutex.Release(); }

	static void Init() noexcept;
#if LPC17xx || STM32F4
	static SharedSpiDevice& GetSharedSpiDevice(SSPChannel chan) noexcept { return *Devices[chan]; }
#else
	static SharedSpiDevice& GetMainSharedSpiDevice() noexcept { return *mainSharedSpiDevice; }
#endif

private:
	bool waitForTxReady() const noexcept;
	bool waitForTxEmpty() const noexcept;
	bool waitForRxReady() const noexcept;

#if SAME5x
	Sercom * const hardware;
#elif USART_SPI
	Usart * const hardware;
#elif LPC17xx || STM32F4
	SPI * const hardware;
#else
	Spi * const hardware;
#endif

	Mutex mutex;

#if LPC17xx || STM32F4
	static SharedSpiDevice *Devices[];
#else
	static SharedSpiDevice *mainSharedSpiDevice;
#endif
};

#endif /* SRC_HARDWARE_SHAREDSPI_SHAREDSPIDEVICE_H_ */
