/**
 * \file
 *
 * \brief SAM SDHC HPL
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */

#include <Sdhc.h>

#if SUPPORT_SDHC

#include <CoreIO.h>

// Define which SDHC controller we are using
Sdhc* const hw = SDHC1;
constexpr IRQn SDHC_IRQn = SDHC1_IRQn;
#define SDHC_ISR	SDHC1_Handler

#define HSMCI_SLOT_0_SIZE 		4
#define CONF_SDHC_CLK_GEN_SEL	0

// Enabling STOP_CLOCK_WHEN_IDLE reduces EMI when idle. Unfortunately it causes hangs when running the SD card write speed test. So leave it disabled.
#define STOP_CLOCK_WHEN_IDLE	0

//extern "C" int debugPrintf(const char* fmt, ...) noexcept __attribute__ ((format (printf, 1, 2)));

static uint32_t currentRequestedClockFrequency = 0;			// the speed we were asked for when we last set the clock frequency (not necessarily the actual clock speed)
static uint32_t currentActualClockFrequency;				// the actual speed we set
static uint64_t mci_sync_trans_pos;
static uint16_t mci_sync_block_size;
static uint16_t mci_sync_nb_block;

#ifdef RTOS

#include <RTOSIface/RTOSIface.h>
volatile static TaskHandle sdhcWaitingTask;

#endif

typedef struct
{
    uint16_t                            attribute;
    uint16_t                            length;
    uint32_t                            address;
} SDHC_ADMA_DESCR;

/* ADMA Descriptor Table Attribute Mask */
#define SDHC_DESC_TABLE_ATTR_NO_OP          (0x00 << 4)
#define SDHC_DESC_TABLE_ATTR_RSVD           (0x01 << 4)
#define SDHC_DESC_TABLE_ATTR_XFER_DATA      (0x02 << 4)
#define SDHC_DESC_TABLE_ATTR_LINK_DESC      (0x03 << 4)

#define SDHC_DESC_TABLE_ATTR_VALID          (1 << 0)
#define SDHC_DESC_TABLE_ATTR_END            (1 << 1)
#define SDHC_DESC_TABLE_ATTR_INTR           (1 << 2)

__attribute__((aligned(32))) static SDHC_ADMA_DESCR sdhc1DmaDescrTable[1];

static void hsmci_reset_cmdinh() noexcept;
static void hsmci_reset_datinh() noexcept;
static void hsmci_reset_all() noexcept;
static bool hsmci_set_speed(uint32_t speed) noexcept;
static bool hsmci_wait_busy() noexcept;
static bool hsmci_send_cmd_execute(uint32_t cmdr, uint32_t cmd, uint32_t arg) noexcept;

/**
 * \brief Reset the SDHC interface command inhibit bit
 *
 * \param hw The pointer to MCI hardware instance
 */
static void hsmci_reset_cmdinh() noexcept
{
	hw->SRR.reg = SDHC_SRR_SWRSTCMD;
	while (hw->SRR.reg & SDHC_SRR_SWRSTCMD) { }
}

/**
 * \brief Reset the SDHC interface command inhibit bit
 *
 * \param hw The pointer to MCI hardware instance
 */
static void hsmci_reset_datinh() noexcept
{
	hw->SRR.reg = SDHC_SRR_SWRSTDAT;
	while (hw->SRR.reg & SDHC_SRR_SWRSTDAT) { }
}

/**
 * \brief Reset the SDHC interface
 *
 * \param hw The pointer to MCI hardware instance
 */
static void hsmci_reset_all() noexcept
{
	hw->SRR.reg = SDHC_SRR_SWRSTALL;
	while (hw->SRR.reg & SDHC_SRR_SWRSTALL) { }
}

// Stop the SD card clock
static void hsmciStopClock() noexcept
{
	if ((hw->CCR.reg & SDHC_CCR_SDCLKEN) != 0)
	{
		const uint32_t startedWaitingAt = millis();
		uint32_t psr;
		while (((psr = hw->PSR.reg) & (SDHC_PSR_CMDINHC_CANNOT | SDHC_PSR_CMDINHD_CANNOT)) != 0 && millis() - startedWaitingAt < 2) { }
		if (psr & SDHC_PSR_CMDINHC_CANNOT)
		{
			hsmci_reset_cmdinh();
		}
		if (psr & SDHC_PSR_CMDINHD_CANNOT)
		{
			hsmci_reset_datinh();
		}
		hw->CCR.reg &= ~SDHC_CCR_SDCLKEN;
	}
}

/**
 * \brief Set speed of the SDHC clock.
 *
 * \param hw       The pointer to MCI hardware instance
 * \param speed    SDHC clock speed in Hz.
 * \return true if success
 */
static bool hsmci_set_speed(uint32_t speed) noexcept
{
	if (speed != currentRequestedClockFrequency)
	{
		currentRequestedClockFrequency = currentActualClockFrequency = 0;

		// The following is based on the code from Harmony
		hsmciStopClock();								// disable clock before changing it

		// Get the base clock frequency
		const uint32_t baseclk_frq = AppGetSdhcClockSpeed()/2;

		// Use programmable clock mode if it is supported. Note, clkmul is 1 on the SAME54P20, not 0 as specified in the data sheet.
		const uint32_t clkmul = (hw->CA1R.reg & SDHC_CA1R_CLKMULT_Msk) >> SDHC_CA1R_CLKMULT_Pos;
		uint16_t divider = 0;
		if (clkmul > 0)
		{
			/* F_SDCLK = F_MULTCLK/(DIV+1), where F_MULTCLK = F_BASECLK x (CLKMULT+1)
			   F_SDCLK = (F_BASECLK x (CLKMULT + 1))/(DIV + 1)
			   For a given F_SDCLK, DIV = [(F_BASECLK x (CLKMULT + 1))/F_SDCLK] - 1
			*/
			divider = (baseclk_frq * (clkmul + 1)) / speed;
			if (divider > 0)
			{
				divider = divider - 1;
			}
			hw->CCR.reg |= SDHC_CCR_CLKGSEL;
		}
		else
		{
			// Programmable clock mode is not supported, so use divided clock mode
			/* F_SDCLK = F_BASECLK/(2 x DIV).
			   For a given F_SDCLK, DIV = F_BASECLK/(2 x F_SDCLK)
			*/
			divider =  baseclk_frq/(2 * speed);
			if (divider == 0)
			{
				divider = 1;
			}
			hw->CCR.reg &= ~SDHC_CCR_CLKGSEL;
		}

		if (speed > 25000000)
		{
			// Enable the high speed mode
			hw->HC1R.reg |= SDHC_HC1R_HSEN;
			if (divider == 0)
			{
				// IP limitation, if high speed mode is active divider must be non zero
				divider = 1;
			}
		}
		else
		{
			// Clear the high speed mode
			hw->HC1R.reg &= ~SDHC_HC1R_HSEN;
		}

		// Set the divider
		hw->CCR.reg = (hw->CCR.reg & ~(SDHC_CCR_SDCLKFSEL_Msk | SDHC_CCR_USDCLKFSEL_Msk))
						| (SDHC_CCR_SDCLKFSEL(divider & 0xFF) | SDHC_CCR_USDCLKFSEL(divider >> 8));

		// Enable internal clock
		hw->CCR.reg |= SDHC_CCR_INTCLKEN;

		// Wait for the internal clock to stabilize
		while ((hw->CCR.reg & SDHC_CCR_INTCLKS) == 0) { }

		currentRequestedClockFrequency = speed;
		currentActualClockFrequency = ((hw->CCR.reg & SDHC_CCR_CLKGSEL) != 0) ? (baseclk_frq * (clkmul + 1)) / (divider + 1) : baseclk_frq/(divider * 2);
	}

	// Enable the SDCLK
	hw->CCR.reg |= SDHC_CCR_SDCLKEN;
	return true;
}

// Setup the DMA transfer.
// Each ADMA2 descriptor can transfer 65536 bytes (or 128 blocks) of data.
// For simplicity we use only one descriptor, so numBytes must not exceed 65536.
static void hsmci_dma_setup (const void* buffer, uint32_t numBytes) noexcept
{
	hw->HC1R.reg |= SDHC_HC1R_DMASEL(SDHC_HC1R_DMASEL_32BIT_Val);

	// Set up the descriptor
	sdhc1DmaDescrTable[0].address = (uint32_t)(buffer);
	sdhc1DmaDescrTable[0].length = numBytes;
	sdhc1DmaDescrTable[0].attribute = (SDHC_DESC_TABLE_ATTR_XFER_DATA | SDHC_DESC_TABLE_ATTR_VALID | SDHC_DESC_TABLE_ATTR_INTR | SDHC_DESC_TABLE_ATTR_END);

	// Set the starting address of the descriptor table
	hw->ASAR[0].reg = (uint32_t)(&sdhc1DmaDescrTable[0]);
}

// Wait for a DMA data transfer to complete, returning true if OK, false if it failed
static bool WaitForDmaComplete() noexcept
{
	// These three constants are probably the same, but let the compiler sort that out
#ifdef RTOS
	constexpr uint16_t ErrorInterruptMask = SDHC_EISIER_DATTEO | SDHC_EISIER_DATCRC | SDHC_EISIER_DATEND | SDHC_EISIER_ADMA;
#endif
	constexpr uint16_t ErrorStatusMask =    SDHC_EISIER_DATTEO | SDHC_EISIER_DATCRC | SDHC_EISIER_DATEND | SDHC_EISIER_ADMA;
	while (true)
	{
		uint16_t nistr, eistr;
		while (true)
		{
			nistr = hw->NISTR.reg;
			eistr = hw->EISTR.reg;
			if ((nistr & SDHC_NISTR_TRFC) != 0 || (eistr & ErrorStatusMask) != 0)
			{
				break;
			}
#ifdef RTOS
			__disable_irq();
			sdhcWaitingTask = TaskBase::GetCallerTaskHandle();
			hw->NISIER.reg = SDHC_NISIER_TRFC;
			hw->EISIER.reg = ErrorInterruptMask;
			__enable_irq();
			if (!TaskBase::Take(500))
			{
				sdhcWaitingTask = nullptr;
				hw->NISIER.reg = 0;
				hw->EISIER.reg = 0;
				// Timed out waiting for interrupt
//				debugPrintf("SDHC timeout, NISTR=%04x EISTR=%04x\n", hw->NISTR.reg, hw->EISTR.reg);
				return false;
			}
#endif
		}

		hw->NISTR.reg = nistr;					// clear the interrupt(s)
		hw->EISTR.reg = eistr;					// clear the error status

		if ((nistr & SDHC_NISTR_ERRINT) == 0)
		{
			return true;						// transfer complete or DMA complete
		}

		eistr &= ErrorStatusMask;				// get the errors we care about
		if ((nistr & SDHC_NISTR_TRFC) != 0 && (eistr & ~SDHC_EISTR_DATTEO) == 0)
		{
			return true;						// we had transfer complete and timeout - the controller specification says treat this as a successful transfer
		}

		if (eistr != 0)							// if there were errors that we care about, quit
		{
			return false;
		}

		// Else we had an error interrupt but we don't care about that error, so wait again
	}
}

static uint32_t hsmci_get_clock_speed() noexcept
{
	return currentActualClockFrequency;
}

/**
 * \brief Wait the end of busy signal on data line
 *
 * \param hw       The pointer to MCI hardware instance
 * \return true if success, otherwise false
 */
static bool hsmci_wait_busy() noexcept
{
	const uint32_t startedWaitingAt = millis();
	while ((hw->PSR.reg & SDHC_PSR_DATLL(1)) == 0)
	{
		if (millis() - startedWaitingAt > 100)
		{
			hsmci_reset_all();
			return false;
		}
	}
	return true;
}

/**
 * \brief Send a command
 *
 * \param hw         The pointer to MCI hardware instance
 * \param cmdr       CMDR register bit to use for this command
 * \param cmd        Command definition
 * \param arg        Argument of the command
 *
 * \return true if success, otherwise false
 */
static bool hsmci_send_cmd_execute(uint32_t cmdr, uint32_t cmd, uint32_t arg) noexcept
{
	// dc42 clear all bits in NISTR and EISTR before we start
	hw->NISTR.reg = SDHC_NISTR_MASK & 0x7FFF;
	hw->EISTR.reg = SDHC_EISTR_MASK;

	cmdr |= SDHC_CR_CMDIDX(cmd) | SDHC_CR_CMDTYP_NORMAL;

	if (cmd & MCI_RESP_PRESENT)
	{
		if (cmd & MCI_RESP_136) {
			cmdr |= SDHC_CR_RESPTYP_136_BIT;
		} else if (cmd & MCI_RESP_BUSY) {
			cmdr |= SDHC_CR_RESPTYP_48_BIT_BUSY;
		} else {
			cmdr |= SDHC_CR_RESPTYP_48_BIT;
		}
	}

	if (cmd & MCI_CMD_OPENDRAIN)
	{
		hw->MC1R.reg |= SDHC_MC1R_OPD;
	}
	else
	{
		hw->MC1R.reg &= ~SDHC_MC1R_OPD;
	}

	hw->ARG1R.reg = arg;
	hw->CR.reg = cmdr;

	/* Wait end of command */
	const uint32_t errorMask = (cmd & MCI_RESP_CRC)
							? SDHC_EISTR_CMDTEO | SDHC_EISTR_CMDEND | SDHC_EISTR_CMDIDX  | SDHC_EISTR_DATTEO | SDHC_EISTR_DATEND | SDHC_EISTR_ADMA | SDHC_EISTR_CMDCRC | SDHC_EISTR_DATCRC
								: SDHC_EISTR_CMDTEO | SDHC_EISTR_CMDEND | SDHC_EISTR_CMDIDX | SDHC_EISTR_DATTEO | SDHC_EISTR_DATEND | SDHC_EISTR_ADMA;
	const uint32_t startedWaitingAt = millis();
	do
	{
		if (hw->EISTR.reg & errorMask)
		{
			hsmci_reset_cmdinh();
			hw->EISTR.reg |= SDHC_EISTR_MASK;
			return false;
		}
		if (millis() - startedWaitingAt > 100)
		{
//			debugPrintf("SD hang, cmd=%" PRIx32 " cmdr=%" PRIx32 " NISTR=%04x EISTR=%04x\n", cmd, cmdr, hw->NISTR.reg, hw->EISTR.reg);
			hsmci_reset_all();
			return false;
		}
	} while ((hw->NISTR.reg & SDHC_NISTR_CMDC) == 0);

	if ((cmdr & SDHC_CR_DPSEL_DATA) == 0)
	{
		// dc42: only clear the CMDC bit! In particular, don't clear TRFC.
		hw->NISTR.reg = SDHC_NISTR_CMDC;
	}
	if (cmd & MCI_RESP_BUSY)
	{
		if (!hsmci_wait_busy())
		{
			return false;
		}
	}

	return true;
}

/**
 *  \brief Initialize MCI low level driver.
 *  If using RTOS then the client must also set the NVIC interrupt priority during initialisation to a value low enough to allow the ISR to make FreeRTOS calls
 */
void hsmci_init() noexcept
{
	hw->SRR.reg |= SDHC_SRR_SWRSTALL;
	while ((hw->SRR.reg & SDHC_SRR_SWRSTALL) != 0) { }

	/* Set the Data Timeout Register to 2 Mega Cycles */
	hw->TCR.reg = SDHC_TCR_DTCVAL(0xE);

	/* Set 3v3 power supply */
	hw->PCR.reg = SDHC_PCR_SDBPWR_ON | SDHC_PCR_SDBVSEL_3V3;

	hw->NISTER.reg = SDHC_NISTER_MASK;
	hw->EISTER.reg = SDHC_EISTER_MASK;

#ifdef RTOS
	hw->NISIER.reg = 0;					// disable normal interrupts
	hw->EISIER.reg = 0;					// disable error interrupts
	NVIC_ClearPendingIRQ(SDHC_IRQn);
	NVIC_EnableIRQ(SDHC_IRQn);
#endif
}


/**
 *  \brief Select a device and initialize it, returning true if success
 */
bool hsmci_select_device(uint8_t slot, uint32_t clock, uint8_t bus_width, bool high_speed) noexcept
{
	(void)slot;
	(void)high_speed;			// we set high speed or not automatically depending on the clock frequency

	if (!hsmci_set_speed(clock))
	{
		return false;
	}

	switch (bus_width)
	{
	case 1:
	default:
		hw->HC1R.reg &= ~SDHC_HC1R_DW;
		break;

	case 4:
		hw->HC1R.reg |= SDHC_HC1R_DW;
		break;
	}
	return true;
}

/**
 *  \brief Deselect a device by an assigned slot
 */
void hsmci_deselect_device(uint8_t slot) noexcept
{
	(void)(slot);
#if STOP_CLOCK_WHEN_IDLE
	hsmciStopClock();				// stop the SD card clock to reduce EMI
#else
	// Nothing to do
#endif
}

/**
 *  \brief Get the maximum bus width of a device
 *         by a selected slot
 */
uint8_t hsmci_get_bus_width(uint8_t slot) noexcept
{
	switch (slot)
	{
	case 0:
		return HSMCI_SLOT_0_SIZE;

	default:
		/* Slot number wrong */
		return 0;
	}
}

/**
 *  \brief Get the high speed capability of the device.
 */
bool hsmci_is_high_speed_capable() noexcept
{
	return (hw->CA0R.reg & SDHC_CA0R_HSSUP) != 0;
}

// Get the transfer rate in bytes/sec
uint32_t hsmci_get_speed() noexcept
{
	return hsmci_get_clock_speed()/(8/HSMCI_SLOT_0_SIZE);
}

/**
 *  \brief Send 74 clock cycles on the line.
 *   Note: It is required after card plug and before card install.
 */
void hsmci_send_clock() noexcept
{
	delayMicroseconds((75'000'000/currentActualClockFrequency) + 1);		// delay for 75 SD card clocks plus 1us to round it up, plus the time taken to execute the division
}

/**
 *  \brief Send a command on the selected slot
 */
bool hsmci_send_cmd(uint32_t cmd, uint32_t arg) noexcept
{
	/* Check Command Inhibit (CMD) in the Present State register */
	if (hw->PSR.reg & SDHC_PSR_CMDINHC)
	{
		return false;
	}

	return hsmci_send_cmd_execute(0, cmd, arg);
}

/**
 *  \brief Get 32 bits response of the last command.
 */
uint32_t hsmci_get_response() noexcept
{
	return hw->RR[0].reg;
}

/**
 *  \brief Get 128 bits response of the last command.
 */
void hsmci_get_response_128(uint8_t *response) noexcept
{
	for (int i = 3; i >= 0; i--)
	{
		const uint32_t response_32 = hw->RR[i].reg;
		if (i != 3)
		{
			*response = (response_32 >> 24) & 0xFF;
			response++;
		}
		*response = (response_32 >> 16) & 0xFF;
		response++;
		*response = (response_32 >> 8) & 0xFF;
		response++;
		*response = (response_32 >> 0) & 0xFF;
		response++;
	}
}

/**
 *  \brief Send an ADTC command on the selected slot
 *         An ADTC (Addressed Data Transfer Commands)
 *         command is used for read/write access.
 */
bool hsmci_adtc_start(uint32_t cmd, uint32_t arg, uint16_t block_size, uint16_t nb_block, const void *dmaAddr) noexcept
{
	/* Check Command Inhibit (CMD/DAT) in the Present State register */
	if ((hw->PSR.reg & (SDHC_PSR_CMDINHC | SDHC_PSR_CMDINHD)) != 0)
	{
		return false;
	}

	uint32_t tmr = (cmd & MCI_CMD_WRITE) ? SDHC_TMR_DTDSEL_WRITE : SDHC_TMR_DTDSEL_READ;

	if (cmd & MCI_CMD_SINGLE_BLOCK)
	{
		tmr |= SDHC_TMR_MSBSEL_SINGLE;
	}
	else if (cmd & MCI_CMD_MULTI_BLOCK)
	{
		tmr |= SDHC_TMR_BCEN | SDHC_TMR_MSBSEL_MULTIPLE;
	}
	else
	{
		return false;
	}

	hw->BCR.reg =  SDHC_BCR_BCNT(nb_block);
	hw->BSR.reg =  SDHC_BSR_BLOCKSIZE(block_size) | SDHC_BSR_BOUNDARY_4K;

	if (dmaAddr != NULL)
	{
		hsmci_dma_setup(dmaAddr, nb_block * (uint32_t)block_size);
		tmr |= SDHC_TMR_DMAEN_ENABLE;
	}

	hw->TMR.reg = tmr;

	mci_sync_trans_pos  = 0;
	mci_sync_block_size = block_size;
	mci_sync_nb_block   = nb_block;

	return hsmci_send_cmd_execute(SDHC_CR_DPSEL_DATA, cmd, arg);
}

/**
 *  \brief Send a command to stop an ADTC command on the selected slot.
 */
bool hsmci_adtc_stop(uint32_t cmd, uint32_t arg) noexcept
{
	/* Nothing to do */
	(void)(cmd);
	(void)(arg);

	return true;
}

/**
 *  \brief Read a word on the line.
 */
bool hsmci_read_word(uint32_t *value) noexcept
{
	/* Wait data available */
	const uint8_t nbytes = (mci_sync_block_size * mci_sync_nb_block - mci_sync_trans_pos < 4)
							 ? (mci_sync_block_size % 4)
							 : 4;

	if (mci_sync_trans_pos % mci_sync_block_size == 0)
	{
		do
		{
			const uint32_t sr = hw->EISTR.reg;
			if (sr & (SDHC_EISTR_DATTEO | SDHC_EISTR_DATCRC | SDHC_EISTR_DATEND))
			{
				hsmci_reset_cmdinh();
				return false;
			}
		} while ((hw->NISTR.reg & SDHC_NISTR_BRDRDY) == 0);
		hw->NISTR.reg |= SDHC_NISTR_BRDRDY;
	}

	/* Read data */
	{
		const uint32_t sr = hw->BDPR.reg;
		switch (nbytes)
		{
		case 4:
			value[0] = sr;
			break;
		case 3:
			value[0] = sr & 0xFFFFFF;
			break;
		case 2:
			value[0] = sr & 0xFFFF;
			break;
		case 1:
			value[0] = sr & 0xFF;
			break;
		}
	}
	mci_sync_trans_pos += nbytes;

	if (((uint64_t)mci_sync_block_size * mci_sync_nb_block) > mci_sync_trans_pos)
	{
		return true;
	}

	/* Wait end of transfer */
	const uint32_t startedWaitingAt = millis();
	do
	{
		const uint32_t sr = hw->EISTR.reg;
		if (sr & (SDHC_EISTR_DATTEO | SDHC_EISTR_DATCRC | SDHC_EISTR_DATEND))
		{
			hsmci_reset_cmdinh();
			return false;
		}
		if (millis() - startedWaitingAt > 100)
		{
//			debugPrintf("SD hang, cmd=%" PRIx32 " cmdr=%" PRIx32 " NISTR=%04x EISTR=%04x\n", cmd, cmdr, hw->NISTR.reg, hw->EISTR.reg);
			hsmci_reset_all();
			return false;
		}
	} while ((hw->NISTR.reg & SDHC_NISTR_TRFC) == 0);
	hw->NISTR.reg |= SDHC_NISTR_TRFC;
	return true;
}

/**
 *  \brief Write a word on the line
 */
bool hsmci_write_word(uint32_t value) noexcept
{
	/* Wait data available */
	uint8_t nbytes = 4; //( mci_dev->mci_sync_block_size & 0x3 ) ? 1 : 4;
	if (mci_sync_trans_pos % mci_sync_block_size == 0)
	{
		do
		{
			const uint32_t sr = hw->EISTR.reg;
			if (sr & (SDHC_EISTR_DATTEO | SDHC_EISTR_DATCRC | SDHC_EISTR_DATEND))
			{
				hsmci_reset_cmdinh();
				return false;
			}
		} while ((hw->NISTR.reg & SDHC_NISTR_BWRRDY) == 0);
		hw->NISTR.reg |= SDHC_NISTR_BWRRDY;
	}
	/* Write data */
	hw->BDPR.reg = value;
	mci_sync_trans_pos += nbytes;

	if (((uint64_t)mci_sync_block_size * mci_sync_nb_block) > mci_sync_trans_pos)
	{
		return true;
	}

	/* Wait end of transfer */
	const uint32_t startedWaitingAt = millis();
	do
	{
		const uint32_t sr = hw->EISTR.reg;
		if (sr & (SDHC_EISTR_DATTEO | SDHC_EISTR_DATCRC | SDHC_EISTR_DATEND))
		{
			hsmci_reset_cmdinh();
			return false;
		}
		if (millis() - startedWaitingAt > 100)
		{
//			debugPrintf("SD hang, cmd=%" PRIx32 " cmdr=%" PRIx32 " NISTR=%04x EISTR=%04x\n", cmd, cmdr, hw->NISTR.reg, hw->EISTR.reg);
			hsmci_reset_all();
			return false;
		}
	} while ((hw->NISTR.reg & SDHC_NISTR_TRFC) == 0);
	hw->NISTR.reg |= SDHC_NISTR_TRFC;
	return true;
}

/**
 *  \brief Start a read blocks transfer on the line
 *  Note: The driver will use the DMA available to speed up the transfer.
 */
bool hsmci_start_read_blocks(void *dst, uint16_t nb_block) noexcept
{
	if (nb_block != 0)
	{
		const bool ok = WaitForDmaComplete();
		if (!ok)
		{
			hsmci_reset_all();
			return false;
		}
	}

	return true;
}

/**
 *  \brief Start a write blocks transfer on the line
 *  Note: The driver will use the DMA available to speed up the transfer.
 */
bool hsmci_start_write_blocks(const void *src, uint16_t nb_block) noexcept
{
	if (nb_block != 0)
	{
		const bool ok = WaitForDmaComplete();
		if (!ok)
		{
			hsmci_reset_all();
			return false;
		}
	}

	return true;
}

/**
 *  \brief Wait the end of transfer initiated by mci_start_read_blocks()
 */
bool hsmci_wait_end_of_read_blocks() noexcept
{
	/* Always return true for sync read blocks */
	return true;
}

/**
 *  \brief Wait the end of transfer initiated by mci_start_write_blocks()
 */
bool hsmci_wait_end_of_write_blocks() noexcept
{
	/* Always return true for sync write blocks */
	return true;
}

#ifdef RTOS

void SDHC_ISR() noexcept
{
	hw->NISIER.reg = 0;					// disable normal interrupts
	hw->EISIER.reg = 0;					// disable error interrupts
	if (sdhcWaitingTask != nullptr)
	{
		TaskBase::GiveFromISR(sdhcWaitingTask);
		sdhcWaitingTask = nullptr;
	}
}

#endif

#endif	// SUPPORT_SDHC
