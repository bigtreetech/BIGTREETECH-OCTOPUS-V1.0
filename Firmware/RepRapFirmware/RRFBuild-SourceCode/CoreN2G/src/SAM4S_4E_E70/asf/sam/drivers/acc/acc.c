/**
 * \file
 *
 * \brief SAM4 Analog Comparator Controller (ACC) driver.
 *
 * Copyright (c) 2011-2018 Microchip Technology Inc. and its subsidiaries.
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

#include "acc.h"

/// @cond
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

#ifndef ACC_WPMR_WPKEY_PASSWD
#  define ACC_WPMR_WPKEY_PASSWD ACC_WPMR_WPKEY((uint32_t) 0x414343)
#endif

/**
 * \brief Initialize the ACC module.
 *
 * \note This function performs a \ref acc_reset() "software reset" on the
 * ACC module prior to its initialization.
 *
 * \param[in,out] p_acc       Module hardware register base address pointer
 * \param[in] ul_select_plus  Selection for the plus comparator input (inp)
 * \param[in] ul_select_minus Selection for the minus comparator input (inn)
 * \param[in] ul_edge_type    Comparison flag triggering mode
 * \param[in] ul_invert       Invert the comparator output mode
 *
 * Where the input parameter <i>ul_select_plus</i> is one of the following:
 * <table>
 * <tr>
 *    <th>Parameter Value</th>
 *    <th>Description</th>
 * </tr>
 *    <tr><td>ACC_MR_SELPLUS_AD0</td><td>Select AD0 as the plus input</td></tr>
 *    <tr><td>ACC_MR_SELPLUS_AD1</td><td>Select AD1 as the plus input</td></tr>
 *    <tr><td>ACC_MR_SELPLUS_AD2</td><td>Select AD2 as the plus input</td></tr>
 *    <tr><td>ACC_MR_SELPLUS_AD3</td><td>Select AD3 as the plus input</td></tr>
 *    <tr><td>ACC_MR_SELPLUS_AD4</td><td>Select AD4 as the plus input</td></tr>
 *    <tr><td>ACC_MR_SELPLUS_AD5</td><td>Select AD5 as the plus input</td></tr>
 *    <tr><td>ACC_MR_SELPLUS_AD6</td><td>Select AD6 as the plus input</td></tr>
 *    <tr><td>ACC_MR_SELPLUS_AD7</td><td>Select AD7 as the plus input</td></tr>
 *</table>
 *
 * Where the input parameter <i>ul_select_minus</i> is one of the following:
 * <table>
 * <tr>
 *    <th>Parameter Value</th>
 *    <th>Description</th>
 * </tr>
 *    <tr><td>ACC_MR_SELMINUS_TS</td><td>Select TS as the minus input</td></tr>
 *    <tr><td>ACC_MR_SELMINUS_ADVREF</td><td>Select ADVREF as the minus input</td></tr>
 *    <tr><td>ACC_MR_SELMINUS_DAC0</td><td>Select DAC0 as the minus input</td></tr>
 *    <tr><td>ACC_MR_SELMINUS_DAC1</td><td>Select DAC1 as the minus input</td></tr>
 *    <tr><td>ACC_MR_SELMINUS_AD0</td><td>Select AD0 as the minus input</td></tr>
 *    <tr><td>ACC_MR_SELMINUS_AD1</td><td>Select AD1 as the minus input</td></tr>
 *    <tr><td>ACC_MR_SELMINUS_AD2</td><td>Select AD2 as the minus input</td></tr>
 *    <tr><td>ACC_MR_SELMINUS_AD3</td><td>Select AD3 as the minus input</td></tr>
 *</table>
 *
 * Where the input parameter <i>ul_edge_type</i> is one of the following:
 * <table>
 * <tr>
 *    <th>Parameter Value</th>
 *    <th>Description</th>
 * </tr>
 *    <tr><td>ACC_MR_EDGETYP_RISING</td><td>Rising edge of comparator output</td></tr>
 *    <tr><td>ACC_MR_EDGETYP_FALLING</td><td>Falling edge of comparator output</td></tr>
 *    <tr><td>ACC_MR_EDGETYP_ANY</td><td>Any edge of comparator output</td></tr>
 * </table>
 *
 * Where the input parameter <i>ul_invert</i> is one of the following:
 * <table>
 * <tr>
 *    <th>Parameter Value</th>
 *    <th>Description</th>
 * </tr>
 *    <tr><td>ACC_MR_INV_DIS</td><td>Comparator output is directly processed</td></tr>
 *    <tr><td>ACC_MR_INV_EN</td><td>Comparator output is inverted prior to being processed</td></tr>
 * </table>
 */
void acc_init(
		Acc *p_acc,
		uint32_t ul_select_plus,
		uint32_t ul_select_minus,
		uint32_t ul_edge_type,
		uint32_t ul_invert)
{
	/* Validate the parameters. */
	Assert(p_acc);
	
	/* Reset the controller. */
	p_acc->ACC_CR |= ACC_CR_SWRST;

	/* Write to the MR register. */
	p_acc->ACC_MR = (((ul_select_plus) & ACC_MR_SELPLUS_Msk) | 
			((ul_select_minus) & ACC_MR_SELMINUS_Msk) | 
			((ul_edge_type) & ACC_MR_EDGETYP_Msk) | 
			((ul_invert) & ACC_MR_INV)) | ACC_MR_ACEN_EN;

	/* Set hysteresis and current option. */
	p_acc->ACC_ACR = (ACC_ACR_ISEL_HISP |
			ACC_ACR_HYST(ACC_ACR_HYST_50mv_max));

	/* Automatic Output Masking Period. */
	while (p_acc->ACC_ISR & (uint32_t) ACC_ISR_MASK);
}

/**
 * \brief Enable the ACC module.
 *
 * \param[in,out] p_acc Module hardware register base address pointer
 */
void acc_enable(
		Acc *p_acc)
{
	/* Validate the parameters. */
	Assert(p_acc);
	
	p_acc->ACC_MR |= ACC_MR_ACEN_EN;
}

/**
 * \brief Disable the ACC module.
 *
 * \param[in,out] p_acc Module hardware register base address pointer
 */
void acc_disable(
		Acc *p_acc)
{
	/* Validate the parameters. */
	Assert(p_acc);
	
	p_acc->ACC_MR &= ~ACC_MR_ACEN_EN;
}

/**
 * \brief Software reset the ACC module.
 *
 * \param[out] p_acc Module hardware register base address pointer
 */
void acc_reset(
		Acc *p_acc)
{
	/* Validate the parameters. */
	Assert(p_acc);
	
	p_acc->ACC_CR = ACC_CR_SWRST;
}

/**
 * \brief Set the ACC comparator plus/minus input sources.
 *
 * \param[in,out] p_acc       Module hardware register base address pointer
 * \param[in] ul_select_minus Selection for the minus comparator input (inn)
 * \param[in] ul_select_plus  Selection for the plus comparator input (inp)
 *
 * Where the input parameter <i>ul_select_minus</i> is one of the following:
 * <table>
 * <tr>
 *    <th>Parameter Value</th>
 *    <th>Description</th>
 * </tr>
 *    <tr><td>ACC_MR_SELMINUS_TS</td><td>Select TS as the minus input</td></tr>
 *    <tr><td>ACC_MR_SELMINUS_ADVREF</td><td>Select ADVREF as the minus input</td></tr>
 *    <tr><td>ACC_MR_SELMINUS_DAC0</td><td>Select DAC0 as the minus input</td></tr>
 *    <tr><td>ACC_MR_SELMINUS_DAC1</td><td>Select DAC1 as the minus input</td></tr>
 *    <tr><td>ACC_MR_SELMINUS_AD0</td><td>Select AD0 as the minus input</td></tr>
 *    <tr><td>ACC_MR_SELMINUS_AD1</td><td>Select AD1 as the minus input</td></tr>
 *    <tr><td>ACC_MR_SELMINUS_AD2</td><td>Select AD2 as the minus input</td></tr>
 *    <tr><td>ACC_MR_SELMINUS_AD3</td><td>Select AD3 as the minus input</td></tr>
 *</table>
 *
 * Where the input parameter <i>ul_select_plus</i> is one of the following:
 * <table>
 * <tr>
 *    <th>Parameter Value</th>
 *    <th>Description</th>
 * </tr>
 *    <tr><td>ACC_MR_SELPLUS_AD0</td><td>Select AD0 as the plus input</td></tr>
 *    <tr><td>ACC_MR_SELPLUS_AD1</td><td>Select AD1 as the plus input</td></tr>
 *    <tr><td>ACC_MR_SELPLUS_AD2</td><td>Select AD2 as the plus input</td></tr>
 *    <tr><td>ACC_MR_SELPLUS_AD3</td><td>Select AD3 as the plus input</td></tr>
 *    <tr><td>ACC_MR_SELPLUS_AD4</td><td>Select AD4 as the plus input</td></tr>
 *    <tr><td>ACC_MR_SELPLUS_AD5</td><td>Select AD5 as the plus input</td></tr>
 *    <tr><td>ACC_MR_SELPLUS_AD6</td><td>Select AD6 as the plus input</td></tr>
 *    <tr><td>ACC_MR_SELPLUS_AD7</td><td>Select AD7 as the plus input</td></tr>
 *</table>
 */
void acc_set_input(
		Acc *p_acc,
		uint32_t ul_select_minus,
		uint32_t ul_select_plus)
{
	/* Validate the parameters. */
	Assert(p_acc);
	
	p_acc->ACC_MR &= ~(ACC_MR_SELMINUS_Msk | ACC_MR_SELPLUS_Msk);
	p_acc->ACC_MR |= ul_select_plus | ul_select_minus;
}

/**
 * \brief Set the ACC output.
 *
 * \param[in,out] p_acc       Module hardware register base address pointer
 * \param[in] ul_invert       Invert comparator output
 * \param[in] ul_fault_enable Fault enable
 * \param[in] ul_fault_source Selection of fault source
 *
 * Where the input parameter <i>ul_invert</i> is one of the following:
 * <table>
 * <tr>
 *    <th>Parameter Value</th>
 *    <th>Description</th>
 * </tr>
 *    <tr><td>ACC_MR_INV_DIS</td><td>Comparator output is directly processed</td></tr>
 *    <tr><td>ACC_MR_INV_EN</td><td>Comparator output is inverted prior to being processed</td></tr>
 * </table>
 *
 * Where the input parameter <i>ul_fault_enable</i> is one of the following:
 * <table>
 * <tr>
 *    <th>Parameter Value</th>
 *    <th>Description</th>
 * </tr>
 *    <tr><td>ACC_MR_FE_DIS</td><td>The FAULT output is tied to 0</td></tr>
 *    <tr><td>ACC_MR_FE_EN</td><td>The FAULT output is driven by <i>ul_fault_source</i></td></tr>
 * </table>
 *
 * Where the input parameter <i>ul_fault_source</i> is one of the following:
 * <table>
 * <tr>
 *    <th>Parameter Value</th>
 *    <th>Description</th>
 * </tr>
 *    <tr><td>ACC_MR_SELFS_CF</td><td>The CF flag is used to drive the FAULT output</td></tr>
 *    <tr><td>ACC_MR_SELFS_OUTPUT</td><td>The output of the Analog Comparator flag is used to drive the FAULT output</td></tr>
 * </table>
 */
void acc_set_output(
		Acc *p_acc,
		uint32_t ul_invert,
		uint32_t ul_fault_enable,
		uint32_t ul_fault_source)
{
	/* Validate the parameters. */
	Assert(p_acc);
	
	p_acc->ACC_MR &= ~(ACC_MR_INV_EN | ACC_MR_FE_EN | ACC_MR_SELFS_OUTPUT);

	p_acc->ACC_MR |= ul_invert | ul_fault_source | ul_fault_enable;
}

/**
 * \brief Get the ACC comparison result.
 *
 * \param[in] p_acc Module hardware register base address pointer
 *
 * \return The ACC comparison result.
 * \retval 0 Comparator minus input is greater than its plus input (inn>inp)
 * \retval 1 Comparator plus input is greater than its minus input (inp>inn)
 */
uint32_t acc_get_comparison_result(
		Acc *p_acc)
{
	/* Validate the parameters. */
	Assert(p_acc);
	
	uint32_t ul_temp = p_acc->ACC_MR;
	uint32_t ul_status = p_acc->ACC_ISR;

	if ((ul_temp & ACC_MR_INV_EN) == ACC_MR_INV_EN) {
		if (ul_status & ACC_ISR_SCO) {
			return 0;	/* inn>inp */
		} else {
			return 1;	/* inp>inn */
		}
	} else {
		if (ul_status & ACC_ISR_SCO) {
			return 1;	/* inp>inn */
		} else {
			return 0;	/* inn>inp */
		}
	}
}

/**
 * \brief Enable the ACC comparison edge interrupt.
 *
 * \param[out] p_acc Module hardware register base address pointer
 */
void acc_enable_interrupt(
		Acc *p_acc)
{
	/* Validate the parameters. */
	Assert(p_acc);
	
	p_acc->ACC_IER = ACC_IER_CE;
}

/**
 * \brief Disable the ACC comparison edge interrupt.
 *
 * \param[out] p_acc Module hardware register base address pointer
 */
void acc_disable_interrupt(
		Acc *p_acc)
{
	/* Validate the parameters. */
	Assert(p_acc);
	
	p_acc->ACC_IDR = ACC_IDR_CE;
}

/**
 * \brief Get the ACC comparison edge interrupt status.
 *
 * \param[in] p_acc Module hardware register base address pointer
 *
 * \return The ACC comparison edge interrupt status.
 */
uint32_t acc_get_interrupt_status(
		Acc *p_acc)
{
	/* Validate the parameters. */
	Assert(p_acc);
	
	return p_acc->ACC_ISR;
}

/**
 * \brief Set the ACC register write-protection.
 *
 * \param[out] p_acc    Module hardware register base address pointer
 * \param[in] ul_enable 1 to enable, 0 to disable
 */
void acc_set_writeprotect(
		Acc *p_acc,
		uint32_t ul_enable)
{
	/* Validate the parameters. */
	Assert(p_acc);
	
	if (ul_enable)
		p_acc->ACC_WPMR = ACC_WPMR_WPKEY_PASSWD | ACC_WPMR_WPEN;
	else
		p_acc->ACC_WPMR = ACC_WPMR_WPKEY_PASSWD;
}

#if (SAMV71 || SAMV70 || SAME70 || SAMS70)
/**
 * \brief Get the ACC register write-protection status.
 *
 * \param[in] p_acc Module hardware register base address pointer
 *
 * \return The ACC register write-protection status.
 * \retval 0                 No write-protection violation occurred
 * \retval ACC_WPSR_WPVS Write-protection violation (WPEN = 1) has occurred since the last read of ACC_WPSR
 */
uint32_t acc_get_writeprotect_status(
		Acc *p_acc)
{
	/* Validate the parameters. */
	Assert(p_acc);
	
	return p_acc->ACC_WPSR & ACC_WPSR_WPVS;
}
#else
/**
 * \brief Get the ACC register write-protection status.
 *
 * \param[in] p_acc Module hardware register base address pointer
 *
 * \return The ACC register write-protection status.
 * \retval 0                 No write-protection error
 * \retval ACC_WPSR_WPROTERR Write-protection error
 */
uint32_t acc_get_writeprotect_status(
		Acc *p_acc)
{
	/* Validate the parameters. */
	Assert(p_acc);
	
	return p_acc->ACC_WPSR & ACC_WPSR_WPROTERR;
}
#endif

/// @cond
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond
