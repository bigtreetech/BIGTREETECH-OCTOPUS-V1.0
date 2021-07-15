/**
 * \file
 *
 * \brief SAM Analog Comparator Controller (ACC) driver.
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

#ifndef ACC_H_INCLUDED
#define ACC_H_INCLUDED

/**
 * \defgroup asfdoc_sam_drivers_acc_group SAM3S/4E/4S/V71/V70/S70/E70 Analog Comparator Controller (ACC) Driver
 *
 * This driver for Atmel&reg; | SMART ARM&reg;-based microcontrollers provides an interface for 
 * the configuration and management of the device's Analog Comparator Controller functionality.
 *
 * The Analog Comparator compares two voltages, and the result of this comparison
 * gives a compare output. The user application can select whether to use a high-speed
 * or a low-power option as well as selecting the hysteresis level, edge detection,
 * and polarity.
 *
 * Devices from the following series can use this module:
 * - Atmel | SMART SAM3S
 * - Atmel | SMART SAM4E
 * - Atmel | SMART SAM4S
 * - Atmel | SMART SAMV71
 * - Atmel | SMART SAMV70
 * - Atmel | SMART SAME70
 * - Atmel | SMART SAMS70
 *
 * The outline of this documentation is as follows:
 *  - \ref asfdoc_sam_drivers_acc_prerequisites
 *  - \ref asfdoc_sam_drivers_acc_module_overview
 *  - \ref asfdoc_sam_drivers_acc_special_considerations
 *  - \ref asfdoc_sam_drivers_acc_extra_info
 *  - \ref asfdoc_sam_drivers_acc_examples
 *  - \ref asfdoc_sam_drivers_acc_api_overview
 *
 *
 * \section asfdoc_sam_drivers_acc_prerequisites Prerequisites
 *
 * There are no prerequisites for this module.
 *
 *
 * \section asfdoc_sam_drivers_acc_module_overview Module Overview
 *
 * The Analog Comparator Controller configures the Analog Comparator, and
 * generates an interrupt according to the user application's settings. The
 * analog comparator embeds 8 to 1 multiplexers on both its plus and minus
 * inputs.
 *
 * The Analog Comparator compares two voltages, and the result of this comparison
 * gives a compare output and an interrupt can be generated accordingly. The user
 * application can select a high-speed or low-power option, the hysteresis level,
 * edge detection, and polarity.
 *
 * The ACC can also generate a comparison event that can be used by the Pulse Width
 * Modulation (PWM) module.
 *
 *
 * \section asfdoc_sam_drivers_acc_special_considerations Special Considerations
 *
 * \subsection asfdoc_sam_drivers_acc_special_considerations_config Configuration Changes
 *
 * As soon as the analog comparator settings are modified, the output of the
 * analog comparator is masked for the time that its output may be invalid.
 * Depending on the user application the following function calls may require
 * the comparator output to be valid before continuing:
 * - \ref acc_enable()
 * - \ref acc_set_input()
 * - \ref acc_set_output()
 *
 * The following code may be used to check if the comparator output is valid
 * before continuing:
 * \code
 * while ((acc_get_interrupt_status(ACC) & ACC_ISR_MASK) == ACC_ISR_MASK) {
 * } \endcode
 *
 * \subsection asfdoc_sam_drivers_acc_special_considerations_io I/O Lines
 *
 * The analog input pins (AD0-AD7 and DAC0-1) are multiplexed with general-purpose 
 * input/output (GPIO) lines. The assignment of these pins to ACC module inputs 
 * is automatically done when the corresponding input is assigned to the 
 * comparator's plus/minus inputs by the user application performing a write to 
 * the module's Mode Register.
 *
 * \subsection asfdoc_sam_drivers_acc_special_considerations_power Power Management
 * The ACC module is clocked through the Power Management Controller (PMC),
 * thus the user application must first configure the PMC, in order to enable the
 * Analog Comparator Controller clock.
 *
 * \note The voltage regulator must be activated before the Analog Comparator module
 * is used.
 *
 * \subsection asfdoc_sam_drivers_acc_special_considerations_irq Interrupt
 *
 * The ACC module has an interrupt line connected to the Nested Vectored Interrupt
 * Controller (NVIC). Handling the ACC interrupt requires that the NVIC is configured
 * before configuring the ACC.
 *
 * \subsection asfdoc_sam_drivers_acc_special_considerations_fault Fault Output
 *
 * The ACC module has a FAULT output that is connected to the FAULT input of the
 * PWM module. Refer to "fault mode" and the implementation of the PWM in
 * the device-specific datasheet.
 *
 *
 * \section asfdoc_sam_drivers_acc_extra_info Extra Information
 *
 * For extra information, see \ref asfdoc_sam_drivers_acc_extra. This includes:
 *  - \ref asfdoc_sam_drivers_acc_extra_acronyms
 *  - \ref asfdoc_sam_drivers_acc_extra_dependencies
 *  - \ref asfdoc_sam_drivers_acc_extra_errata
 *  - \ref asfdoc_sam_drivers_acc_extra_history
 *
 * \section asfdoc_sam_drivers_acc_examples Examples
 *
 * For a list of examples related to this driver, see
 * \ref asfdoc_sam_drivers_acc_exqsg.
 *
 *
 * \section asfdoc_sam_drivers_acc_api_overview API Overview
 * @{
 */
 
#include <compiler.h>

/// @cond
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/** \name Hysteresis Levels
 * Refer to the "Analog Comparator Characteristics" table in the
 * "Electrical Characteristics" chapter of the device-specific datasheet.
 * @{
 */
#define ACC_ACR_HYST_0mv_max	0x00
#define ACC_ACR_HYST_50mv_max	0x01
#define ACC_ACR_HYST_90mv_max	0x11
/** @} */

void acc_init(Acc *p_acc, uint32_t ul_select_plus, uint32_t ul_select_minus,
		uint32_t ul_edge_type, uint32_t ul_invert);
void acc_enable(Acc *p_acc);
void acc_disable(Acc *p_acc);
void acc_reset(Acc *p_acc);
void acc_set_input(Acc *p_acc, uint32_t ul_select_minus,
		uint32_t ul_select_plus);
void acc_set_output(Acc *p_acc, uint32_t ul_invert,
		uint32_t ul_fault_enable, uint32_t ul_fault_source);
uint32_t acc_get_comparison_result(Acc *p_acc);
void acc_enable_interrupt(Acc *p_acc);
void acc_disable_interrupt(Acc *p_acc);
uint32_t acc_get_interrupt_status(Acc *p_acc);
void acc_set_writeprotect(Acc *p_acc, uint32_t ul_enable);
uint32_t acc_get_writeprotect_status(Acc *p_acc);

/// @cond
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

/** @} */

/**
 * \page asfdoc_sam_drivers_acc_extra Extra Information for Analog Comparator Controller
 *
 * \section asfdoc_sam_drivers_acc_extra_acronyms Acronyms
 * Below is a table listing the acronyms used in this module, along with their
 * intended meanings.
 *
 * <table>
 *  <tr>
 *      <th>Acronym</th>
 *      <th>Definition</th>
 *  </tr>
 *  <tr>
 *      <td>AD</td>
 *      <td>Analog to Digital</td>
 * </tr>
 *  <tr>
 *      <td>DAC</td>
 *      <td>Digital to Analog Converter</td>
 * </tr>
 *  <tr>
 *      <td>GPIO</td>
 *      <td>General Purpose Input Output</td>
 * </tr>
 *  <tr>
 *      <td>NVIC</td>
 *      <td>Nested Vectored Interrupt Controller</td>
 * </tr>
 *  <tr>
 *      <td>PMC</td>
 *      <td>Power Management Controller</td>
 * </tr>
 *  <tr>
 *      <td>PWM</td>
 *      <td>Pulse Width Modulator</td>
 * </tr>
 *  <tr>
 *      <td>QSG</td>
 *      <td>Quick Start Guide</td>
 * </tr>
 * </table>
 *
 *
 * \section asfdoc_sam_drivers_acc_extra_dependencies Dependencies
 * This driver has the following dependencies:
 *
 *  - None
 *
 *
 * \section asfdoc_sam_drivers_acc_extra_errata Errata
 * There are no errata related to this driver.
 *
 *
 * \section asfdoc_sam_drivers_acc_extra_history Module History
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
 * \page asfdoc_sam_drivers_acc_exqsg Examples for Analog Comparator Controller
 *
 * This is a list of the available Quick Start guides (QSGs) and example
 * applications for \ref asfdoc_sam_drivers_acc_group. QSGs are simple examples, with
 * step-by-step instructions to configure and use this driver in a selection of
 * use cases. Note that a QSG can be compiled as a standalone application or be
 * added to the user application.
 *
 *  - \subpage asfdoc_sam_drivers_acc_qsg
 *  - \subpage asfdoc_sam_drivers_acc_example_irq
 *
 * \page asfdoc_sam_drivers_acc_document_revision_history Document Revision History
 *
 * <table>
 *	<tr>
 *		<th>Doc. Rev.</td>
 *		<th>Date</td>
 *		<th>Comments</td>
 *	</tr>
 *  <tr>
 *    <td>42292B</td>
 *    <td>07/2015</td>
 *    <td>Updated title of application note and added list of supported devices</td>
 *  </tr>
 *	<tr>
 *		<td>42292A</td>
 *		<td>05/2014</td>
 *		<td>Initial document release</td>
 *	</tr>
 * </table>
 *
 */

/**
 * \page asfdoc_sam_drivers_acc_qsg Quick Start Guide for the ACC driver
 *
 * This is the quick start guide for the \ref asfdoc_sam_drivers_acc_group, with
 * step-by-step instructions on how to configure and use the driver for
 * a specific use case. The code examples can be copied into e.g. the main
 * application loop or any other function that will need to control the
 * ACC module.
 *
 * \section asfdoc_sam_drivers_acc_qsg_use_cases Use Cases
 * - \ref asfdoc_sam_drivers_acc_qsg_basic
 *
 * \section asfdoc_sam_drivers_acc_qsg_basic ACC Basic Usage
 *
 * This use case will demonstrate how to initialize the ACC module in
 * interrupt mode.
 *
 *
 * \section asfdoc_sam_drivers_acc_qsg_basic_setup Setup Steps
 *
 * \subsection asfdoc_sam_acc_qsg_basic_prereq Prerequisites
 *
 * This module requires the following service:
 * - \ref clk_group "System Clock Management (sysclock)"
 *
 * \subsection asfdoc_sam_drivers_acc_qsg_basic_setup_code Setup Code
 *
 * Add this to your main application C-file:
 * \verbatim
   void ACC_Handler(void)
   {
   } \endverbatim
 * Add this to the main loop or a setup function:
 * \snippet acc_example.c acc_enable_clock
 *
 * \subsection asfdoc_sam_drivers_acc_qsg_basic_setup_workflow Workflow
 *
 * -# Initialize the ACC module so that:
 *   - ADC channel 5 is connected to its positive input
 *   - DAC channel 0 is connected to its negative input
 *   - Generate an interrupt on either edge of the output
 *   - Disable the ACC module output inversion
 * \snippet acc_example.c acc_init
 * -# Enable the ACC module interrupt:
 * \snippet acc_example.c acc_irq_enable
 *
 * \section asfdoc_sam_drivers_acc_qsg_basic_usage Usage Steps
 *
 * \subsection asfdoc_sam_drivers_acc_qsg_basic_usage_code Usage Code
 *
 * In the ACC_Handler() function, check if the output result is available by:
 * \verbatim
   if ((ul_status & ACC_ISR_CE) == ACC_ISR_CE) {
   } \endverbatim
 * In the ACC_Handler() function, check if ADC channel 5 is greater than
 * DAC channel 0 by:
 * \verbatim
   if (acc_get_comparison_result(ACC)) {
       do_something_with_a_greater_result();
   } \endverbatim
 * In the ACC_Handler() function, check if ADC channel 5 is less than
 * DAC channel 0 by:
 * \verbatim
   if (!acc_get_comparison_result(ACC)) {
       do_something_with_a_lesser_result();
   } \endverbatim
 */

#endif /* ACC_H_INCLUDED */
