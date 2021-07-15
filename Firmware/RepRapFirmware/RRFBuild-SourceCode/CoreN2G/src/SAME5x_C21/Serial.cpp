/*
 * Serial.cpp - simple serial driver for sending messages to an attached PanelDue
 *
 *  Created on: 9 Aug 2019
 *      Author: David
 */

#include "Serial.h"

#include <peripheral_clk_config.h>
#include <hal_gpio.h>
#include <RTOSIface/RTOSIface.h>

#if SAME5x
# include <hri_sercom_e54.h>
#elif SAMC21
# include <hri_sercom_c21.h>
#else
# error Unsupported processor
#endif

constexpr uint32_t DiagBaudRate = 57600;		// the baud rate we default to

void Serial::EnableSercomClock(uint8_t sercomNumber) noexcept
{
	struct SercomClockParams
	{
		uint8_t gclkFastIndex;
		uint8_t gclkSlowIndex;
		volatile uint32_t& mclkMaskReg;
		uint32_t mcklBitVal;
	};

	static const SercomClockParams SercomClockTable[] =
	{
#if SAME5x
		{ SERCOM0_GCLK_ID_CORE, SERCOM0_GCLK_ID_SLOW, MCLK->APBAMASK.reg, MCLK_APBAMASK_SERCOM0 },
		{ SERCOM1_GCLK_ID_CORE, SERCOM1_GCLK_ID_SLOW, MCLK->APBAMASK.reg, MCLK_APBAMASK_SERCOM1 },
		{ SERCOM2_GCLK_ID_CORE, SERCOM2_GCLK_ID_SLOW, MCLK->APBBMASK.reg, MCLK_APBBMASK_SERCOM2 },
		{ SERCOM3_GCLK_ID_CORE, SERCOM3_GCLK_ID_SLOW, MCLK->APBBMASK.reg, MCLK_APBBMASK_SERCOM3 },
		{ SERCOM4_GCLK_ID_CORE, SERCOM4_GCLK_ID_SLOW, MCLK->APBDMASK.reg, MCLK_APBDMASK_SERCOM4 },
		{ SERCOM5_GCLK_ID_CORE, SERCOM5_GCLK_ID_SLOW, MCLK->APBDMASK.reg, MCLK_APBDMASK_SERCOM5 },
		{ SERCOM6_GCLK_ID_CORE, SERCOM6_GCLK_ID_SLOW, MCLK->APBDMASK.reg, MCLK_APBDMASK_SERCOM6 },
		{ SERCOM7_GCLK_ID_CORE, SERCOM7_GCLK_ID_SLOW, MCLK->APBDMASK.reg, MCLK_APBDMASK_SERCOM7 },
#elif SAMC21
		{ SERCOM0_GCLK_ID_CORE, SERCOM0_GCLK_ID_SLOW, MCLK->APBCMASK.reg, MCLK_APBCMASK_SERCOM0 },
		{ SERCOM1_GCLK_ID_CORE, SERCOM1_GCLK_ID_SLOW, MCLK->APBCMASK.reg, MCLK_APBCMASK_SERCOM1 },
		{ SERCOM2_GCLK_ID_CORE, SERCOM2_GCLK_ID_SLOW, MCLK->APBCMASK.reg, MCLK_APBCMASK_SERCOM2 },
		{ SERCOM3_GCLK_ID_CORE, SERCOM3_GCLK_ID_SLOW, MCLK->APBCMASK.reg, MCLK_APBCMASK_SERCOM3 },
		{ SERCOM4_GCLK_ID_CORE, SERCOM4_GCLK_ID_SLOW, MCLK->APBCMASK.reg, MCLK_APBCMASK_SERCOM4 },
		{ SERCOM5_GCLK_ID_CORE, SERCOM5_GCLK_ID_SLOW, MCLK->APBCMASK.reg, MCLK_APBCMASK_SERCOM5 },
#else
# error Unsupported processor
#endif
	};

	if (sercomNumber < ARRAY_SIZE(SercomClockTable))
	{
		const SercomClockParams p = SercomClockTable[sercomNumber];
		GCLK->PCHCTRL[p.gclkFastIndex].reg = GCLK_PCHCTRL_GEN(SercomFastGclkNum) | GCLK_PCHCTRL_CHEN;
		GCLK->PCHCTRL[p.gclkSlowIndex].reg = GCLK_PCHCTRL_GEN(SercomSlowGclkNum) | GCLK_PCHCTRL_CHEN;
		p.mclkMaskReg |= p.mcklBitVal;
	}
}

// Initialise the serial port. This does not set up the I/O pins.
void Serial::InitUart(uint8_t sercomNumber, uint32_t baudRate, uint8_t rxPad
#if SAME5x
	, bool use32bitMode
#endif
	) noexcept
{
	EnableSercomClock(sercomNumber);
	Sercom * const sercom = GetSercom(sercomNumber);

	const uint32_t ctrla = (1u << SERCOM_USART_CTRLA_DORD_Pos)				// MSB first
						 | (0u << SERCOM_USART_CTRLA_CPOL_Pos)				// use rising clock edge
						 | (0u << SERCOM_USART_CTRLA_CMODE_Pos)				// async mode
						 | (0u << SERCOM_USART_CTRLA_FORM_Pos)				// usart frame, no parity
						 | (0u << SERCOM_USART_CTRLA_SAMPA_Pos)				// sample on clocks 7-8-9
						 | ((uint32_t)rxPad << SERCOM_USART_CTRLA_RXPO_Pos)	// receive data pad
						 | (0u << SERCOM_USART_CTRLA_TXPO_Pos)				// transmit on pad 0
						 | (0u << SERCOM_USART_CTRLA_SAMPR_Pos)				// 16x over sampling, normal baud rate generation
#if SAME5x
						 | (0u << SERCOM_USART_CTRLA_RXINV_Pos)				// don't invert receive data
						 | (0u << SERCOM_USART_CTRLA_TXINV_Pos)				// don't invert transmitted data
#endif
						 | (0u << SERCOM_USART_CTRLA_IBON_Pos)				// don't report buffer overflow early
						 | (0u << SERCOM_USART_CTRLA_RUNSTDBY_Pos)			// don't clock during standby
						 | (1u << SERCOM_USART_CTRLA_MODE_Pos)				// use internal clock
						 | (0u << SERCOM_USART_CTRLA_ENABLE_Pos)			// not enabled
						 | (0u << SERCOM_USART_CTRLA_SWRST_Pos);			// no reset
	if (!hri_sercomusart_is_syncing(sercom, SERCOM_USART_SYNCBUSY_SWRST))
	{
		const uint32_t mode = ctrla & SERCOM_USART_CTRLA_MODE_Msk;
		if (hri_sercomusart_get_CTRLA_reg(sercom, SERCOM_USART_CTRLA_ENABLE))
		{
			hri_sercomusart_clear_CTRLA_ENABLE_bit(sercom);
			hri_sercomusart_wait_for_sync(sercom, SERCOM_USART_SYNCBUSY_ENABLE);
		}
		hri_sercomusart_write_CTRLA_reg(sercom, SERCOM_USART_CTRLA_SWRST | mode);
	}
	hri_sercomusart_wait_for_sync(sercom, SERCOM_USART_SYNCBUSY_SWRST);

	sercom->USART.CTRLA.reg = ctrla;
	sercom->USART.CTRLB.reg = SERCOM_USART_CTRLB_TXEN | SERCOM_USART_CTRLB_RXEN;
#if SAME5x
	sercom->USART.CTRLC.reg = (use32bitMode) ? SERCOM_USART_CTRLC_DATA32B(3) : 0u;
#else
	sercom->USART.CTRLC.reg = 0u;
#endif
	const uint32_t baudReg = 65536u - (((uint64_t)65536 * 16 * baudRate)/SercomFastGclkFreq);
	sercom->USART.BAUD.reg = baudReg;
	hri_sercomusart_set_CTRLA_ENABLE_bit(sercom);
	hri_sercomusart_wait_for_sync(sercom, SERCOM_USART_SYNCBUSY_ENABLE);
}

// Undo the initialisation, so that when we jump into the main firmware the USART can be initialised again
void Serial::Disable(uint8_t sercomNumber) noexcept
{
	Sercom * const sercom = GetSercom(sercomNumber);
	hri_sercomusart_clear_CTRLA_ENABLE_bit(sercom);
	hri_sercomusart_set_CTRLA_SWRST_bit(sercom);
}

// End
