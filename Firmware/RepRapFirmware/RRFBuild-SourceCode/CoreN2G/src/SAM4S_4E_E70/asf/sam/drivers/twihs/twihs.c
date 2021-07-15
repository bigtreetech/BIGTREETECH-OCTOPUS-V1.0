/**
 * \file
 *
 * \brief Two-Wire Interface (TWIHS) driver for SAM.
 *
 * Copyright (c) 2013-2018 Microchip Technology Inc. and its subsidiaries.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "twihs.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \defgroup sam_drivers_twihs_group High-Speed Two-Wire Interface (TWIHS)
 *
 * Driver for the TWIHS (High-Speed Two-Wire Interface). This driver provides access to the main
 * features of the TWIHS controller.
 * The TWIHS interconnects components on a unique two-wire bus.
 * The TWIHS is programmable as a master or a slave with sequential or single-byte access.
 * Multiple master capability is supported.
 * The High Speed of 3.4Mbits per second can be achieved in slave mode only.
 *
 * \par Usage
 *
 * -# Enable the TWIHS peripheral clock in the PMC.
 * -# Enable the required TWIHS PIOs (see pio.h).
 * -# Enable TWIHS master mode by calling twihs_enable_master_mode if it is a master on the I2C bus.
 * -# Configure the TWIHS in master mode by calling twihs_master_init.
 * -# Send data to a slave device on the I2C bus by calling twihs_master_write.
 * -# Receive data from a slave device on the I2C bus by calling the twihs_master_read.
 * -# Enable TWIHS slave mode by calling twihs_enable_slave_mode if it is a slave on the I2C bus.
 * -# Configure the TWIHS in slave mode by calling twihs_slave_init.
 *
 * @{
 */

/* Low level time limit of I2C Fast Mode. */
#define LOW_LEVEL_TIME_LIMIT   384000
#define I2C_FAST_MODE_SPEED    400000
#define TWIHS_CLK_DIVIDER      2
#define TWIHS_CLK_CALC_ARGU    3
#define TWIHS_CLK_DIV_MAX      0xFF
#define TWIHS_CLK_DIV_MIN      7

/**
 * \brief Enable TWIHS master mode.
 *
 * \param p_twihs Pointer to a TWIHS instance.
 */
void twihs_enable_master_mode(Twihs *p_twihs)
{
	/* Set Master Disable bit and Slave Disable bit */
	p_twihs->TWIHS_CR = TWIHS_CR_MSDIS;
	p_twihs->TWIHS_CR = TWIHS_CR_SVDIS;

	/* Set Master Enable bit */
	p_twihs->TWIHS_CR = TWIHS_CR_MSEN;
}

/**
 * \brief Disable TWIHS master mode.
 *
 * \param p_twihs Pointer to a TWIHS instance.
 */
void twihs_disable_master_mode(Twihs *p_twihs)
{
	/* Set Master Disable bit */
	p_twihs->TWIHS_CR = TWIHS_CR_MSDIS;
}

/**
 * \brief Initialize TWIHS master mode.
 *
 * \param p_twihs Pointer to a TWIHS instance.
 * \param p_opt Options for initializing the TWIHS module (see \ref twihs_options_t).
 *
 * \return TWIHS_SUCCESS if initialization is complete, error code otherwise.
 */
uint32_t twihs_master_init(Twihs *p_twihs, const twihs_options_t *p_opt)
{
	uint32_t status = TWIHS_SUCCESS;

	/* Disable TWIHS interrupts */
	p_twihs->TWIHS_IDR = ~0UL;

	/* Dummy read in status register */
	p_twihs->TWIHS_SR;

	/* Reset TWIHS peripheral */
	twihs_reset(p_twihs);

	twihs_enable_master_mode(p_twihs);

	/* Select the speed */
	if (twihs_set_speed(p_twihs, p_opt->speed, p_opt->master_clk) == FAIL) {
		/* The desired speed setting is rejected */
		status = TWIHS_INVALID_ARGUMENT;
	}

	return status;
}

/**
 * \brief Set the I2C bus speed in conjunction with the clock frequency.
 *
 * \param p_twihs Pointer to a TWIHS instance.
 * \param ul_speed The desired I2C bus speed (in Hz).
 * \param ul_mck Main clock of the device (in Hz).
 *
 * \retval PASS New speed setting is accepted.
 * \retval FAIL New speed setting is rejected.
 */
uint32_t twihs_set_speed(Twihs *p_twihs, uint32_t ul_speed, uint32_t ul_mck)
{
	uint32_t ckdiv = 0;
	uint32_t c_lh_div;
	uint32_t cldiv, chdiv;

	/* High-Speed can be only used in slave mode, 400k is the max speed allowed for master */
	if (ul_speed > I2C_FAST_MODE_SPEED) {
		return FAIL;
	}

	/* Low level time not less than 1.3us of I2C Fast Mode. */
	if (ul_speed > LOW_LEVEL_TIME_LIMIT) {
		/* Low level of time fixed for 1.3us. */
		cldiv = ul_mck / (LOW_LEVEL_TIME_LIMIT * TWIHS_CLK_DIVIDER) - TWIHS_CLK_CALC_ARGU;
		chdiv = ul_mck / ((ul_speed + (ul_speed - LOW_LEVEL_TIME_LIMIT)) * TWIHS_CLK_DIVIDER) - TWIHS_CLK_CALC_ARGU;
		
		/* cldiv must fit in 8 bits, ckdiv must fit in 3 bits */
		while ((cldiv > TWIHS_CLK_DIV_MAX) && (ckdiv < TWIHS_CLK_DIV_MIN)) {
			/* Increase clock divider */
			ckdiv++;
			/* Divide cldiv value */
			cldiv /= TWIHS_CLK_DIVIDER;
		}
		/* chdiv must fit in 8 bits, ckdiv must fit in 3 bits */
		while ((chdiv > TWIHS_CLK_DIV_MAX) && (ckdiv < TWIHS_CLK_DIV_MIN)) {
			/* Increase clock divider */
			ckdiv++;
			/* Divide cldiv value */
			chdiv /= TWIHS_CLK_DIVIDER;
		}

		/* set clock waveform generator register */
		p_twihs->TWIHS_CWGR =
				TWIHS_CWGR_CLDIV(cldiv) | TWIHS_CWGR_CHDIV(chdiv) |
				TWIHS_CWGR_CKDIV(ckdiv);
	} else {
		c_lh_div = ul_mck / (ul_speed * TWIHS_CLK_DIVIDER) - TWIHS_CLK_CALC_ARGU;

		/* cldiv must fit in 8 bits, ckdiv must fit in 3 bits */
		while ((c_lh_div > TWIHS_CLK_DIV_MAX) && (ckdiv < TWIHS_CLK_DIV_MIN)) {
			/* Increase clock divider */
			ckdiv++;
			/* Divide cldiv value */
			c_lh_div /= TWIHS_CLK_DIVIDER;
		}

		/* set clock waveform generator register */
		p_twihs->TWIHS_CWGR =
				TWIHS_CWGR_CLDIV(c_lh_div) | TWIHS_CWGR_CHDIV(c_lh_div) |
				TWIHS_CWGR_CKDIV(ckdiv);
	}

	return PASS;
}

/**
 * \brief Test if a chip answers a given I2C address.
 *
 * \param p_twihs Pointer to a TWIHS instance.
 * \param uc_slave_addr Address of the remote chip to search for.
 *
 * \return TWIHS_SUCCESS if a chip was found, error code otherwise.
 */
uint32_t twihs_probe(Twihs *p_twihs, uint8_t uc_slave_addr)
{
	twihs_packet_t packet;
	uint8_t data = 0;

	/* Data to send */
	packet.buffer = &data;
	/* Data length */
	packet.length = 1;
	/* Slave chip address */
	packet.chip = (uint32_t) uc_slave_addr;
	/* Internal chip address */
	packet.addr[0] = 0;
	/* Address length */
	packet.addr_length = 0;

	/* Perform a master write access */
	return (twihs_master_write(p_twihs, &packet));
}


/**
 * \internal
 * \brief Construct the TWIHS module address register field
 *
 * The TWIHS module address register is sent out MSB first. And the size controls
 * which byte is the MSB to start with.
 *
 * Please see the device datasheet for details on this.
 */
static uint32_t twihs_mk_addr(const uint8_t *addr, int len)
{
	uint32_t val;

	if (len == 0)
		return 0;

	val = addr[0];
	if (len > 1) {
		val <<= 8;
		val |= addr[1];
	}
	if (len > 2) {
		val <<= 8;
		val |= addr[2];
	}
	return val;
}

/**
 * \brief Read multiple bytes from a TWIHS compatible slave device.
 *
 * \note This function will NOT return until all data has been read or error occurs.
 *
 * \param p_twihs Pointer to a TWIHS instance.
 * \param p_packet Packet information and data (see \ref twihs_packet_t).
 *
 * \return TWIHS_SUCCESS if all bytes were read, error code otherwise.
 */
uint32_t twihs_master_read(Twihs *p_twihs, twihs_packet_t *p_packet)
{
	uint32_t status, cnt = p_packet->length;
	uint8_t *buffer = p_packet->buffer;
	uint32_t timeout = TWIHS_TIMEOUT;

	/* Check argument */
	if (cnt == 0) {
		return TWIHS_INVALID_ARGUMENT;
	}

	/* Set read mode, slave address and 3 internal address byte lengths */
	p_twihs->TWIHS_MMR = 0;
	p_twihs->TWIHS_MMR = TWIHS_MMR_MREAD | TWIHS_MMR_DADR(p_packet->chip) |
			((p_packet->addr_length << TWIHS_MMR_IADRSZ_Pos) &
			TWIHS_MMR_IADRSZ_Msk);

	/* Set internal address for remote chip */
	p_twihs->TWIHS_IADR = 0;
	p_twihs->TWIHS_IADR = twihs_mk_addr(p_packet->addr, p_packet->addr_length);

	/* Send a START Condition */
	p_twihs->TWIHS_CR = TWIHS_CR_START;

	while (cnt > 0) {
		status = p_twihs->TWIHS_SR;
		if (status & TWIHS_SR_NACK) {
			return TWIHS_RECEIVE_NACK;
		}
		if (!timeout--) {
			return TWIHS_ERROR_TIMEOUT;
		}
		/* Last byte ? */
		if (cnt == 1) {
			p_twihs->TWIHS_CR = TWIHS_CR_STOP;
		}

		if (!(status & TWIHS_SR_RXRDY)) {
			continue;
		}
		*buffer++ = p_twihs->TWIHS_RHR;

		cnt--;
		timeout = TWIHS_TIMEOUT;
	}

	while (!(p_twihs->TWIHS_SR & TWIHS_SR_TXCOMP)) {
	}

	p_twihs->TWIHS_SR;

	return TWIHS_SUCCESS;
}

/**
 * \brief Write multiple bytes to a TWIHS compatible slave device.
 *
 * \note This function will NOT return until all data has been written or error occurred.
 *
 * \param p_twihs Pointer to a TWIHS instance.
 * \param p_packet Packet information and data (see \ref twihs_packet_t).
 *
 * \return TWIHS_SUCCESS if all bytes were written, error code otherwise.
 */
uint32_t twihs_master_write(Twihs *p_twihs, twihs_packet_t *p_packet)
{
	uint32_t status, cnt = p_packet->length;
	uint8_t *buffer = p_packet->buffer;

	/* Check argument */
	if (cnt == 0) {
		return TWIHS_INVALID_ARGUMENT;
	}

	/* Set write mode, slave address and 3 internal address byte lengths */
	p_twihs->TWIHS_MMR = 0;
	p_twihs->TWIHS_MMR = TWIHS_MMR_DADR(p_packet->chip) |
			((p_packet->addr_length << TWIHS_MMR_IADRSZ_Pos) &
			TWIHS_MMR_IADRSZ_Msk);

	/* Set internal address for remote chip */
	p_twihs->TWIHS_IADR = 0;
	p_twihs->TWIHS_IADR = twihs_mk_addr(p_packet->addr, p_packet->addr_length);

	/* Send all bytes */
	while (cnt > 0) {
		status = p_twihs->TWIHS_SR;
		if (status & TWIHS_SR_NACK) {
			return TWIHS_RECEIVE_NACK;
		}

		if (!(status & TWIHS_SR_TXRDY)) {
			continue;
		}
		p_twihs->TWIHS_THR = *buffer++;

		cnt--;
	}

	while (1) {
		status = p_twihs->TWIHS_SR;
		if (status & TWIHS_SR_NACK) {
			return TWIHS_RECEIVE_NACK;
		}

		if (status & TWIHS_SR_TXRDY) {
			break;
		}
	}

	p_twihs->TWIHS_CR = TWIHS_CR_STOP;

	while (!(p_twihs->TWIHS_SR & TWIHS_SR_TXCOMP)) {
	}

	return TWIHS_SUCCESS;
}

/**
 * \brief Enable TWIHS interrupts.
 *
 * \param p_twihs Pointer to a TWIHS instance.
 * \param ul_sources Interrupts to be enabled.
 */
void twihs_enable_interrupt(Twihs *p_twihs, uint32_t ul_sources)
{
	/* Enable the specified interrupts */
	p_twihs->TWIHS_IER = ul_sources;
}

/**
 * \brief Disable TWIHS interrupts.
 *
 * \param p_twihs Pointer to a TWIHS instance.
 * \param ul_sources Interrupts to be disabled.
 */
void twihs_disable_interrupt(Twihs *p_twihs, uint32_t ul_sources)
{
	/* Disable the specified interrupts */
	p_twihs->TWIHS_IDR = ul_sources;
	/* Dummy read */
	p_twihs->TWIHS_SR;
}

/**
 * \brief Get TWIHS interrupt status.
 *
 * \param p_twihs Pointer to a TWIHS instance.
 *
 * \retval TWIHS interrupt status.
 */
uint32_t twihs_get_interrupt_status(Twihs *p_twihs)
{
	return p_twihs->TWIHS_SR;
}

/**
 * \brief Read TWIHS interrupt mask.
 *
 * \param p_twihs Pointer to a TWIHS instance.
 *
 * \return The interrupt mask value.
 */
uint32_t twihs_get_interrupt_mask(Twihs *p_twihs)
{
	return p_twihs->TWIHS_IMR;
}

/**
 * \brief Reads a byte from the TWIHS bus.
 *
 * \param p_twihs Pointer to a TWIHS instance.
 *
 * \return The byte read.
 */
uint8_t twihs_read_byte(Twihs *p_twihs)
{
	return p_twihs->TWIHS_RHR;
}

/**
 * \brief Sends a byte of data to one of the TWIHS slaves on the bus.
 *
 * \param p_twihs Pointer to a TWIHS instance.
 * \param byte The byte to send.
 */
void twihs_write_byte(Twihs *p_twihs, uint8_t uc_byte)
{
	p_twihs->TWIHS_THR = uc_byte;
}

/**
 * \brief Enable TWIHS slave mode.
 *
 * \param p_twihs Pointer to a TWIHS instance.
 */
void twihs_enable_slave_mode(Twihs *p_twihs)
{
	/* Set Master Disable bit and Slave Disable bit */
	p_twihs->TWIHS_CR = TWIHS_CR_MSDIS;
	p_twihs->TWIHS_CR = TWIHS_CR_SVDIS;

	/* Set Slave Enable bit */
	p_twihs->TWIHS_CR = TWIHS_CR_SVEN;
}

/**
 * \brief Disable TWIHS slave mode.
 *
 * \param p_twihs Pointer to a TWIHS instance.
 */
void twihs_disable_slave_mode(Twihs *p_twihs)
{
	/* Set Slave Disable bit */
	p_twihs->TWIHS_CR = TWIHS_CR_SVDIS;
}

/**
 * \brief Initialize TWIHS slave mode.
 *
 * \param p_twihs Pointer to a TWIHS instance.
 * \param ul_device_addr Device address of the SAM slave device on the I2C bus.
 */
void twihs_slave_init(Twihs *p_twihs, uint32_t ul_device_addr)
{
	/* Disable TWIHS interrupts */
	p_twihs->TWIHS_IDR = ~0UL;
	p_twihs->TWIHS_SR;

	/* Reset TWIHS */
	twihs_reset(p_twihs);

	/* Set slave address in slave mode */
	p_twihs->TWIHS_SMR = TWIHS_SMR_SADR(ul_device_addr);

	/* Enable slave mode */
	twihs_enable_slave_mode(p_twihs);
}

/**
 * \brief Set TWIHS slave address.
 *
 * \param p_twihs Pointer to a TWIHS instance.
 * \param ul_device_addr Device address of the SAM slave device on the I2C bus.
 */
void twihs_set_slave_addr(Twihs *p_twihs, uint32_t ul_device_addr)
{
	/* Set slave address */
	p_twihs->TWIHS_SMR = TWIHS_SMR_SADR(ul_device_addr);
}

/**
 * \brief Read data from master.
 *
 * \note This function will NOT return until master sends a STOP condition.
 *
 * \param p_twihs Pointer to a TWIHS instance.
 * \param p_data Pointer to the data buffer where data received will be stored.
 *
 * \return Number of bytes read.
 */
uint32_t twihs_slave_read(Twihs *p_twihs, uint8_t *p_data)
{
	uint32_t status, cnt = 0;

	do {
		status = p_twihs->TWIHS_SR;
		if (status & TWIHS_SR_SVACC) {
			if (!(status & (TWIHS_SR_GACC | TWIHS_SR_SVREAD)) &&
			(status & TWIHS_SR_RXRDY)) {
				*p_data++ = (uint8_t) p_twihs->TWIHS_RHR;
				cnt++;
			}
		} else if ((status & (TWIHS_SR_EOSACC | TWIHS_SR_TXCOMP))
					== (TWIHS_SR_EOSACC | TWIHS_SR_TXCOMP)) {
			break;
		}
	} while (1);

	return cnt;
}

/**
 * \brief Write data to TWIHS bus.
 *
 * \note This function will NOT return until master sends a STOP condition.
 *
 * \param p_twihs Pointer to a TWIHS instance.
 * \param p_data Pointer to the data buffer to be sent.
 *
 * \return Number of bytes written.
 */
uint32_t twihs_slave_write(Twihs *p_twihs, uint8_t *p_data)
{
	uint32_t status, cnt = 0;

	do {
		status = p_twihs->TWIHS_SR;
		if (status & TWIHS_SR_SVACC) {
			if (!(status & (TWIHS_SR_GACC | TWIHS_SR_NACK)) &&
			((status & (TWIHS_SR_SVREAD | TWIHS_SR_TXRDY))
			== (TWIHS_SR_SVREAD | TWIHS_SR_TXRDY))) {
				p_twihs->TWIHS_THR = *p_data++;
				cnt++;
			}
		} else if ((status & (TWIHS_SR_EOSACC | TWIHS_SR_TXCOMP))
					== (TWIHS_SR_EOSACC | TWIHS_SR_TXCOMP)) {
			break;
		}
	} while (1);

	return cnt;
}

/**
 * \brief Reset TWIHS.
 *
 * \param p_twihs Pointer to a TWIHS instance.
 */
void twihs_reset(Twihs *p_twihs)
{
	/* Set SWRST bit to reset TWIHS peripheral */
	p_twihs->TWIHS_CR = TWIHS_CR_SWRST;
	p_twihs->TWIHS_RHR;
}

#if !(SAMV70 || SAMV71 || SAME70 || SAMS70)
/**
 * \brief Get TWIHS PDC base address.
 *
 * \param p_twihs Pointer to a TWIHS instance.
 *
 * \return TWIHS PDC registers base for PDC driver to access.
 */
Pdc *twihs_get_pdc_base(Twihs *p_twihs)
{
	Pdc *p_pdc_base = NULL;

	if (p_twihs == TWI0) {
		p_pdc_base = PDC_TWI0;
	} else {
		Assert(false);
	}

	return p_pdc_base;
}
#endif

/**
 * \brief Enables/Disables write protection mode.
 *
 * \param p_twihs Pointer to a TWIHS instance.
 * \param flag ture for enable, false for disable.
 */
void twihs_set_write_protection(Twihs *p_twihs, bool flag)
{
	if (flag) {
		p_twihs->TWIHS_WPMR = TWIHS_WPMR_WPKEY_PASSWD | TWIHS_WPMR_WPEN;
	} else {
		p_twihs->TWIHS_WPMR = TWIHS_WPMR_WPKEY_PASSWD;
	}
}

/**
 * \brief Read the write protection status.
 *
 * \param p_twihs Pointer to a TWIHS instance.
 * \param p_status Pointer to save the status.
 */
void twihs_read_write_protection_status(Twihs *p_twihs, uint32_t *p_status)
{
	*p_status = p_twihs->TWIHS_WPSR;
}

/**
 * \brief Set the prescaler, TLOW:SEXT, TLOW:MEXT and clock high max cycles for SMBUS mode.
 *
 * \param p_twihs   Base address of the TWIHS instance.
 * \param ul_timing Parameter for prescaler, TLOW:SEXT, TLOW:MEXT and clock high max cycles.
 */
void twihs_smbus_set_timing(Twihs *p_twihs, uint32_t ul_timing)
{
	p_twihs->TWIHS_SMBTR = ul_timing;;
}

#if !(SAMV70 || SAMV71 || SAME70 || SAMS70)
/**
 * \brief Set length/direction/PEC for alternative command mode.
 *
 * \param p_twihs   Base address of the TWIHS instance.
 * \param ul_alt_cmd Alternative command parameters.
 */
void twihs_set_alternative_command(Twihs *p_twihs, uint32_t ul_alt_cmd)
{
	p_twihs->TWIHS_ACR = ul_alt_cmd;;
}
#endif

/**
 * \brief Set the filter for TWIHS.
 *
 * \param p_twihs   Base address of the TWIHS instance.
 * \param ul_filter   Filter value.
 */
void twihs_set_filter(Twihs *p_twihs, uint32_t ul_filter)
{
	p_twihs->TWIHS_FILTR = ul_filter;;
}

/**
 * \brief A mask can be applied on the slave device address in slave mode in order to allow multiple
 * address answer. For each bit of the MASK field set to one the corresponding SADR bit will be masked.
 *
 * \param p_twihs   Base address of the TWIHS instance.
 * \param ul_mask  Mask value.
 */
void twihs_mask_slave_addr(Twihs *p_twihs, uint32_t ul_mask)
{
	p_twihs->TWIHS_SMR |= TWIHS_SMR_MASK(ul_mask);
}

#if (SAMG53 || SAMG54 || SAMV70 || SAMV71 || SAME70 || SAMS70)
/**
 * \brief Set sleepwalking match mode.
 *
 * \param p_twihs Pointer to a TWIHS instance.
 * \param ul_matching_addr1   Address 1 value.
 * \param ul_matching_addr2   Address 2 value.
 * \param ul_matching_addr3   Address 3 value.
 * \param ul_matching_data   Data value.
 * \param flag1 ture for set, false for no.
 * \param flag2 ture for set, false for no.
 * \param flag3 ture for set, false for no.
 * \param flag ture for set, false for no.
 */
void twihs_set_sleepwalking(Twihs *p_twihs,
		uint32_t ul_matching_addr1, bool flag1,
		uint32_t ul_matching_addr2, bool flag2,
		uint32_t ul_matching_addr3, bool flag3,
		uint32_t ul_matching_data, bool flag)
{
	uint32_t temp = 0;

	if (flag1) {
		temp |= TWIHS_SWMR_SADR1(ul_matching_addr1);
	}

	if (flag2) {
		temp |= TWIHS_SWMR_SADR2(ul_matching_addr2);
	}

	if (flag3) {
		temp |= TWIHS_SWMR_SADR3(ul_matching_addr3);
	}

	if (flag) {
		temp |= TWIHS_SWMR_DATAM(ul_matching_data);
	}

	p_twihs->TWIHS_SWMR = temp;
}
#endif
//@}

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond
