/**
 * \file
 *
 * \brief USB OTG Driver for USBHS.
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

#ifndef USBHS_OTG_H_INCLUDED
#define USBHS_OTG_H_INCLUDED

#include "compiler.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Get USB VBus/ID pin configuration in board configuration */
#include "conf_board.h"
#include "board.h"
#include "ioport.h"
#include "pio.h"

#if 0	// dc42 pio_handler.h clashes with the PIO interrupt handler in WInterrupts.c, .h

#include "pio_handler.h"

__always_inline static void otg_io_pin_init(uint32_t pin, uint32_t flags,
    IRQn_Type port_irqn, uint8_t irq_level,
    void (*handler)(uint32_t,uint32_t), uint32_t wkup)
{
	// IOPORT must be initialized before by ioport_init(), \see ioport_group.
	pio_handler_set_pin(pin, flags, handler);
	ioport_set_pin_sense_mode(pin, IOPORT_SENSE_BOTHEDGES);
	NVIC_SetPriority(port_irqn, irq_level);
	NVIC_EnableIRQ(port_irqn);
	pio_enable_pin_interrupt(pin);
	if (wkup) {
		pmc_set_fast_startup_input(wkup);
	}
}

#endif

//! \ingroup usb_group
//! \defgroup otg_group USBHS OTG Driver
//! USBHS low-level driver for OTG features
//!
//! @{

/**
 * \brief USB interrupt level
 * By default USB interrupt have low priority.
 */
#ifndef USB_INT_LEVEL
# define USB_INT_LEVEL 5
#endif

/**
 * \brief Initialize the dual role
 * This function is implemented in usbhs_host.c file.
 *
 * \return \c true if the ID pin management has been started, otherwise \c false.
 */
bool otg_dual_enable(void);

/**
 * \brief Uninitialize the dual role
 * This function is implemented in usbhs_host.c file.
 */
void otg_dual_disable(void);


//! @name USBHS OTG ID pin management
//! The ID pin come from the USB OTG connector (A and B receptacle) and
//! allows to select the USB mode host or device.
//!
//! The ID pin can be managed through PIO pin.
//! This feature is optional, and it is enabled if USB_ID_PIN
//! is defined in board.h and CONF_BOARD_USB_ID_DETECT defined in
//! conf_board.h.
//! @{
#define OTG_ID_DETECT       (defined(CONF_BOARD_USB_PORT) && \
    defined(CONF_BOARD_USB_ID_DETECT))
#define OTG_ID_IO           (defined(USB_ID_PIN) && OTG_ID_DETECT)

#if OTG_ID_IO
#define otg_id_init(handler)         otg_io_pin_init(USB_ID_PIN, USB_ID_FLAGS, \
			USB_ID_PIN_IRQn, USB_INT_LEVEL, handler, false)
# define otg_id_interrupt_enable()   pio_enable_pin_interrupt(USB_ID_PIN)
# define otg_id_interrupt_disable()  pio_disable_pin_interrupt(USB_ID_PIN)
# define Is_otg_id_device()          ioport_get_pin_level(USB_ID_PIN)
# define Is_otg_id_host()            (!Is_otg_id_device())
#endif

#define otg_force_device_mode()             (Set_bits(USBHS->USBHS_CTRL, USBHS_CTRL_UIMOD))
   //! Test if device mode is forced
#define Is_otg_device_mode_forced()         (Tst_bits(USBHS->USBHS_CTRL, USBHS_CTRL_UIMOD))
   //! Disable external OTG_ID pin and force host mode
#define otg_force_host_mode()               (Clr_bits(USBHS->USBHS_CTRL, USBHS_CTRL_UIMOD))
   //! Test if host mode is forced
#define Is_otg_host_mode_forced()           (!Tst_bits(USBHS->USBHS_CTRL, USBHS_CTRL_UIMOD))

//! @}

//! @name USBHS OTG VBUS pin management
//! USBHS peripheral does not support VBUS management and it's monitored by a PIO
//! pin.
//! This feature is optional, and it is enabled if USB_VBUS_PIN is defined in
//! board.h and CONF_BOARD_USB_VBUS_DETECT defined in conf_board.h.
//!
//! @note ioport_init() must be invoked before using VBus pin functions since
//!       they use IOPORT API, \see ioport_group.
//!
//! @{
#define OTG_VBUS_DETECT (defined(CONF_BOARD_USB_PORT) && \
    defined(CONF_BOARD_USB_VBUS_DETECT))
#define OTG_VBUS_IO     (defined(USB_VBUS_PIN) && OTG_VBUS_DETECT)
#ifndef USB_VBUS_WKUP
#  define USB_VBUS_WKUP 0
#endif

#define otg_vbus_init(handler)       otg_io_pin_init(USB_VBUS_PIN, USB_VBUS_FLAGS, \
  USB_VBUS_PIN_IRQn, USB_INT_LEVEL, handler, USB_VBUS_WKUP)
#define Is_otg_vbus_high()           ioport_get_pin_level(USB_VBUS_PIN)
#define Is_otg_vbus_low()            (!Is_otg_vbus_high())
#define otg_enable_vbus_interrupt()  pio_enable_pin_interrupt(USB_VBUS_PIN)
#define otg_disable_vbus_interrupt() pio_disable_pin_interrupt(USB_VBUS_PIN)
//! @}

//! @name USBHS OTG main management
//! These macros allows to enable/disable pad and USBHS hardware
//! @{
  //! Reset USB macro
#define otg_reset()                         \
	do {                                    \
		USBHS->USBHS_CTRL = 0;            \
		while( USBHS->USBHS_SR & 0x3FFF) {\
			USBHS->USBHS_SCR = 0xFFFFFFFF;\
		}                                   \
	} while (0)
  //! Enable USB macro
#define otg_enable()                        (Set_bits(USBHS->USBHS_CTRL, USBHS_CTRL_USBE))
  //! Disable USB macro                     
#define otg_disable()                       (Clr_bits(USBHS->USBHS_CTRL, USBHS_CTRL_USBE))
#define Is_otg_enabled()                    (Tst_bits(USBHS->USBHS_CTRL, USBHS_CTRL_USBE))

 //! Check Clock Usable               
  //! For parts with HS feature, this one corresponding at UTMI clock
#define Is_otg_clock_usable()               (Tst_bits(USBHS->USBHS_SR, USBHS_SR_CLKUSABLE))

  //! Stop (freeze) internal USB clock
#define otg_freeze_clock()                  (Set_bits(USBHS->USBHS_CTRL, USBHS_CTRL_FRZCLK))
#define otg_unfreeze_clock()                (Clr_bits(USBHS->USBHS_CTRL, USBHS_CTRL_FRZCLK))
#define Is_otg_clock_frozen()               (Tst_bits(USBHS->USBHS_CTRL, USBHS_CTRL_FRZCLK))

   //! Enables RDERR interrupt
#define otg_enable_rderr_interrupt()          (Set_bits(USBHS->USBHS_CTRL, USBHS_CTRL_RDERRE))
  //! Disables RDERR interrupt
#define otg_disable_rderr_interrupt()         (Clr_bits(USBHS->USBHS_CTRL, USBHS_CTRL_RDERRE))
#define Is_otg_rderr_interrupt_enabled()      (Tst_bits(USBHS->USBHS_CTRL, USBHS_CTRL_RDERRE))
  //! ACKs RDERR interrupt
#define otg_ack_rderr_interrupt()             (USBHS->USBHS_SCR = USBHS_SCR_RDERRIC)
  //! Raises RDERR interrupt
#define otg_raise_rderr_interrupt()           (USBHS->USBHS_SFR = USBHS_SFR_RDERRIS)
  //! Tests if a RDERR occurs
#define Is_otg_rderr_interrupt()              (Tst_bits(USBHS->USBHS_SR, USBHS_SR_RDERRI))
//! @}

//! @}

#ifdef __cplusplus
}
#endif


#endif /* USBHS_OTG_H_INCLUDED */
