/**
 *
 * \file
 *
 * \brief SAM Advanced Encryption Standard driver.
 *
 * This file defines a useful set of functions for the AES on SAM devices.
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

#include <aes.h>
#include <sysclk.h>
#include <sleepmgr.h>

/**
 * \internal
 * \brief AES callback function pointer
 */
aes_callback_t aes_callback_pointer[AES_INTERRUPT_SOURCE_NUM];

/**
 * \brief Initializes an AES configuration structure to defaults.
 *
 * Initializes the specified AES configuration structure to a set of
 * known default values.
 *
 * \note This function should be called to initialize <i>all</i> new instances of
 * AES configuration structures before they are further modified by the user
 * application.
 *
 *  The default configuration is as follows:
 *  - Data encryption
 *  - 128-bit AES key size
 *  - 128-bit cipher feedback size
 *  - Manual start mode
 *  - Electronic Codebook (ECB) mode
 *  - Last output data mode is disabled
 *  - No extra delay
 *
 *  \param[out] p_cfg Pointer to an AES configuration structure
 */
void aes_get_config_defaults(
		struct aes_config *const p_cfg)
{
	/* Sanity check arguments */
	Assert(p_cfg);

	/* Default configuration values */
	p_cfg->encrypt_mode = AES_ENCRYPTION;
	p_cfg->key_size = AES_KEY_SIZE_128;
	p_cfg->start_mode = AES_MANUAL_START;
	p_cfg->opmode = AES_ECB_MODE;
	p_cfg->cfb_size = AES_CFB_SIZE_128;
	p_cfg->lod = false;
	p_cfg->gtag_en = false;
	p_cfg->processing_delay = 0;
}

/**
 * \brief Initialize the AES module.
 *
 * \param[out] p_aes Module hardware register base address pointer
 * \param[in] p_cfg  Pointer to an AES configuration structure
 */
void aes_init(
		Aes *const p_aes,
		struct aes_config *const p_cfg)
{
	/* Sanity check arguments */
	Assert(p_aes);
	Assert(p_cfg);

	/* Enable clock for AES */
	sysclk_enable_peripheral_clock(ID_AES);

	/* Perform a software reset */
	aes_reset(p_aes);

	/* Initialize the AES with new configurations */
	aes_set_config(p_aes, p_cfg);

	/* Disable clock for AES */
	sysclk_disable_peripheral_clock(ID_AES);
}

/**
 * \brief Enable the AES module.
 */
void aes_enable(void)
{
	sysclk_enable_peripheral_clock(ID_AES);
	sleepmgr_lock_mode(SLEEPMGR_SLEEP_WFI);
}

/**
 * \brief Disable the AES module.
 */
void aes_disable(void)
{
	sysclk_disable_peripheral_clock(ID_AES);
	sleepmgr_unlock_mode(SLEEPMGR_SLEEP_WFI);
}

/**
 * \brief Configure the AES module.
 *
 * \param[out] p_aes Module hardware register base address pointer
 * \param[in] p_cfg  Pointer to an AES configuration structure
 */
void aes_set_config(
		Aes *const p_aes,
		struct aes_config *const p_cfg)
{
	uint32_t ul_mode = 0;

	/* Validate arguments. */
	Assert(p_aes);
	Assert(p_cfg);
	
	/* Set processing mode */
	if (p_cfg->encrypt_mode) {
		ul_mode |= AES_MR_CIPHER;
	}

	/* Active dual buffer in DMA mode */
	if (p_cfg->start_mode == AES_IDATAR0_START) {
		ul_mode |= AES_MR_DUALBUFF_ACTIVE;
	}

	/* Set start mode */
	ul_mode |= (p_cfg->start_mode << AES_MR_SMOD_Pos);

	/* Set key size */
	ul_mode |= (p_cfg->key_size << AES_MR_KEYSIZE_Pos);

	/* Set Confidentiality mode */
	ul_mode |= (p_cfg->opmode << AES_MR_OPMOD_Pos);

	/* Set CFB size */
	ul_mode |= (p_cfg->cfb_size << AES_MR_CFBS_Pos);

	if (p_cfg->lod) {
		ul_mode |= AES_MR_LOD;
	}

	#if (SAM4C || SAM4CP || SAM4CM || SAMV70 || SAMV71 || SAME70 || SAMS70)
	if ((p_cfg->opmode == AES_GCM_MODE) && (p_cfg->gtag_en == true)) {
		ul_mode |= AES_MR_GTAGEN;
	}
	#endif /* SAM4C || SAM4CP || SAM4CM */

	ul_mode |= AES_MR_PROCDLY(p_cfg->processing_delay);

	ul_mode |= AES_MR_CKEY_PASSWD;

	p_aes->AES_MR = ul_mode;
}

/**
 * \brief Write the 128/192/256-bit cryptographic key.
 *
 * \param[out] p_aes Module hardware register base address pointer
 * \param[in]  p_key Pointer to 4/6/8 contiguous 32-bit words
 *
 * \note The key size depends on the current AES configuration.
 */
void aes_write_key(
		Aes *const p_aes,
		const uint32_t *p_key)
{
	uint32_t i, key_length = 0;

	/* Validate arguments. */
	Assert(p_aes);
	Assert(p_key);
	
	switch ((p_aes->AES_MR & AES_MR_KEYSIZE_Msk) >>
			AES_MR_KEYSIZE_Pos) {
	case 0: /* 128bit cryptographic key */
		key_length = 4;
		break;

	case 1: /* 192bit cryptographic key */
		key_length = 6;
		break;

	case 2: /* 256bit cryptographic key */
		key_length = 8;
		break;

	default:
		break;
	}

	for (i = 0; i < key_length; i++) {
		p_aes->AES_KEYWR[i] = *p_key;
		p_key++;
	}
}

/**
 * \brief Write the initialization vector (for the CBC, CFB, OFB, CTR & GCM
 * cipher modes).
 *
 * \param[out] p_aes   Module hardware register base address pointer
 * \param[in] p_vector Pointer to four contiguous 32-bit words
 */
void aes_write_initvector(
		Aes *const p_aes,
		const uint32_t *p_vector)
{
	uint32_t i;

	/* Validate arguments. */
	Assert(p_aes);
	
	for (i = 0; i < 4; i++) {
		p_aes->AES_IVR[i] = *p_vector;
		p_vector++;
	}
}

/**
 * \brief Write the input data (four consecutive 32-bit words).
 *
 * \param[out] p_aes              Module hardware register base address pointer
 * \param[in] p_input_data_buffer Pointer to an input data buffer
 */
void aes_write_input_data(
		Aes *const p_aes,
		const uint32_t *p_input_data_buffer)
{
	uint32_t i;

	/* Validate arguments. */
	Assert(p_aes);
	Assert(p_input_data_buffer);
	
	for (i = 0; i < 4; i++) {
		p_aes->AES_IDATAR[i] = *p_input_data_buffer;
		p_input_data_buffer++;
	}
}

/**
 * \brief Read the output data.
 *
 * \note The data buffer that holds the processed data must be large enough to hold
 * four consecutive 32-bit words.
 *
 * \param[in] p_aes                 Module hardware register base address pointer
 * \param[in] *p_output_data_buffer Pointer to an output buffer
 */
void aes_read_output_data(
		Aes *const p_aes,
		uint32_t *p_output_data_buffer)
{
	uint32_t i;

	/* Validate arguments. */
	Assert(p_aes);
	Assert(p_output_data_buffer);
	
	for (i = 0; i < 4; i++) {
		*p_output_data_buffer = p_aes->AES_ODATAR[i];
		p_output_data_buffer++;
	}
}

#if SAM4C || SAM4CP || SAM4CM || defined(__DOXYGEN__)
/**
 * \brief Get AES PDC base address.
 *
 * \note This function is only available on SAM4C devices.
 *
 * \param[in] p_aes Module hardware register base address pointer
 *
 * \return The PDC registers base address for the AES module.
 */
Pdc *aes_get_pdc_base(
		Aes *p_aes)
{
	/* Validate arguments. */
	Assert(p_aes);
	
	Pdc *p_pdc_base;
	if (p_aes == AES) {
		p_pdc_base = PDC_AES;
	} else {
		p_pdc_base = NULL;
	}

	return p_pdc_base;
}
#endif /* SAM4C || SAM4CP || SAM4CM || defined(__DOXYGEN__) */

/**
 * \brief Set the AES interrupt callback.
 *
 * \param[out] p_aes    Module hardware register base address pointer
 * \param[in] source    Interrupt source
 * \param[in] callback  Interrupt callback function pointer
 * \param[in] irq_level Interrupt priority level
 */
void aes_set_callback(
		Aes *const p_aes,
		aes_interrupt_source_t source,
		aes_callback_t callback,
		uint8_t irq_level)
{
	/* Validate arguments. */
	Assert(p_aes);
	
	if (source == AES_INTERRUPT_DATA_READY) {
		aes_callback_pointer[0] = callback;
	} else if (source == AES_INTERRUPT_UNSPECIFIED_REGISTER_ACCESS) {
		aes_callback_pointer[1] = callback;
	} 

#if SAM4C || SAM4CP || SAM4CM
	else if (source == AES_INTERRUPT_END_OF_RECEIVE_BUFFER) {
		aes_callback_pointer[2] = callback;
	} else if (source == AES_INTERRUPT_END_OF_TRANSMIT_BUFFER) {
		aes_callback_pointer[3] = callback;
	} else if (source == AES_INTERRUPT_RECEIVE_BUFFER_FULL) {
		aes_callback_pointer[4] = callback;
	} else if (source == AES_INTERRUPT_TRANSMIT_BUFFER_FULL) {
		aes_callback_pointer[5] = callback;
	}
#elif SAMV70 || SAMV71 || SAME70 || SAMS70
	else if ((source == AES_INTERRUPT_TAG_READY)) {
		aes_callback_pointer[2] = callback;
	}
#endif /* SAM4C || SAM4CP || SAM4CM */
	irq_register_handler((IRQn_Type)AES_IRQn, irq_level);
	aes_enable_interrupt(p_aes, source);
}

/**
 * \internal The AES interrupt handler.
 */
void AES_Handler(void)
{
	uint32_t status = aes_read_interrupt_status(AES);
	uint32_t mask = aes_read_interrupt_mask(AES);

	if ((status & AES_ISR_DATRDY) && (mask & AES_IMR_DATRDY)) {
		if (aes_callback_pointer[0]) {
			aes_callback_pointer[0]();
		}
	}

	if ((status & AES_ISR_URAD) && (mask & AES_IMR_URAD)) {
		if (aes_callback_pointer[1]) {
			aes_callback_pointer[1]();
		}
	}

#if SAM4C || SAM4CP || SAM4CM
	if ((status & AES_ISR_ENDRX) && (mask & AES_IMR_ENDRX)) {
		if (aes_callback_pointer[2]) {
			aes_callback_pointer[2]();
		}
	}

	if ((status & AES_ISR_ENDTX) && (mask & AES_IMR_ENDTX)) {
		if (aes_callback_pointer[3]) {
			aes_callback_pointer[3]();
		}
	}

	if ((status & AES_ISR_RXBUFF) && (mask & AES_IMR_RXBUFF)) {
		if (aes_callback_pointer[4]) {
			aes_callback_pointer[4]();
		}
	}

	if ((status & AES_ISR_TXBUFE) && (mask & AES_IMR_TXBUFE)) {
		if (aes_callback_pointer[5]) {
			aes_callback_pointer[5]();
		}
	}
#elif SAMV70 || SAMV71 || SAME70 || SAMS70
	if ((status & AES_IER_TAGRDY) && (mask & AES_IER_TAGRDY)) {
		if (aes_callback_pointer[2]) {
			aes_callback_pointer[2]();
		}
	}
#endif /* SAM4C || SAM4CP || SAM4CM */
}
