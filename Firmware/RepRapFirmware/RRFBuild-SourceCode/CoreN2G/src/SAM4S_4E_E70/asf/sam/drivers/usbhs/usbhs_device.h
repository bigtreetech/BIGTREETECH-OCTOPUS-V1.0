/**
 * \file
 *
 * \brief USB Device Driver for USBHS. Compliant with common UDD driver.
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef USBHS_DEVICE_H_INCLUDED
#define USBHS_DEVICE_H_INCLUDED

#include "compiler.h"
#include "preprocessor.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

#ifndef USBHS_RAM_ADDR
#define USBHS_RAM_ADDR        0xA0100000u
#endif

//! \ingroup udd_group
//! \defgroup udd_udphs_group USB High-Speed Port for device mode (USBHS)
//! USBHS low-level driver for USB device mode
//!
//! @{

#ifndef USBHS_DEVEPTCFG_EPDIR_Pos
// Bit pos is not defined in SAM header file but we need it.
# define USBHS_DEVEPTCFG_EPDIR_Pos 8
#endif

//! @name USBHS Device IP properties
//! These macros give access to IP properties
//! @{
  //! Get maximal number of endpoints
#define udd_get_endpoint_max_nbr()             (9)
#define UDD_MAX_PEP_NB                         (udd_get_endpoint_max_nbr() + 1)
  //! Get maximal number of banks of endpoints
#define udd_get_endpoint_bank_max_nbr(ep)      ((ep == 0) ? 1 : (( ep <= 2) ? 3 : 2))
  //! Get maximal size of endpoint (3X, 1024/64)
#define udd_get_endpoint_size_max(ep)          (((ep) == 0) ? 64 : 1024)
  //! Get DMA support of endpoints
#define Is_udd_endpoint_dma_supported(ep)      ((((ep) >= 1) && ((ep) <= 7)) ? true : false)
  //! Get High Band Width support of endpoints
#define Is_udd_endpoint_high_bw_supported(ep)  (((ep) >= 2) ? true : false)
//! @}

//! @name USBHS Device speeds management
//! @{
  //! Enable/disable device low-speed mode
#define udd_low_speed_enable()               (Set_bits(USBHS->USBHS_DEVCTRL, USBHS_DEVCTRL_LS))
#define udd_low_speed_disable()              (Clr_bits(USBHS->USBHS_DEVCTRL, USBHS_DEVCTRL_LS))
  //! Test if device low-speed mode is forced
#define Is_udd_low_speed_enable()            (Tst_bits(USBHS->USBHS_DEVCTRL, USBHS_DEVCTRL_LS))

#ifdef USBHS_DEVCTRL_SPDCONF_HIGH_SPEED
  //! Enable high speed mode
# define udd_high_speed_enable()          (Wr_bitfield(USBHS->USBHS_DEVCTRL, USBHS_DEVCTRL_SPDCONF_Msk, 0))
  //! Disable high speed mode
# define udd_high_speed_disable()         (Wr_bitfield(USBHS->USBHS_DEVCTRL, USBHS_DEVCTRL_SPDCONF_Msk, 3))
  //! Test if controller is in full speed mode
# define Is_udd_full_speed_mode()         (Rd_bitfield(USBHS->USBHS_SR, USBHS_SR_SPEED_Msk) == USBHS_SR_SPEED_FULL_SPEED)
#else
# define udd_high_speed_enable()          do { } while (0)
# define udd_high_speed_disable()         do { } while (0)
# define Is_udd_full_speed_mode()         true
#endif
//! @}

//! @name USBHS Device HS test mode management
//! @{
#ifdef USBHS_DEVCTRL_SPDCONF_HIGH_SPEED
  //! Enable high speed test mode
# define udd_enable_hs_test_mode()        (Wr_bitfield(USBHS->USBHS_DEVCTRL, USBHS_DEVCTRL_SPDCONF_Msk, 2))
# define udd_enable_hs_test_mode_j()      (Set_bits(USBHS->USBHS_DEVCTRL, USBHS_DEVCTRL_TSTJ))
# define udd_enable_hs_test_mode_k()      (Set_bits(USBHS->USBHS_DEVCTRL, USBHS_DEVCTRL_TSTK))
# define udd_enable_hs_test_mode_packet() (Set_bits(USBHS->USBHS_DEVCTRL, USBHS_DEVCTRL_TSTPCKT))
#endif
//! @}

//! @name USBHS device attach control
//! These macros manage the USBHS Device attach.
//! @{
  //! Detaches from USB bus
#define udd_detach_device()               (Set_bits(USBHS->USBHS_DEVCTRL, USBHS_DEVCTRL_DETACH))
  //! Attaches to USB bus
#define udd_attach_device()               (Clr_bits(USBHS->USBHS_DEVCTRL, USBHS_DEVCTRL_DETACH))
  //! Test if the device is detached
#define Is_udd_detached()                 (Tst_bits(USBHS->USBHS_DEVCTRL, USBHS_DEVCTRL_DETACH))
//! @}


//! @name USBHS device bus events control
//! These macros manage the USBHS Device bus events.
//! @{

//! Initiates a remote wake-up event
//! @{
#define udd_initiate_remote_wake_up()     (Set_bits(USBHS->USBHS_DEVCTRL, USBHS_DEVCTRL_RMWKUP))
#define Is_udd_pending_remote_wake_up()   (Tst_bits(USBHS->USBHS_DEVCTRL, USBHS_DEVCTRL_RMWKUP))
//! @}

//! Manage upstream resume event (=remote wakeup)
//! The USB driver sends a resume signal called "Upstream Resume"
//! @{
#define udd_enable_remote_wake_up_interrupt()     (USBHS->USBHS_DEVIER = USBHS_DEVIER_UPRSMES)
#define udd_disable_remote_wake_up_interrupt()    (USBHS->USBHS_DEVIDR = USBHS_DEVIDR_UPRSMEC)
#define Is_udd_remote_wake_up_interrupt_enabled() (Tst_bits(USBHS->USBHS_DEVIMR, USBHS_DEVIMR_UPRSME))
#define udd_ack_remote_wake_up_start()            (USBHS->USBHS_DEVICR = USBHS_DEVICR_UPRSMC)
#define udd_raise_remote_wake_up_start()          (USBHS->USBHS_DEVIFR = USBHS_DEVIFR_UPRSMS)
#define Is_udd_remote_wake_up_start()             (Tst_bits(USBHS->USBHS_DEVISR, USBHS_DEVISR_UPRSM))
//! @}

//! Manage downstream resume event (=remote wakeup from host)
//! The USB controller detects a valid "End of Resume" signal initiated by the host
//! @{
#define udd_enable_resume_interrupt()             (USBHS->USBHS_DEVIER = USBHS_DEVIER_EORSMES)
#define udd_disable_resume_interrupt()            (USBHS->USBHS_DEVIDR = USBHS_DEVIDR_EORSMEC)
#define Is_udd_resume_interrupt_enabled()         (Tst_bits(USBHS->USBHS_DEVIMR, USBHS_DEVIMR_EORSME))
#define udd_ack_resume()                          (USBHS->USBHS_DEVICR = USBHS_DEVICR_EORSMC)
#define udd_raise_resume()                        (USBHS->USBHS_DEVIFR = USBHS_DEVIFR_EORSMS)
#define Is_udd_resume()                           (Tst_bits(USBHS->USBHS_DEVISR, USBHS_DEVISR_EORSM))
//! @}

//! Manage wake-up event (=usb line activity)
//! The USB controller is reactivated by a filtered non-idle signal from the lines
//! @{
#define udd_enable_wake_up_interrupt()            (USBHS->USBHS_DEVIER = USBHS_DEVIER_WAKEUPES)
#define udd_disable_wake_up_interrupt()           (USBHS->USBHS_DEVIDR = USBHS_DEVIDR_WAKEUPEC)
#define Is_udd_wake_up_interrupt_enabled()        (Tst_bits(USBHS->USBHS_DEVIMR, USBHS_DEVIMR_WAKEUPE))
#define udd_ack_wake_up()                         (USBHS->USBHS_DEVICR = USBHS_DEVICR_WAKEUPC)
#define udd_raise_wake_up()                       (USBHS->USBHS_DEVIFR = USBHS_DEVIFR_WAKEUPS)
#define Is_udd_wake_up()                          (Tst_bits(USBHS->USBHS_DEVISR, USBHS_DEVISR_WAKEUP))
//! @}

//! Manage reset event
//! Set when a USB "End of Reset" has been detected
//! @{
#define udd_enable_reset_interrupt()              (USBHS->USBHS_DEVIER = USBHS_DEVIER_EORSTES)
#define udd_disable_reset_interrupt()             (USBHS->USBHS_DEVIDR = USBHS_DEVIDR_EORSTEC)
#define Is_udd_reset_interrupt_enabled()          (Tst_bits(USBHS->USBHS_DEVIMR, USBHS_DEVIMR_EORSTE))
#define udd_ack_reset()                           (USBHS->USBHS_DEVICR = USBHS_DEVICR_EORSTC)
#define udd_raise_reset()                         (USBHS->USBHS_DEVIFR = USBHS_DEVIFR_EORSTS)
#define Is_udd_reset()                            (Tst_bits(USBHS->USBHS_DEVISR, USBHS_DEVISR_EORST))
//! @}

//! Manage start of frame event
//! @{
#define udd_enable_sof_interrupt()                (USBHS->USBHS_DEVIER = USBHS_DEVIER_SOFES)
#define udd_disable_sof_interrupt()               (USBHS->USBHS_DEVIDR = USBHS_DEVIDR_SOFEC)
#define Is_udd_sof_interrupt_enabled()            (Tst_bits(USBHS->USBHS_DEVIMR, USBHS_DEVIMR_SOFE))
#define udd_ack_sof()                             (USBHS->USBHS_DEVICR = USBHS_DEVICR_SOFC)
#define udd_raise_sof()                           (USBHS->USBHS_DEVIFR = USBHS_DEVIFR_SOFS)
#define Is_udd_sof()                              (Tst_bits(USBHS->USBHS_DEVISR, USBHS_DEVISR_SOF))
#define udd_frame_number()                        (Rd_bitfield(USBHS->USBHS_DEVFNUM, USBHS_DEVFNUM_FNUM_Msk))
#define Is_udd_frame_number_crc_error()           (Tst_bits(USBHS->USBHS_DEVFNUM, USBHS_DEVFNUM_FNCERR))
//! @}

//! Manage Micro start of frame event (High Speed Only)
//! @{
#define udd_enable_msof_interrupt()               (USBHS->USBHS_DEVIER = USBHS_DEVIER_MSOFES)
#define udd_disable_msof_interrupt()              (USBHS->USBHS_DEVIDR = USBHS_DEVIDR_MSOFEC)
#define Is_udd_msof_interrupt_enabled()           (Tst_bits(USBHS->USBHS_DEVIMR, USBHS_DEVIMR_MSOFE))
#define udd_ack_msof()                            (USBHS->USBHS_DEVICR = USBHS_DEVIMR_MSOFE)
#define udd_raise_msof()                          (USBHS->USBHS_DEVIFR = USBHS_DEVIFR_MSOFS)
#define Is_udd_msof()                             (Tst_bits(USBHS->USBHS_DEVISR, USBHS_DEVISR_MSOF))
#define udd_micro_frame_number()                  \
	(Rd_bitfield(USBHS->USBHS_DEVFNUM, (USBHS_DEVFNUM_FNUM_Msk|USBHS_DEVFNUM_MFNUM_Msk)))
//! @}

//! Manage suspend event
//! @{
#define udd_enable_suspend_interrupt()            (USBHS->USBHS_DEVIER = USBHS_DEVIER_SUSPES)
#define udd_disable_suspend_interrupt()           (USBHS->USBHS_DEVIDR = USBHS_DEVIDR_SUSPEC)
#define Is_udd_suspend_interrupt_enabled()        (Tst_bits(USBHS->USBHS_DEVIMR, USBHS_DEVIMR_SUSPE))
#define udd_ack_suspend()                         (USBHS->USBHS_DEVICR = USBHS_DEVICR_SUSPC)
#define udd_raise_suspend()                       (USBHS->USBHS_DEVIFR = USBHS_DEVIFR_SUSPS)
#define Is_udd_suspend()                          (Tst_bits(USBHS->USBHS_DEVISR, USBHS_DEVISR_SUSP))
//! @}

//! @}

//! @name USBHS device address control
//! These macros manage the USBHS Device address.
//! @{
  //! enables USB device address
#define udd_enable_address()                      (Set_bits(USBHS->USBHS_DEVCTRL, USBHS_DEVCTRL_ADDEN))
  //! disables USB device address
#define udd_disable_address()                     (Clr_bits(USBHS->USBHS_DEVCTRL, USBHS_DEVCTRL_ADDEN))
#define Is_udd_address_enabled()                  (Tst_bits(USBHS->USBHS_DEVCTRL, USBHS_DEVCTRL_ADDEN))
  //! configures the USB device address
#define udd_configure_address(addr)               (Wr_bitfield(USBHS->USBHS_DEVCTRL, USBHS_DEVCTRL_UADD_Msk, addr))
  //! gets the currently configured USB device address
#define udd_get_configured_address()              (Rd_bitfield(USBHS->USBHS_DEVCTRL, USBHS_DEVCTRL_UADD_Msk))
//! @}


//! @name USBHS Device endpoint drivers
//! These macros manage the common features of the endpoints.
//! @{

//! Generic macro for USBHS registers that can be arrayed
//! @{
#define USBHS_ARRAY(reg,index)                   ((&(USBHS->reg))[(index)])
//! @}

//! @name USBHS Device endpoint configuration
//! @{
  //! enables the selected endpoint
#define udd_enable_endpoint(ep)                   (Set_bits(USBHS->USBHS_DEVEPT, USBHS_DEVEPT_EPEN0 << (ep)))
  //! disables the selected endpoint
#define udd_disable_endpoint(ep)                  (Clr_bits(USBHS->USBHS_DEVEPT, USBHS_DEVEPT_EPEN0 << (ep)))
  //! tests if the selected endpoint is enabled
#define Is_udd_endpoint_enabled(ep)               (Tst_bits(USBHS->USBHS_DEVEPT, USBHS_DEVEPT_EPEN0 << (ep)))
  //! resets the selected endpoint
#define udd_reset_endpoint(ep)                                         \
	do {                                                               \
		Set_bits(USBHS->USBHS_DEVEPT, USBHS_DEVEPT_EPRST0 << (ep)); \
		Clr_bits(USBHS->USBHS_DEVEPT, USBHS_DEVEPT_EPRST0 << (ep)); \
	} while (0)
  //! Tests if the selected endpoint is being reset
#define Is_udd_resetting_endpoint(ep)             (Tst_bits(USBHS->USBHS_DEVEPT, USBHS_DEVEPT_EPRST0 << (ep)))

  //! Configures the selected endpoint type
#define udd_configure_endpoint_type(ep, type)     (Wr_bitfield(USBHS_ARRAY(USBHS_DEVEPTCFG[0], ep), USBHS_DEVEPTCFG_EPTYPE_Msk, type))
  //! Gets the configured selected endpoint type
#define udd_get_endpoint_type(ep)                 (Rd_bitfield(USBHS_ARRAY(USBHS_DEVEPTCFG[0], ep), USBHS_DEVEPTCFG_EPTYPE_Msk))
  //! Enables the bank autoswitch for the selected endpoint
#define udd_enable_endpoint_bank_autoswitch(ep)   (Set_bits(USBHS_ARRAY(USBHS_DEVEPTCFG[0], ep), USBHS_DEVEPTCFG_AUTOSW))
  //! Disables the bank autoswitch for the selected endpoint
#define udd_disable_endpoint_bank_autoswitch(ep)    (Clr_bits(USBHS_ARRAY(USBHS_DEVEPTCFG[0], ep), USBHS_DEVEPTCFG_AUTOSW))
#define Is_udd_endpoint_bank_autoswitch_enabled(ep) (Tst_bits(USBHS_ARRAY(USBHS_DEVEPTCFG[0], ep), USBHS_DEVEPTCFG_AUTOSW))
  //! Configures the selected endpoint direction
#define udd_configure_endpoint_direction(ep, dir) (Wr_bitfield(USBHS_ARRAY(USBHS_DEVEPTCFG[0], ep), USBHS_DEVEPTCFG_EPDIR, dir))
  //! Gets the configured selected endpoint direction
#define udd_get_endpoint_direction(ep)            (Rd_bitfield(USBHS_ARRAY(USBHS_DEVEPTCFG[0], ep), USBHS_DEVEPTCFG_EPDIR))
#define Is_udd_endpoint_in(ep)                    (Tst_bits(USBHS_ARRAY(USBHS_DEVEPTCFG[0], ep), USBHS_DEVEPTCFG_EPDIR))
  //! Bounds given integer size to allowed range and rounds it up to the nearest
  //! available greater size, then applies register format of USBHS controller
  //! for endpoint size bit-field.
#define udd_format_endpoint_size(size)            (32 - clz(((uint32_t)Min(Max(size, 8), 1024) << 1) - 1) - 1 - 3)
  //! Configures the selected endpoint size
#define udd_configure_endpoint_size(ep, size)     (Wr_bitfield(USBHS_ARRAY(USBHS_DEVEPTCFG[0], ep), USBHS_DEVEPTCFG_EPSIZE_Msk, udd_format_endpoint_size(size)))
  //! Gets the configured selected endpoint size
#define udd_get_endpoint_size(ep)                 (8 << Rd_bitfield(USBHS_ARRAY(USBHS_DEVEPTCFG[0], ep), USBHS_DEVEPTCFG_EPSIZE_Msk))
  //! Configures the selected endpoint number of banks
#define udd_configure_endpoint_bank(ep, bank)     (Wr_bitfield(USBHS_ARRAY(USBHS_DEVEPTCFG[0], ep), USBHS_DEVEPTCFG_EPBK_Msk, bank))
  //! Gets the configured selected endpoint number of banks
#define udd_get_endpoint_bank(ep)                 (Rd_bitfield(USBHS_ARRAY(USBHS_DEVEPTCFG[0], ep), USBHS_DEVEPTCFG_EPBK_Msk)+1)
  //! Allocates the configuration selected endpoint in DPRAM memory
#define udd_allocate_memory(ep)                   (Set_bits(USBHS_ARRAY(USBHS_DEVEPTCFG[0], ep), USBHS_DEVEPTCFG_ALLOC))
  //! un-allocates the configuration selected endpoint in DPRAM memory
#define udd_unallocate_memory(ep)                 (Clr_bits(USBHS_ARRAY(USBHS_DEVEPTCFG[0], ep), USBHS_DEVEPTCFG_ALLOC))
#define Is_udd_memory_allocated(ep)               (Tst_bits(USBHS_ARRAY(USBHS_DEVEPTCFG[0], ep), USBHS_DEVEPTCFG_ALLOC))

  //! Configures selected endpoint in one step
#define udd_configure_endpoint(ep, type, dir, size, bank) (\
	Wr_bits(USBHS_ARRAY(USBHS_DEVEPTCFG[0], ep), USBHS_DEVEPTCFG_EPTYPE_Msk |\
			USBHS_DEVEPTCFG_EPDIR  |\
			USBHS_DEVEPTCFG_EPSIZE_Msk |\
			USBHS_DEVEPTCFG_EPBK_Msk ,   \
			(((uint32_t)(type) << USBHS_DEVEPTCFG_EPTYPE_Pos) & USBHS_DEVEPTCFG_EPTYPE_Msk) |\
			(((uint32_t)(dir ) << USBHS_DEVEPTCFG_EPDIR_Pos ) & USBHS_DEVEPTCFG_EPDIR) |\
			( (uint32_t)udd_format_endpoint_size(size) << USBHS_DEVEPTCFG_EPSIZE_Pos) |\
			(((uint32_t)(bank) << USBHS_DEVEPTCFG_EPBK_Pos) & USBHS_DEVEPTCFG_EPBK_Msk))\
)
  //! Tests if current endpoint is configured
#define Is_udd_endpoint_configured(ep)            (Tst_bits(USBHS_ARRAY(USBHS_DEVEPTISR[0], ep), USBHS_DEVEPTISR_CFGOK))
  //! Returns the control direction
#define udd_control_direction()                   (Rd_bitfield(USBHS_ARRAY(USBHS_DEVEPTISR[0], EP_CONTROL), USBHS_DEVEPTISR_CTRLDIR))

  //! Resets the data toggle sequence
#define udd_reset_data_toggle(ep)                 (USBHS_ARRAY(USBHS_DEVEPTIER[0], ep) = USBHS_DEVEPTIER_RSTDTS)
  //! Tests if the data toggle sequence is being reset
#define Is_udd_data_toggle_reset(ep)              (Tst_bits(USBHS_ARRAY(USBHS_DEVEPTIMR[0], ep), USBHS_DEVEPTIMR_RSTDT))
  //! Returns data toggle
#define udd_data_toggle(ep)                       (Rd_bitfield(USBHS_ARRAY(USBHS_DEVEPTISR[0], ep), USBHS_DEVEPTISR_DTSEQ_Msk))
//! @}


//! @name USBHS Device control endpoint
//! These macros control the endpoints.
//! @{

//! @name USBHS Device control endpoint interrupts
//! These macros control the endpoints interrupts.
//! @{
  //! Enables the selected endpoint interrupt
#define udd_enable_endpoint_interrupt(ep)         (USBHS->USBHS_DEVIER = USBHS_DEVIER_PEP_0 << (ep))
  //! Disables the selected endpoint interrupt
#define udd_disable_endpoint_interrupt(ep)        (USBHS->USBHS_DEVIDR = USBHS_DEVIDR_PEP_0 << (ep))
  //! Tests if the selected endpoint interrupt is enabled
#define Is_udd_endpoint_interrupt_enabled(ep)     (Tst_bits(USBHS->USBHS_DEVIMR, USBHS_DEVIMR_PEP_0 << (ep)))
  //! Tests if an interrupt is triggered by the selected endpoint
#define Is_udd_endpoint_interrupt(ep)             (Tst_bits(USBHS->USBHS_DEVISR, USBHS_DEVISR_PEP_0 << (ep)))
  //! Returns the lowest endpoint number generating an endpoint interrupt or MAX_PEP_NB if none
#define udd_get_interrupt_endpoint_number()       (ctz(((USBHS->USBHS_DEVISR >> USBHS_DEVISR_PEP_Pos) & \
                                                   (USBHS->USBHS_DEVIMR >> USBHS_DEVIMR_PEP_Pos)) |     \
                                                   (1 << MAX_PEP_NB)))
#define USBHS_DEVISR_PEP_Pos   12
#define USBHS_DEVIMR_PEP_Pos   12
//! @}

//! @name USBHS Device control endpoint errors
//! These macros control the endpoint errors.
//! @{
  //! Enables the STALL handshake
#define udd_enable_stall_handshake(ep)            (USBHS_ARRAY(USBHS_DEVEPTIER[0], ep) = USBHS_DEVEPTIER_STALLRQS)
  //! Disables the STALL handshake
#define udd_disable_stall_handshake(ep)           (USBHS_ARRAY(USBHS_DEVEPTIDR[0], ep) = USBHS_DEVEPTIDR_STALLRQC)
  //! Tests if STALL handshake request is running
#define Is_udd_endpoint_stall_requested(ep)       (Tst_bits(USBHS_ARRAY(USBHS_DEVEPTIMR[0], ep), USBHS_DEVEPTIMR_STALLRQ))
  //! Tests if STALL sent
#define Is_udd_stall(ep)                          (Tst_bits(USBHS_ARRAY(USBHS_DEVEPTISR[0], ep), USBHS_DEVEPTISR_STALLEDI))
  //! ACKs STALL sent
#define udd_ack_stall(ep)                         (USBHS_ARRAY(USBHS_DEVEPTICR[0], ep) = USBHS_DEVEPTICR_STALLEDIC)
  //! Raises STALL sent
#define udd_raise_stall(ep)                       (USBHS_ARRAY(USBHS_DEVEPTIFR[0], ep) = USBHS_DEVEPTIFR_STALLEDIS)
  //! Enables STALL sent interrupt
#define udd_enable_stall_interrupt(ep)            (USBHS_ARRAY(USBHS_DEVEPTIER[0], ep) = USBHS_DEVEPTIER_STALLEDES)
  //! Disables STALL sent interrupt
#define udd_disable_stall_interrupt(ep)           (USBHS_ARRAY(USBHS_DEVEPTIDR[0], ep) = USBHS_DEVEPTIDR_STALLEDEC)
  //! Tests if STALL sent interrupt is enabled
#define Is_udd_stall_interrupt_enabled(ep)        (Tst_bits(USBHS_ARRAY(USBHS_DEVEPTIMR[0], ep), USBHS_DEVEPTIMR_STALLEDE))

  //! Tests if NAK OUT received
#define Is_udd_nak_out(ep)                        (Tst_bits(USBHS_ARRAY(USBHS_DEVEPTISR[0], ep), USBHS_DEVEPTISR_NAKOUTI))
  //! ACKs NAK OUT received
#define udd_ack_nak_out(ep)                       (USBHS_ARRAY(USBHS_DEVEPTICR[0], ep) = USBHS_DEVEPTICR_NAKOUTIC)
  //! Raises NAK OUT received
#define udd_raise_nak_out(ep)                     (USBHS_ARRAY(USBHS_DEVEPTIFR[0], ep) = USBHS_DEVEPTIFR_NAKOUTIS)
  //! Enables NAK OUT interrupt
#define udd_enable_nak_out_interrupt(ep)          (USBHS_ARRAY(USBHS_DEVEPTIER[0], ep) = USBHS_DEVEPTIER_NAKOUTES)
  //! Disables NAK OUT interrupt
#define udd_disable_nak_out_interrupt(ep)         (USBHS_ARRAY(USBHS_DEVEPTIDR[0], ep) = USBHS_DEVEPTIDR_NAKOUTEC)
  //! Tests if NAK OUT interrupt is enabled
#define Is_udd_nak_out_interrupt_enabled(ep)      (Tst_bits(USBHS_ARRAY(USBHS_DEVEPTIMR[0], ep), USBHS_DEVEPTIMR_NAKOUTE))

  //! Tests if NAK IN received
#define Is_udd_nak_in(ep)                         (Tst_bits(USBHS_ARRAY(USBHS_DEVEPTISR[0], ep), USBHS_DEVEPTISR_NAKINI))
  //! ACKs NAK IN received
#define udd_ack_nak_in(ep)                        (USBHS_ARRAY(USBHS_DEVEPTICR[0], ep) = USBHS_DEVEPTICR_NAKINIC)
  //! Raises NAK IN received
#define udd_raise_nak_in(ep)                      (USBHS_ARRAY(USBHS_DEVEPTIFR[0], ep) = USBHS_DEVEPTIFR_NAKINIS)
  //! Enables NAK IN interrupt
#define udd_enable_nak_in_interrupt(ep)           (USBHS_ARRAY(USBHS_DEVEPTIER[0], ep) = USBHS_DEVEPTIER_NAKINES)
  //! Disables NAK IN interrupt
#define udd_disable_nak_in_interrupt(ep)          (USBHS_ARRAY(USBHS_DEVEPTIDR[0], ep) = USBHS_DEVEPTIDR_NAKINEC)
  //! Tests if NAK IN interrupt is enabled
#define Is_udd_nak_in_interrupt_enabled(ep)       (Tst_bits(USBHS_ARRAY(USBHS_DEVEPTIMR[0], ep), USBHS_DEVEPTIMR_NAKINE))

  //! ACKs endpoint isochronous overflow interrupt
#define udd_ack_overflow_interrupt(ep)            (USBHS_ARRAY(USBHS_DEVEPTICR[0], ep) = USBHS_DEVEPTICR_OVERFIC)
  //! Raises endpoint isochronous overflow interrupt
#define udd_raise_overflow_interrupt(ep)          (USBHS_ARRAY(USBHS_DEVEPTIFR[0], ep) = USBHS_DEVEPTIFR_OVERFIS)
  //! Tests if an overflow occurs
#define Is_udd_overflow(ep)                       (Tst_bits(USBHS_ARRAY(USBHS_DEVEPTISR[0], ep), USBHS_DEVEPTISR_OVERFI))
  //! Enables overflow interrupt
#define udd_enable_overflow_interrupt(ep)         (USBHS_ARRAY(USBHS_DEVEPTIER[0], ep) = USBHS_DEVEPTIER_OVERFES)
  //! Disables overflow interrupt
#define udd_disable_overflow_interrupt(ep)        (USBHS_ARRAY(USBHS_DEVEPTIDR[0], ep) = USBHS_DEVEPTIDR_OVERFEC)
  //! Tests if overflow interrupt is enabled
#define Is_udd_overflow_interrupt_enabled(ep)     (Tst_bits(USBHS_ARRAY(USBHS_DEVEPTIMR[0], ep), USBHS_DEVEPTIMR_OVERFE))

  //! ACKs endpoint isochronous underflow interrupt
#define udd_ack_underflow_interrupt(ep)           (USBHS_ARRAY(USBHS_DEVEPTICR[0], ep) = USBHS_DEVEPTICR_UNDERFIC)
  //! Raises endpoint isochronous underflow interrupt
#define udd_raise_underflow_interrupt(ep)         (USBHS_ARRAY(USBHS_DEVEPTIFR[0], ep) = USBHS_DEVEPTIFR_UNDERFIS)
  //! Tests if an underflow occurs
#define Is_udd_underflow(ep)                      (Tst_bits(USBHS_ARRAY(USBHS_DEVEPTISR[0], ep), USBHS_DEVEPTISR_UNDERFI))
  //! Enables underflow interrupt
#define udd_enable_underflow_interrupt(ep)        (USBHS_ARRAY(USBHS_DEVEPTIER[0], ep) = USBHS_DEVEPTIER_UNDERFES)
  //! Disables underflow interrupt
#define udd_disable_underflow_interrupt(ep)       (USBHS_ARRAY(USBHS_DEVEPTIDR[0], ep) = USBHS_DEVEPTIDR_UNDERFEC)
  //! Tests if underflow interrupt is enabled
#define Is_udd_underflow_interrupt_enabled(ep)    (Tst_bits(USBHS_ARRAY(USBHS_DEVEPTIMR[0], ep), USBHS_DEVEPTIMR_UNDERFE))

  //! Tests if CRC ERROR ISO OUT detected
#define Is_udd_crc_error(ep)                      (Tst_bits(USBHS_ARRAY(USBHS_DEVEPTISR[0], ep), USBHS_DEVEPTISR_CRCERRI))
  //! ACKs CRC ERROR ISO OUT detected
#define udd_ack_crc_error(ep)                     (USBHS_ARRAY(USBHS_DEVEPTICR[0], ep) = USBHS_DEVEPTICR_CRCERRIC)
  //! Raises CRC ERROR ISO OUT detected
#define udd_raise_crc_error(ep)                   (USBHS_ARRAY(USBHS_DEVEPTIFR[0], ep) = USBHS_DEVEPTIFR_CRCERRIS)
  //! Enables CRC ERROR ISO OUT detected interrupt
#define udd_enable_crc_error_interrupt(ep)        (USBHS_ARRAY(USBHS_DEVEPTIER[0], ep) = USBHS_DEVEPTIER_CRCERRES)
  //! Disables CRC ERROR ISO OUT detected interrupt
#define udd_disable_crc_error_interrupt(ep)       (USBHS_ARRAY(USBHS_DEVEPTIDR[0], ep) = USBHS_DEVEPTIDR_CRCERREC)
  //! Tests if CRC ERROR ISO OUT detected interrupt is enabled
#define Is_udd_crc_error_interrupt_enabled(ep)    (Tst_bits(USBHS_ARRAY(USBHS_DEVEPTIMR[0], ep), USBHS_DEVEPTIMR_CRCERRE))
//! @}

//! @name USBHS Device control endpoint transfer
//! These macros control the endpoint transfer.
//! @{

  //! Tests if endpoint read allowed
#define Is_udd_read_enabled(ep)                   (Tst_bits(USBHS_ARRAY(USBHS_DEVEPTISR[0], ep), USBHS_DEVEPTISR_RWALL))
  //! Tests if endpoint write allowed
#define Is_udd_write_enabled(ep)                  (Tst_bits(USBHS_ARRAY(USBHS_DEVEPTISR[0], ep), USBHS_DEVEPTISR_RWALL))

  //! Returns the byte count
#define udd_byte_count(ep)                        (Rd_bitfield(USBHS_ARRAY(USBHS_DEVEPTISR[0], ep), USBHS_DEVEPTISR_BYCT_Msk))
  //! Clears FIFOCON bit
#define udd_ack_fifocon(ep)                       (USBHS_ARRAY(USBHS_DEVEPTIDR[0], ep) = USBHS_DEVEPTIDR_FIFOCONC)
  //! Tests if FIFOCON bit set
#define Is_udd_fifocon(ep)                        (Tst_bits(USBHS_ARRAY(USBHS_DEVEPTIMR[0], ep), USBHS_DEVEPTIMR_FIFOCON))

  //! Returns the number of busy banks
#define udd_nb_busy_bank(ep)                      (Rd_bitfield(USBHS_ARRAY(USBHS_DEVEPTISR[0], ep), USBHS_DEVEPTISR_NBUSYBK_Msk))
  //! Returns the number of the current bank
#define udd_current_bank(ep)                      (Rd_bitfield(USBHS_ARRAY(USBHS_DEVEPTISR[0], ep), USBHS_DEVEPTISR_CURRBK_Msk))
  //! Kills last bank
#define udd_kill_last_in_bank(ep)                 (USBHS_ARRAY(USBHS_DEVEPTIER[0], ep) = USBHS_DEVEPTIER_KILLBKS)
#define Is_udd_kill_last(ep)                      (Tst_bits(USBHS_ARRAY(USBHS_DEVEPTIMR[0], ep), USBHS_DEVEPTIMR_KILLBK))
  //! Tests if last bank killed
#define Is_udd_last_in_bank_killed(ep)            (!Tst_bits(USBHS_ARRAY(USBHS_DEVEPTIMR[0], ep), USBHS_DEVEPTIMR_KILLBK))
  //! Forces all banks full (OUT) or free (IN) interrupt
#define udd_force_bank_interrupt(ep)              (USBHS_ARRAY(USBHS_DEVEPTIFR[0], ep) = USBHS_DEVEPTIFR_NBUSYBKS)
  //! Unforces all banks full (OUT) or free (IN) interrupt
#define udd_unforce_bank_interrupt(ep)            (USBHS_ARRAY(USBHS_DEVEPTIFR[0], ep) = USBHS_DEVEPTIFR_NBUSYBKS)
  //! Enables all banks full (OUT) or free (IN) interrupt
#define udd_enable_bank_interrupt(ep)             (USBHS_ARRAY(USBHS_DEVEPTIER[0], ep) = USBHS_DEVEPTIER_NBUSYBKES)
  //! Disables all banks full (OUT) or free (IN) interrupt
#define udd_disable_bank_interrupt(ep)            (USBHS_ARRAY(USBHS_DEVEPTIDR[0], ep) = USBHS_DEVEPTIDR_NBUSYBKEC)
  //! Tests if all banks full (OUT) or free (IN) interrupt enabled
#define Is_udd_bank_interrupt_enabled(ep)         (Tst_bits(USBHS_ARRAY(USBHS_DEVEPTIMR[0], ep), USBHS_DEVEPTIMR_NBUSYBKE))

  //! Tests if SHORT PACKET received
#define Is_udd_short_packet(ep)                   (Tst_bits(USBHS_ARRAY(USBHS_DEVEPTISR[0], ep), USBHS_DEVEPTISR_SHORTPACKET))
  //! ACKs SHORT PACKET received
#define udd_ack_short_packet(ep)                  (USBHS_ARRAY(USBHS_DEVEPTICR[0], ep) = USBHS_DEVEPTICR_SHORTPACKETC)
  //! Raises SHORT PACKET received
#define udd_raise_short_packet(ep)                (USBHS_ARRAY(USBHS_DEVEPTIFR[0], ep) = USBHS_DEVEPTIFR_SHORTPACKETS)
  //! Enables SHORT PACKET received interrupt
#define udd_enable_short_packet_interrupt(ep)     (USBHS_ARRAY(USBHS_DEVEPTIER[0], ep) = USBHS_DEVEPTIER_SHORTPACKETES)
  //! Disables SHORT PACKET received interrupt
#define udd_disable_short_packet_interrupt(ep)    (USBHS_ARRAY(USBHS_DEVEPTIDR[0], ep) = USBHS_DEVEPTIDR_SHORTPACKETEC)
  //! Tests if SHORT PACKET received interrupt is enabled
#define Is_udd_short_packet_interrupt_enabled(ep) (Tst_bits(USBHS_ARRAY(USBHS_DEVEPTIMR[0], ep), USBHS_DEVEPTIMR_SHORTPACKETE))

  //! Tests if SETUP received
#define Is_udd_setup_received(ep)                    (Tst_bits(USBHS_ARRAY(USBHS_DEVEPTISR[0], ep), USBHS_DEVEPTISR_RXSTPI))
  //! ACKs SETUP received
#define udd_ack_setup_received(ep)                   (USBHS_ARRAY(USBHS_DEVEPTICR[0], ep) = USBHS_DEVEPTICR_RXSTPIC)
  //! Raises SETUP received
#define udd_raise_setup_received(ep)                 (USBHS_ARRAY(USBHS_DEVEPTIFR[0], ep) = USBHS_DEVEPTIFR_RXSTPIS)
  //! Enables SETUP received interrupt
#define udd_enable_setup_received_interrupt(ep)      (USBHS_ARRAY(USBHS_DEVEPTIER[0], ep) = USBHS_DEVEPTIER_RXSTPES)
  //! Disables SETUP received interrupt
#define udd_disable_setup_received_interrupt(ep)     (USBHS_ARRAY(USBHS_DEVEPTIDR[0], ep) = USBHS_DEVEPTIDR_RXSTPEC)
  //! Tests if SETUP received interrupt is enabled
#define Is_udd_setup_received_interrupt_enabled(ep)  (Tst_bits(USBHS_ARRAY(USBHS_DEVEPTIMR[0], ep), USBHS_DEVEPTIMR_RXSTPE))

  //! Tests if OUT received
#define Is_udd_out_received(ep)                   (Tst_bits(USBHS_ARRAY(USBHS_DEVEPTISR[0], ep), USBHS_DEVEPTISR_RXOUTI))
  //! ACKs OUT received
#define udd_ack_out_received(ep)                  (USBHS_ARRAY(USBHS_DEVEPTICR[0], ep) = USBHS_DEVEPTICR_RXOUTIC)
  //! Raises OUT received
#define udd_raise_out_received(ep)                (USBHS_ARRAY(USBHS_DEVEPTIFR[0], ep) = USBHS_DEVEPTIFR_RXOUTIS)
  //! Enables OUT received interrupt
#define udd_enable_out_received_interrupt(ep)     (USBHS_ARRAY(USBHS_DEVEPTIER[0], ep) = USBHS_DEVEPTIER_RXOUTES)
  //! Disables OUT received interrupt
#define udd_disable_out_received_interrupt(ep)    (USBHS_ARRAY(USBHS_DEVEPTIDR[0], ep) = USBHS_DEVEPTIDR_RXOUTEC)
  //! Tests if OUT received interrupt is enabled
#define Is_udd_out_received_interrupt_enabled(ep) (Tst_bits(USBHS_ARRAY(USBHS_DEVEPTIMR[0], ep), USBHS_DEVEPTIMR_RXOUTE))

  //! Tests if IN sending
#define Is_udd_in_send(ep)                        (Tst_bits(USBHS_ARRAY(USBHS_DEVEPTISR[0], ep), USBHS_DEVEPTISR_TXINI))
  //! ACKs IN sending
#define udd_ack_in_send(ep)                       (USBHS_ARRAY(USBHS_DEVEPTICR[0], ep) = USBHS_DEVEPTICR_TXINIC)
  //! Raises IN sending
#define udd_raise_in_send(ep)                     (USBHS_ARRAY(USBHS_DEVEPTIFR[0], ep) = USBHS_DEVEPTIFR_TXINIS)
  //! Enables IN sending interrupt
#define udd_enable_in_send_interrupt(ep)          (USBHS_ARRAY(USBHS_DEVEPTIER[0], ep) = USBHS_DEVEPTIER_TXINES)
  //! Disables IN sending interrupt
#define udd_disable_in_send_interrupt(ep)         (USBHS_ARRAY(USBHS_DEVEPTIDR[0], ep) = USBHS_DEVEPTIDR_TXINEC)
  //! Tests if IN sending interrupt is enabled
#define Is_udd_in_send_interrupt_enabled(ep)      (Tst_bits(USBHS_ARRAY(USBHS_DEVEPTIMR[0], ep), USBHS_DEVEPTIMR_TXINE))


  //! Get 64-, 32-, 16- or 8-bit access to FIFO data register of selected endpoint.
  //! @param ep Endpoint of which to access FIFO data register
  //! @param scale Data scale in bits: 64, 32, 16 or 8
  //! @return Volatile 64-, 32-, 16- or 8-bit data pointer to FIFO data register
  //! @warning It is up to the user of this macro to make sure that all accesses
  //! are aligned with their natural boundaries except 64-bit accesses which
  //! require only 32-bit alignment.
  //! @warning It is up to the user of this macro to make sure that used HSB
  //! addresses are identical to the DPRAM internal pointer modulo 32 bits.
#define udd_get_endpoint_fifo_access(ep, scale) \
		(((volatile TPASTE2(U, scale) (*)[0x8000 / ((scale) / 8)])USBHS_RAM_ADDR)[(ep)])

//! @name USBHS endpoint DMA drivers
//! These macros manage the common features of the endpoint DMA channels.
//! @{

  //! Maximum transfer size on USB DMA
#define UDD_ENDPOINT_MAX_TRANS 0x10000
  //! Enables the disabling of HDMA requests by endpoint interrupts
#define udd_enable_endpoint_int_dis_hdma_req(ep)     (USBHS_ARRAY(USBHS_DEVEPTIER[0](ep) = USBHS_DEVEPTIER_EPDISHDMAS)
  //! Disables the disabling of HDMA requests by endpoint interrupts
#define udd_disable_endpoint_int_dis_hdma_req(ep)    (USBHS_ARRAY(USBHS_DEVEPTIDR[0](ep) = USBHS_DEVEPTIDR_EPDISHDMAC)
  //! Tests if the disabling of HDMA requests by endpoint interrupts is enabled
#define Is_udd_endpoint_int_dis_hdma_req_enabled(ep) (Tst_bits(USBHS_ARRAY(USBHS_DEVEPTIMR[0](ep), USBHS_DEVEPTIMR_EPDISHDMA))

  //! Raises the selected endpoint DMA channel interrupt
#define udd_raise_endpoint_dma_interrupt(ep)         (USBHS->USBHS_DEVIFR = USBHS_DEVIFR_DMA_1 << ((ep) - 1))
  //! Raises the selected endpoint DMA channel interrupt
#define udd_clear_endpoint_dma_interrupt(ep)         (USBHS->USBHS_DEVICR = USBHS_DEVISR_DMA_1 << ((ep) - 1))
  //! Tests if an interrupt is triggered by the selected endpoint DMA channel
#define Is_udd_endpoint_dma_interrupt(ep)            (Tst_bits(USBHS->USBHS_DEVISR, USBHS_DEVISR_DMA_1 << ((ep) - 1)))
  //! Enables the selected endpoint DMA channel interrupt
#define udd_enable_endpoint_dma_interrupt(ep)        (USBHS->USBHS_DEVIER = USBHS_DEVIER_DMA_1 << ((ep) - 1))
  //! Disables the selected endpoint DMA channel interrupt
#define udd_disable_endpoint_dma_interrupt(ep)       (USBHS->USBHS_DEVIDR = USBHS_DEVIDR_DMA_1 << ((ep) - 1))
  //! Tests if the selected endpoint DMA channel interrupt is enabled
#define Is_udd_endpoint_dma_interrupt_enabled(ep)    (Tst_bits(USBHS->USBHS_DEVIMR, USBHS_DEVIMR_DMA_1 << ((ep) - 1)))

  //! Access points to the USBHS device DMA memory map with arrayed registers
  //! @{
      //! Structure for DMA next descriptor register
typedef struct {
	uint32_t *NXT_DSC_ADD;
} uotghs_dma_nextdesc_t;
      //! Structure for DMA control register
typedef struct {
	uint32_t CHANN_ENB:1,
		LDNXT_DSC:1,
		END_TR_EN:1,
		END_B_EN:1,
		END_TR_IT:1,
		END_BUFFIT:1,
		DESC_LD_IT:1,
		BUST_LCK:1,
		reserved:8,
		BUFF_LENGTH:16;
} uotghs_dma_control_t;
      //! Structure for DMA status register
typedef struct {
	uint32_t CHANN_ENB:1,
		CHANN_ACT:1,
		reserved0:2,
		END_TR_ST:1,
		END_BF_ST:1,
		DESC_LDST:1,
		reserved1:9,
		BUFF_COUNT:16;
} uotghs_dma_status_t;
      //! Structure for DMA descriptor
typedef struct {
	union {
		uint32_t nextdesc;
		uotghs_dma_nextdesc_t NEXTDESC;
	};
	uint32_t addr;
	union {
		uint32_t control;
		uotghs_dma_control_t CONTROL;
	};
	uint32_t reserved;
} sam_uotghs_dmadesc_t, uotghs_dmadesc_t;
      //! Structure for DMA registers in a channel
typedef struct {
	union {
		uint32_t nextdesc;
		uotghs_dma_nextdesc_t NEXTDESC;
	};
	uint32_t addr;
	union {
		uint32_t control;
		uotghs_dma_control_t CONTROL;
	};
	union {
		unsigned long status;
		uotghs_dma_status_t STATUS;
	};
} sam_uotghs_dmach_t, uotghs_dmach_t;
      //! DMA channel control command
#define UDD_ENDPOINT_DMA_STOP_NOW                 (0)
#define UDD_ENDPOINT_DMA_RUN_AND_STOP             (USBHS_DEVDMACONTROL_CHANN_ENB)
#define UDD_ENDPOINT_DMA_LOAD_NEXT_DESC           (USBHS_DEVDMACONTROL_LDNXT_DSC)
#define UDD_ENDPOINT_DMA_RUN_AND_LINK             (USBHS_DEVDMACONTROL_CHANN_ENB|USBHS_DEVDMACONTROL_LDNXT_DSC)
      //! Structure for DMA registers
#define USBHS_UDDMA_ARRAY(ep)                    (((volatile uotghs_dmach_t *)USBHS->USBHS_DEVDMA)[(ep) - 1])

      //! Set control desc to selected endpoint DMA channel
#define udd_endpoint_dma_set_control(ep,desc)     (USBHS_UDDMA_ARRAY(ep).control = desc)
      //! Get control desc to selected endpoint DMA channel
#define udd_endpoint_dma_get_control(ep)          (USBHS_UDDMA_ARRAY(ep).control)
      //! Set RAM address to selected endpoint DMA channel
#define udd_endpoint_dma_set_addr(ep,add)         (USBHS_UDDMA_ARRAY(ep).addr = add)
      //! Get status to selected endpoint DMA channel
#define udd_endpoint_dma_get_status(ep)           (USBHS_UDDMA_ARRAY(ep).status)
   //! @}
//! @}

//! @}
//! @}
//! @}
//! @}


/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

#endif /* USBHS_DEVICE_H_INCLUDED */
