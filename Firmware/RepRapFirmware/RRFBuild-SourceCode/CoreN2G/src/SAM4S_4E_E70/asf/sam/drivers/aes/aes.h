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

#ifndef AES_H_INCLUDED
#define AES_H_INCLUDED

/**
 * \defgroup asfdoc_sam_drivers_aes_group SAM4C/4E/V71/V70/S70/E70 Advanced Encryption Standard (AES) Driver
 *
 * This driver for Atmel&reg; | SMART ARM&reg;-based microcontrollers provides an interface for 
 * the configuration and management of the device's Advanced Encryption
 * Standard functionality.
 *
 * The Advanced Encryption Standard module supports all five confidentiality
 * modes of operation for symmetrical key block cipher algorithms (as specified
 * in the NIST Special Publication 800-38A Recommendation):
 * - Electronic Codebook (ECB)
 * - Cipher Block Chaining (CBC)
 * - Output Feedback (OFB)
 * - Cipher Feedback (CFB)
 * - Counter (CTR)
 *
 *
 * Devices from the following series can use this module:
 * - Atmel | SMART SAM4C
 * - Atmel | SMART SAM4E
 * - Atmel | SMART SAMV71
 * - Atmel | SMART SAMV70
 * - Atmel | SMART SAME70
 * - Atmel | SMART SAMS70
 *
 * The outline of this documentation is as follows:
 *  - \ref asfdoc_sam_drivers_aes_prerequisites
 *  - \ref asfdoc_sam_drivers_aes_module_overview
 *  - \ref asfdoc_sam_drivers_aes_special_considerations
 *  - \ref asfdoc_sam_drivers_aes_extra_info
 *  - \ref asfdoc_sam_drivers_aes_examples
 *  - \ref asfdoc_sam_drivers_aes_api_overview
 *
 *
 * \section asfdoc_sam_drivers_aes_prerequisites Prerequisites
 *
 * There are no prerequisites for this module.
 *
 *
 * \section asfdoc_sam_drivers_aes_module_overview Module Overview
 *
 * The Advanced Encryption Standard (AES) module is compliant with the American FIPS
 * (Federal Information Processing Standard) Publication 197 specification.
 *
 * The AES supports all five confidentiality modes of operation for symmetrical
 * key block cipher algorithms (as specified in the NIST Special Publication
 * 800-38A Recommendation) :
 * - Electronic Codebook (ECB)
 * - Cipher Block Chaining (CBC)
 * - Output Feedback (OFB)
 * - Cipher Feedback (CFB)
 * - Counter (CTR)
 *
 * Data transfers both to and from the AES module can occur using the Peripheral
 * DMA Controller (PDC) channels (thus minimizing processor intervention for
 * large data buffer transfers).
 *
 * As soon as the initialization vector, the input data, and the key are
 * configured, the encryption/decryption process may be started. Once the
 * process has completed the encrypted/decrypted data can be read out via
 * registers or through DMA channels.
 *
 *
 * \section asfdoc_sam_drivers_aes_special_considerations Special Considerations
 *
 * \subsection asfdoc_sam_drivers_aes_special_considerations_power Power Management
 * The AES module may be clocked through the Power Management Controller (PMC),
 * in which case the user application must first configure the PMC to enable the
 * AES clock.
 *
 * \subsection asfdoc_sam_drivers_aes_special_considerations_irq Interrupt
 * When using the AES module's interrupt, the configuration of the device's
 * Nested Vectored Interrupt Controller (NVIC) needs to be carried out before
 * the AES module is configured.
 *
 *
 * \section asfdoc_sam_drivers_aes_extra_info Extra Information
 *
 * For extra information, see \ref asfdoc_sam_drivers_aes_extra. This includes:
 *  - \ref asfdoc_sam_drivers_aes_extra_acronyms
 *  - \ref asfdoc_sam_drivers_aes_extra_dependencies
 *  - \ref asfdoc_sam_drivers_aes_extra_errata
 *  - \ref asfdoc_sam_drivers_aes_extra_history
 *
 * \section asfdoc_sam_drivers_aes_examples Examples
 *
 * For a list of examples related to this driver, see
 * \ref asfdoc_sam_drivers_aes_exqsg.
 *
 *
 * \section asfdoc_sam_drivers_aes_api_overview API Overview
 * @{
 */

#include <compiler.h>

#ifdef __cplusplus
extern "C" {
#endif

#if SAM4E || defined(__DOXYGEN__)
/** AES DMAC TX channel interface number. */
#define AES_DMA_TX_IDX 11
/** AES DMAC RX channel interface number. */
#define AES_DMA_RX_IDX 12
#endif

/** AES processing mode. */
enum aes_encrypt_mode {
	AES_DECRYPTION = 0, 	/**< Decryption of data will be performed. */
	AES_ENCRYPTION,			/**< Encryption of data will be performed. */
};

/** AES cryptographic key size. */
enum aes_key_size {
	AES_KEY_SIZE_128 = 0, 	/**< AES key size is 128 bits. */
	AES_KEY_SIZE_192,		/**< AES key size is 192 bits. */
	AES_KEY_SIZE_256,		/**< AES key size is 256 bits. */
};

/** AES start mode. */
enum aes_start_mode {
	AES_MANUAL_START = 0,	/**< Manual start mode. */
	AES_AUTO_START,			/**< Auto start mode. */
	AES_IDATAR0_START,		/**< AES_IDATAR0 access only Auto Mode. */
};

/** AES cipher block mode. */
enum aes_opmode {
	AES_ECB_MODE = 0,		/**< Electronic Codebook (ECB). */
	AES_CBC_MODE,			/**< Cipher Block Chaining (CBC). */
	AES_OFB_MODE,			/**< Output Feedback (OFB). */
	AES_CFB_MODE,			/**< Cipher Feedback (CFB). */
	AES_CTR_MODE,			/**< Counter (CTR). */
	AES_GCM_MODE,			/**< Galois Counter Mode (GCM).*/
};

/** AES Cipher FeedBack (CFB) size. */
enum aes_cfb_size {
	AES_CFB_SIZE_128 = 0,	/**< Cipher feedback data size is 128-bit. */
	AES_CFB_SIZE_64,		/**< Cipher feedback data size is 64-bit. */
	AES_CFB_SIZE_32,		/**< Cipher feedback data size is 32-bit. */
	AES_CFB_SIZE_16,		/**< Cipher feedback data size is 16-bit. */
	AES_CFB_SIZE_8,			/**< Cipher feedback data size is 8-bit. */
};

/** AES interrupt source type. */
typedef enum aes_interrupt_source {
	/** Data ready interrupt.*/
	AES_INTERRUPT_DATA_READY = AES_IER_DATRDY,
	/** Unspecified register access detection interrupt.*/
	AES_INTERRUPT_UNSPECIFIED_REGISTER_ACCESS = AES_IER_URAD,
#if SAM4C || SAM4CP || SAM4CM || defined(__DOXYGEN__)
	/** End of receive buffer interrupt (SAM4C devices only). */
	AES_INTERRUPT_END_OF_RECEIVE_BUFFER = AES_IER_ENDRX,
	/** End of transmit buffer interrupt (SAM4C devices only). */
	AES_INTERRUPT_END_OF_TRANSMIT_BUFFER = AES_IER_ENDTX,
	/** Receive buffer full interrupt (SAM4C devices only). */
	AES_INTERRUPT_RECEIVE_BUFFER_FULL = AES_IER_RXBUFF,
	/** Transmit buffer empty interrupt (SAM4C devices only). */
	AES_INTERRUPT_TRANSMIT_BUFFER_FULL = AES_IER_TXBUFE,
#elif SAMV70 || SAMV71 || SAME70 || SAMS70 
	AES_INTERRUPT_TAG_READY = AES_IER_TAGRDY,
#endif /* SAM4C || SAM4CP || SAM4CM || defined(__DOXYGEN__) */
} aes_interrupt_source_t;

#if SAM4E
/** \internal Max number of interrupt sources. */
#define AES_INTERRUPT_SOURCE_NUM 2
#elif SAM4C || SAM4CP || SAM4CM
/** \internal Max number of interrupt sources. */
#define AES_INTERRUPT_SOURCE_NUM 6
#elif SAMV70 || SAMV71 || SAME70 || SAMS70
/** \internal Max number of interrupt sources. */
#define AES_INTERRUPT_SOURCE_NUM 3
#endif

/** AES interrupt callback function type. */
typedef void (*aes_callback_t)(void);

/** AES Configuration structure. */
struct aes_config {
	/** AES data mode (decryption or encryption). */
	enum aes_encrypt_mode encrypt_mode;
	/** AES key size. */
	enum aes_key_size key_size;
	/** Start mode. */
	enum aes_start_mode start_mode;
	/** AES block cipher operation mode.*/
	enum aes_opmode opmode;
	/** Cipher feedback data size. */
	enum aes_cfb_size cfb_size;
	/** Last output data mode enable/disable. */
	bool lod;
	/** Galois Counter Mode (GCM) automatic tag generation enable/disable
	(SAM4C devices only). */
	bool gtag_en;
	/** Processing delay parameter. */
	uint32_t processing_delay;
};

void aes_get_config_defaults(struct aes_config *const p_cfg);

void aes_init(Aes *const p_aes, struct aes_config *const p_cfg);

/**
 * \brief Perform an AES software reset.
 *
 * \param[out] p_aes Module hardware register base address pointer
 */
static inline void aes_reset(Aes *const p_aes)
{
	p_aes->AES_CR = AES_CR_SWRST;
}

/**
 * \brief Start a manual encryption/decryption process.
 *
 * \param[out] p_aes Module hardware register base address pointer
 */
static inline void aes_start(Aes *const p_aes)
{
	p_aes->AES_CR = AES_CR_START;
}

void aes_enable(void);

void aes_disable(void);

void aes_set_config(Aes *const p_aes, struct aes_config *const p_cfg);

/**
 * \brief Get the AES interrupt status.
 *
 * \param[in]  p_aes Module hardware register base address pointer
 *
 * \return The AES interrupt status register contents.
 */
static inline uint32_t aes_read_interrupt_status(Aes *const p_aes)
{
	return p_aes->AES_ISR;
}

void aes_set_callback(Aes *const p_aes,
		aes_interrupt_source_t source, aes_callback_t callback,
		uint8_t irq_level);

/**
 * \brief Enable an AES interrupt.
 *
 * \param[out]  p_aes Module hardware register base address pointer
 * \param[in] source \ref aes_interrupt_source "Interrupt source"
 */
static inline void aes_enable_interrupt(Aes *const p_aes,
		aes_interrupt_source_t source)
{
	p_aes->AES_IER = (uint32_t)source;
}

/**
 * \brief Disable an AES interrupt.
 *
 * \param[out]  p_aes Module hardware register base address pointer
 * \param[in]  source \ref aes_interrupt_source "Interrupt source"
 */
static inline void aes_disable_interrupt(
		Aes *const p_aes, aes_interrupt_source_t source)
{
	p_aes->AES_IDR = (uint32_t)source;
}

/**
 * \brief Get the AES interrupt mask status.
 *
 * \param[in]  p_aes Module hardware register base address pointer
 *
 * \return The AES interrupt mask contents.
 */
static inline uint32_t aes_read_interrupt_mask(Aes *const p_aes)
{
	return p_aes->AES_IMR;
}

void aes_write_key(Aes *const p_aes, const uint32_t *p_key);

void aes_write_initvector(Aes *const p_aes, const uint32_t *p_vector);

void aes_write_input_data(Aes *const p_aes,
		const uint32_t *p_input_data_buffer);

void aes_read_output_data(Aes *const p_aes,
		uint32_t *p_output_data_buffer);

#if SAM4C || SAM4CP || SAM4CM || SAMV70 || SAMV71 || SAME70 || SAMS70 || defined(__DOXYGEN__)
#if !(SAMV70 || SAMV71 || SAME70 || SAMS70)
Pdc *aes_get_pdc_base(Aes *p_aes);
#endif

/**
 * \brief Get the AES Additional Authenticated Data (AAD) length in bytes.
 *
 * \note This function is only available on SAM4C devices.
 *
 * \param[in]  p_aes Module hardware register base address pointer
 *
 * \return The Additional Authenticated Data (AAD) length in bytes.
 */
static inline uint32_t aes_read_authen_datalength(Aes *const p_aes)
{
	return p_aes->AES_AADLENR;
}

/**
 * \brief Set the AES Additional Authenticated Data (AAD) length in bytes.
 *
 * \note This function is only available on SAM4C devices.
 *
 * \param[out]  p_aes Module hardware register base address pointer
 * \param[in]  length Length in bytes of the AAD data to be processed
 */
static inline void aes_write_authen_datalength(Aes *const p_aes,
		uint32_t length)
{
	p_aes->AES_AADLENR = length;
}

/**
 * \brief Get the AES plaintext/ciphertext length in bytes.
 *
 * \note This function is only available on SAM4C devices.
 *
 * \param[in]  p_aes Module hardware register base address pointer
 *
 * \return The plaintext/ciphertext length in bytes.
 */
static inline uint32_t aes_read_pctext_length(Aes *const p_aes)
{
	return p_aes->AES_CLENR;
}

/**
 * \brief Set the AES plaintext/ciphertext length in bytes.
 *
 * \note This function is only available on SAM4C devices.
 *
 * \param[out] p_aes Module hardware register base address pointer
 * \param[in] length Length in bytes of the plaintext/ciphertext data
 */
static inline void aes_write_pctext_length(Aes *const p_aes, uint32_t length)
{
	p_aes->AES_CLENR = length;
}

/**
 * \brief  Get the AES GCM Encryption Counter.
 *
 * \note This function is only available on SAM4C devices.
 *
 * \param[in]  p_aes Module hardware register base address pointer
 *
 * \return The AES GCM encryption counter.
 */
static inline uint32_t aes_read_gcm_counter(Aes *const p_aes)
{
	return p_aes->AES_CTRR;
}

/**
 * \brief  Get the AES GCM Intermediate Hash Word.
 *
 * \note This function is only available on SAM4C devices.
 *
 * \param[in]  p_aes Module hardware register base address pointer
 * \param[in]  id    Index into the GHASH array (range 0 to 3)
 *
 * \return The content of the AES_GHASHRx[x = 0...3] register.
 */
static inline uint32_t aes_read_ghash(Aes *const p_aes, uint32_t id)
{
	return p_aes->AES_GHASHR[id];
}

/**
 * \brief  Set the AES GCM Intermediate Hash Word.
 *
 * \note This function is only available on SAM4C devices.
 *
 * \param[out] p_aes Module hardware register base address pointer
 * \param[in] id     Index into the GHASHx array (range 0 to 3)
 * \param[in] ghash  Intermediate GCM Hash Word x
 */
static inline void aes_write_ghash(Aes *const p_aes, uint32_t id,
		uint32_t ghash)
{
	p_aes->AES_GHASHR[id] = ghash;
}

/**
 * \brief  Get AES GCM Authentication Tag Word.
 *
 * \note This function is only available on SAM4C devices.
 *
 * \param[in]  p_aes Module hardware register base address pointer
 * \param[in]  id    Index into the TAGR array (range 0 to 3)
 *
 * \return The contents of the AES_TAGRx[x = 0...3] register specified.
 */
static inline uint32_t aes_read_tag(Aes *const p_aes, uint32_t id)
{
	return p_aes->AES_TAGR[id];
}

/**
 * \brief  Get AES GCM Hash subkey word.
 *
 * \note This function is only available on SAM4C devices.
 *
 * \param[in]  p_aes Module hardware register base address pointer
 * \param[in]  id    Index into the GCMHR array (range 0 to 3)
 *
 * \return The contents of the AES_GCMHRx[x = 0...3] register specified.
 */
static inline uint32_t aes_read_gcmh(Aes *const p_aes, uint32_t id)
{
	return p_aes->AES_GCMHR[id];
}

/**
 * \brief  Set the AES GCM Hash subkey word.
 *
 * \note This function is only available on SAM4C devices.
 *
 * \param[out]  p_aes Module hardware register base address pointer
 * \param[in]  id    Index into the GCMHR array (range 0 to 3)
 * \param[in]  hword GCM H Word
 */
static inline void aes_write_gcmh(Aes *const p_aes, uint32_t id, uint32_t hword)
{
	p_aes->AES_GCMHR[id] = hword;
}

#endif /* #if SAM4C || SAM4CP || SAM4CM || SAMV70 || SAMV71 || SAME70 || SAMS70 || defined(__DOXYGEN__) */

#ifdef __cplusplus
}
#endif

 /** @} */

/**
 * \page asfdoc_sam_drivers_aes_extra Extra Information for Advanced Encryption Standard
 *
 * \section asfdoc_sam_drivers_aes_extra_acronyms Acronyms
 * Below is a table listing the acronyms used in this module, along with their
 * intended meanings.
 *
 * <table>
 *  <tr>
 *      <th>Acronym</th>
 *      <th>Definition</th>
 *  </tr>
 *  <tr>
 *      <td>AAD</td>
 *      <td>Additional Authenticated Data</td>
 * </tr>
 *  <tr>
 *      <td>CBC</td>
 *      <td>Cipher Block Chaining</td>
 * </tr>
 *  <tr>
 *      <td>CFB</td>
 *      <td>Cipher Feedback</td>
 * </tr>
 *  <tr>
 *      <td>CTR</td>
 *      <td> Counter</td>
 * </tr>
 *  <tr>
 *      <td>DMA</td>
 *      <td>Direct Memory Access</td>
 * </tr>
 *  <tr>
 *      <td>DMAC</td>
 *      <td>DMA Controller</td>
 * </tr>
 *  <tr>
 *      <td>ECB</td>
 *      <td>Electronic Codebook</td>
 * </tr>
 *  <tr>
 *      <td>GCM</td>
 *      <td>Galois Counter Mode</td>
 * </tr>
 *  <tr>
 *      <td>NVIC</td>
 *      <td>Nested Vectored Interrupt Controller</td>
 * </tr>
 *  <tr>
 *      <td>OFB</td>
 *      <td>Output Feedback</td>
 * </tr>
 *  <tr>
 *      <td>PDC</td>
 *      <td>Peripheral DMA Controller</td>
 * </tr>
 *  <tr>
 *      <td>PMC</td>
 *      <td>Power Management Controller</td>
 * </tr>
 *  <tr>
 *      <td>QSG</td>
 *      <td>Quick Start Guide</td>
 * </tr>
 * </table>
 *
 *
 * \section asfdoc_sam_drivers_aes_extra_dependencies Dependencies
 * This driver has the following dependencies:
 *
 *  - None
 *
 *
 * \section asfdoc_sam_drivers_aes_extra_errata Errata
 * There are no errata related to this driver.
 *
 *
 * \section asfdoc_sam_drivers_aes_extra_history Module History
 * An overview of the module history is presented in the table below, with
 * details on the enhancements and fixes made to the module since its first
 * release. The current version of this corresponds to the newest version in
 * the table.
 *
 * <table>
 *	<tr>
 *		<th>Changelog</th>
 *	</tr>
 *	<tr>
 *		<td>Initial document release</td>
 *	</tr>
 * </table>
 */
 
/**
 * \page asfdoc_sam_drivers_aes_exqsg Examples for Advanced Encryption Standard
 *
 * This is a list of the available Quick Start Guides (QSGs) and example
 * applications for \ref asfdoc_sam_drivers_aes_group. QSGs are simple examples with
 * step-by-step instructions to configure and use this driver in a selection of
 * use cases. Note that QSGs can be compiled as a standalone application or be
 * added to the user application.
 *
 *  - \subpage asfdoc_sam_drivers_aes_qsg
 *  - \subpage asfdoc_sam_drivers_aes_example1
 *
 * \page asfdoc_sam_drivers_aes_document_revision_history Document Revision History
 *
 * <table>
 *	<tr>
 *		<th>Doc. Rev.</td>
 *		<th>Date</td>
 *		<th>Comments</td>
 *	</tr>
 *	<tr>
 *		<td>42295B</td>
 *		<td>07/2014</td>5
 *		<td>Updated title of application note and added list of supported devices</td>
 *	</tr>

 *	<tr>
 *		<td>42295A</td>
 *		<td>05/2014</td>
 *		<td>Initial document release</td>
 *	</tr>
 * </table>
 *
 */

/**
 * \page asfdoc_sam_drivers_aes_qsg Quick Start Guide for the AES Driver
 *
 * This is the quick start guide for the \ref asfdoc_sam_drivers_aes_group, with
 * step-by-step instructions on how to configure and use the driver for
 * a specific use case. The code examples can be copied into any function that
 * needs to control the AES module, such as the main application loop, for example.
 *
 * \section aes_qs_use_cases Use Cases
 * - \ref aes_basic
 *
 * \section aes_basic AES Basic Usage
 *
 * This use case will demonstrate how to initialize the AES module to
 * perform encryption or decryption of data.
 *
 *
 * \section aes_basic_setup Setup Steps
 *
 * \subsection aes_basic_prereq Prerequisites
 *
 * This module requires the following service:
 * - \ref clk_group "System clock (sysclk)"
 *
 * \subsection aes_basic_setup_code Setup Code
 *
 * Add this to the main loop or a setup function:
 * \verbatim
   struct aes_config   g_aes_cfg;
   aes_get_config_defaults(&g_aes_cfg);
   aes_init(AES, &g_aes_cfg);
   aes_enable(); \endverbatim
 *
 * \subsection aes_basic_setup_workflow Workflow
 *
 * -# Enable the AES module:
 * \verbatim aes_enable(); \endverbatim
 *
 * -# Set the AES interrupt and callback:
 * \verbatim
   aes_set_callback(AES, AES_INTERRUPT_DATA_READY,
 		aes_callback, 1); \endverbatim
 *
 * -# Initialize the AES to ECB cipher mode:
 * \verbatim
   g_aes_cfg.encrypt_mode = AES_ENCRYPTION;
   g_aes_cfg.key_size = AES_KEY_SIZE_128;
   g_aes_cfg.start_mode = AES_AUTO_MODE;
   g_aes_cfg.opmode = AES_ECB_MODE;
   g_aes_cfg.cfb_size = AES_CFB_SIZE_128;
   g_aes_cfg.lod = false;
   aes_set_config(AES, &g_aes_cfg);  \endverbatim
 *
 * \section aes_basic_usage Usage Steps
 *
 * \subsection aes_basic_usage_code Usage Code
 *
 * Plain text can be encrypted by:
 * \verbatim
   aes_write_key(AES, key128);
   aes_write_input_data(AES, ref_plain_text); \endverbatim
 *
 * The cipher text can be retrieved after it's been encrypted by:
 * \verbatim aes_read_output_data(AES, output_data); \endverbatim
 */

#endif  /* AES_H_INCLUDED */
