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

#include "conf_usb.h"
#include "sysclk.h"
#include "udd.h"
#include "usbhs_otg.h"
#include "usbhs_device.h"
#include <string.h>

#ifndef UDD_NO_SLEEP_MGR
# include "sleep.h"
# include "sleepmgr.h"
#endif

#if !(SAMV71 || SAMV70 || SAME70 || SAMS70)
# error The current USBHS Device Driver supports only SAMV71, SAMV70, SAME70 and SAMS70.
#endif
#ifndef UDD_USB_INT_FUN
# define UDD_USB_INT_FUN USBHS_Handler
#endif

#ifndef UDD_USB_INT_LEVEL
# define UDD_USB_INT_LEVEL 5 // By default USB interrupt have low priority
#endif

#define UDD_EP_USED(ep)      (USB_DEVICE_MAX_EP >= ep)

#if (     (UDD_EP_USED( 1) && Is_udd_endpoint_dma_supported( 1)) \
	||(UDD_EP_USED( 2) && Is_udd_endpoint_dma_supported( 2)) \
	||(UDD_EP_USED( 3) && Is_udd_endpoint_dma_supported( 3)) \
	||(UDD_EP_USED( 4) && Is_udd_endpoint_dma_supported( 4)) \
	||(UDD_EP_USED( 5) && Is_udd_endpoint_dma_supported( 5)) \
	||(UDD_EP_USED( 6) && Is_udd_endpoint_dma_supported( 6)) \
	||(UDD_EP_USED( 7) && Is_udd_endpoint_dma_supported( 7)) \
	||(UDD_EP_USED( 8) && Is_udd_endpoint_dma_supported( 8)) \
	||(UDD_EP_USED( 9) && Is_udd_endpoint_dma_supported( 9)) \
	||(UDD_EP_USED(10) && Is_udd_endpoint_dma_supported(10)) \
	||(UDD_EP_USED(11) && Is_udd_endpoint_dma_supported(11)) \
	||(UDD_EP_USED(12) && Is_udd_endpoint_dma_supported(12)) \
	||(UDD_EP_USED(13) && Is_udd_endpoint_dma_supported(13)) \
	||(UDD_EP_USED(14) && Is_udd_endpoint_dma_supported(14)) \
	||(UDD_EP_USED(15) && Is_udd_endpoint_dma_supported(15)) \
	)
# define UDD_EP_DMA_SUPPORTED
#endif

#if (     (UDD_EP_USED( 1) && !Is_udd_endpoint_dma_supported( 1)) \
	||(UDD_EP_USED( 2) && !Is_udd_endpoint_dma_supported( 2)) \
	||(UDD_EP_USED( 3) && !Is_udd_endpoint_dma_supported( 3)) \
	||(UDD_EP_USED( 4) && !Is_udd_endpoint_dma_supported( 4)) \
	||(UDD_EP_USED( 5) && !Is_udd_endpoint_dma_supported( 5)) \
	||(UDD_EP_USED( 6) && !Is_udd_endpoint_dma_supported( 6)) \
	||(UDD_EP_USED( 7) && !Is_udd_endpoint_dma_supported( 7)) \
	||(UDD_EP_USED( 8) && !Is_udd_endpoint_dma_supported( 8)) \
	||(UDD_EP_USED( 9) && !Is_udd_endpoint_dma_supported( 9)) \
	||(UDD_EP_USED(10) && !Is_udd_endpoint_dma_supported(10)) \
	||(UDD_EP_USED(11) && !Is_udd_endpoint_dma_supported(11)) \
	||(UDD_EP_USED(12) && !Is_udd_endpoint_dma_supported(12)) \
	||(UDD_EP_USED(13) && !Is_udd_endpoint_dma_supported(13)) \
	||(UDD_EP_USED(14) && !Is_udd_endpoint_dma_supported(14)) \
	||(UDD_EP_USED(15) && !Is_udd_endpoint_dma_supported(15)) \
	)
# define UDD_EP_FIFO_SUPPORTED
#endif

// for debug text
//#define dbg_print printf
#define dbg_print(...)

#ifdef UDD_EP_DMA_SUPPORTED
// for DCache
/**
 * \brief Flush content in DCache to physical memory
 * \param addr The memory address to flush
 * \param dsize The size of the memory
 */
static void _dcache_flush(void *addr, uint32_t dsize)
{
#ifdef CONF_BOARD_ENABLE_CACHE_AT_INIT
	int32_t op_size = dsize;
	uint32_t op_addr = (uint32_t) addr;
	int32_t linesize = 32U;                // in Cortex-M7 size of cache line is fixed to 8 words (32 bytes)
	if (op_addr & (linesize - 1)) {
		op_size += op_addr & (linesize - 1);
		op_addr &= ~(linesize - 1);
	}
	__ISB();
	__DSB();

	while (op_size > 0) {
		SCB->DCCMVAC = op_addr;
		op_addr += linesize;
		op_size -= linesize;
	}

	__DSB();
	__ISB();
#endif
}

/**
 * \brief Preparation for unaligned buffer invalidation
 * \param addr The memory address to invalidate
 * \param dsize The size of the memory
 */
static void _dcache_invalidate_prepare(void *addr, uint32_t dsize)
{
#ifdef CONF_BOARD_ENABLE_CACHE_AT_INIT
	int32_t op_size = dsize;
	uint32_t op_addr = (uint32_t) addr;
	int32_t linesize = 32U;                // in Cortex-M7 size of cache line is fixed to 8 words (32 bytes)
	uint32_t addr1 = op_addr;
	uint32_t addr2 = op_addr + op_size;
	if ((addr1 & (linesize - 1)) || (addr2 & (linesize - 1))) {
		addr1 &= ~(linesize - 1);
		addr2 &= ~(linesize - 1);
		__ISB();
		__DSB();
		SCB->DCCIMVAC = addr1;
		SCB->DCCIMVAC = addr2;
		__DSB();
		__ISB();
	}
#endif
}

/**
 * \brief Invalidate DCache of physical memory
 * \param addr The memory address to invalidate
 * \param dsize The size of the memory
 */
static void _dcache_invalidate(void *addr, uint32_t dsize)
{
#ifdef CONF_BOARD_ENABLE_CACHE_AT_INIT
	int32_t op_size = dsize;
	uint32_t op_addr = (uint32_t)addr;
	int32_t linesize = 32U;                // in Cortex-M7 size of cache line is fixed to 8 words (32 bytes)
	if (op_addr & (linesize - 1)) {
		op_size += op_addr & (linesize - 1);
		op_addr &= ~(linesize - 1);
	}
	__ISB();
	__DSB();

	while (op_size > 0) {
		/* D-Cache Invalidate by MVA to PoC */
#if 1	//DC42
		SCB->DCIMVAC= op_addr;
#else
		*(volatile uint32_t *)(0xE000EF5C) = op_addr;
#endif
		op_addr += linesize;
		op_size -= linesize;
	}

	__DSB();
	__ISB();
#endif
}
#endif

/**
 * \ingroup udd_group
 * \defgroup udd_udphs_group USB High-Speed Port for device mode (USBHS)
 *
 * \section USBHS_CONF USBHS Custom configuration
 * The following USBHS driver configuration must be included in the conf_usb.h
 * file of the application.
 *
 * UDD_USB_INT_LEVEL<br>
 * Option to change the interrupt priority (0 to 15) by default 5 (recommended).
 *
 * UDD_USB_INT_FUN<br>
 * Option to fit interrupt function to what defined in exception table.
 *
 * UDD_ISOCHRONOUS_NB_BANK(ep)<br>
 * Feature to reduce or increase isochronous endpoints buffering (1 to 3).
 * Default value 2.
 *
 * UDD_BULK_NB_BANK(ep)<br>
 * Feature to reduce or increase bulk endpoints buffering (1 to 2).
 * Default value 2.
 *
 * UDD_INTERRUPT_NB_BANK(ep)<br>
 * Feature to reduce or increase interrupt endpoints buffering (1 to 2).
 * Default value 1.
 *
 * UDD_NO_SLEEP_MGR<br>
 * Feature to work without sleep manager module.
 * Default not defined.
 * Note that with this feature defined sleep manager must not be used in
 * application.
 *
 * \section Callbacks management
 * The USB driver is fully managed by interrupt and does not request periodique
 * task. Thereby, the USB events use callbacks to transfer the information.
 * The callbacks are declared in static during compilation or in variable during
 * code execution.
 *
 * Static declarations defined in conf_usb.h:
 * - UDC_VBUS_EVENT(bool b_present)<br>
 *   To signal Vbus level change
 * - UDC_SUSPEND_EVENT()<br>
 *   Called when USB bus enter in suspend mode
 * - UDC_RESUME_EVENT()<br>
 *   Called when USB bus is wakeup
 * - UDC_SOF_EVENT()<br>
 *   Called for each received SOF, Note: Each 1ms in HS/FS mode only.
 *
 * Dynamic callbacks, called "endpoint job" , are registered
 * in udd_ep_job_t structure via the following functions:
 * - udd_ep_run()<br>
 *   To call it when a transfer is finish
 * - udd_ep_wait_stall_clear()<br>
 *   To call it when a endpoint halt is disabled
 *
 * \section Power mode management
 * The Sleep modes authorized :
 * - in USB IDLE state, the USBHS needs of USB clock and authorizes up to sleep mode WFI.
 * - in USB SUSPEND state, the USBHS no needs USB clock and authorizes up to sleep mode WAIT.
 * @{
 */

// Check USB Device configuration
#ifndef USB_DEVICE_EP_CTRL_SIZE
# error USB_DEVICE_EP_CTRL_SIZE not defined
#endif
#ifndef USB_DEVICE_MAX_EP
# error USB_DEVICE_MAX_EP not defined
#endif

// Note: USB_DEVICE_MAX_EP does not include control endpoint
#if USB_DEVICE_MAX_EP > (UDD_MAX_PEP_NB-1)
#  error USB_DEVICE_MAX_EP is too high and not supported by this part
#endif

#define UDD_EP_ISO_NBANK_ERROR(ep)            \
	( (UDD_ISOCHRONOUS_NB_BANK(ep) < 1)   \
		|| (UDD_ISOCHRONOUS_NB_BANK(ep) > 3) )
#define UDD_EP_BULK_NBANK_ERROR(ep)           \
	( (UDD_BULK_NB_BANK(ep) < 1) || (UDD_BULK_NB_BANK(ep) > 2) )
#define UDD_EP_INT_NBANK_ERROR(ep)            \
	( (UDD_INTERRUPT_NB_BANK(ep) < 1) || (UDD_INTERRUPT_NB_BANK(ep) > 2) )

#define UDD_EP_ISO_NB_BANK_ERROR(ep)          \
	(UDD_EP_USED(ep) && UDD_EP_ISO_NBANK_ERROR(ep))
#define UDD_EP_BULK_NB_BANK_ERROR(ep)         \
	(UDD_EP_USED(ep) && UDD_EP_ISO_NBANK_ERROR(ep))
#define UDD_EP_INT_NB_BANK_ERROR(ep)          \
	(UDD_EP_USED(ep) && UDD_EP_ISO_NBANK_ERROR(ep))

#define UDD_EP_NB_BANK_ERROR(ep, type)        \
	(ATPASTE3(UDD_EP_, type, _NB_BANK_ERROR(ep)))

#define UDD_ISO_NB_BANK_ERROR \
	(          UDD_EP_NB_BANK_ERROR( 1, ISO) \
		|| UDD_EP_NB_BANK_ERROR( 2, ISO) \
		|| UDD_EP_NB_BANK_ERROR( 3, ISO) \
		|| UDD_EP_NB_BANK_ERROR( 4, ISO) \
		|| UDD_EP_NB_BANK_ERROR( 5, ISO) \
		|| UDD_EP_NB_BANK_ERROR( 6, ISO) \
		|| UDD_EP_NB_BANK_ERROR( 7, ISO) \
		|| UDD_EP_NB_BANK_ERROR( 8, ISO) \
		|| UDD_EP_NB_BANK_ERROR( 9, ISO) \
		|| UDD_EP_NB_BANK_ERROR(10, ISO) \
		|| UDD_EP_NB_BANK_ERROR(11, ISO) \
		|| UDD_EP_NB_BANK_ERROR(12, ISO) \
		|| UDD_EP_NB_BANK_ERROR(13, ISO) \
		|| UDD_EP_NB_BANK_ERROR(14, ISO) \
		|| UDD_EP_NB_BANK_ERROR(15, ISO) )
#define UDD_BULK_NB_BANK_ERROR \
	(          UDD_EP_NB_BANK_ERROR( 1, BULK) \
		|| UDD_EP_NB_BANK_ERROR( 2, BULK) \
		|| UDD_EP_NB_BANK_ERROR( 3, BULK) \
		|| UDD_EP_NB_BANK_ERROR( 4, BULK) \
		|| UDD_EP_NB_BANK_ERROR( 5, BULK) \
		|| UDD_EP_NB_BANK_ERROR( 6, BULK) \
		|| UDD_EP_NB_BANK_ERROR( 7, BULK) \
		|| UDD_EP_NB_BANK_ERROR( 8, BULK) \
		|| UDD_EP_NB_BANK_ERROR( 9, BULK) \
		|| UDD_EP_NB_BANK_ERROR(10, BULK) \
		|| UDD_EP_NB_BANK_ERROR(11, BULK) \
		|| UDD_EP_NB_BANK_ERROR(12, BULK) \
		|| UDD_EP_NB_BANK_ERROR(13, BULK) \
		|| UDD_EP_NB_BANK_ERROR(14, BULK) \
		|| UDD_EP_NB_BANK_ERROR(15, BULK) )
#define UDD_INTERRUPT_NB_BANK_ERROR \
	(          UDD_EP_NB_BANK_ERROR( 1, INT) \
		|| UDD_EP_NB_BANK_ERROR( 2, INT) \
		|| UDD_EP_NB_BANK_ERROR( 3, INT) \
		|| UDD_EP_NB_BANK_ERROR( 4, INT) \
		|| UDD_EP_NB_BANK_ERROR( 5, INT) \
		|| UDD_EP_NB_BANK_ERROR( 6, INT) \
		|| UDD_EP_NB_BANK_ERROR( 7, INT) \
		|| UDD_EP_NB_BANK_ERROR( 8, INT) \
		|| UDD_EP_NB_BANK_ERROR( 9, INT) \
		|| UDD_EP_NB_BANK_ERROR(10, INT) \
		|| UDD_EP_NB_BANK_ERROR(11, INT) \
		|| UDD_EP_NB_BANK_ERROR(12, INT) \
		|| UDD_EP_NB_BANK_ERROR(13, INT) \
		|| UDD_EP_NB_BANK_ERROR(14, INT) \
		|| UDD_EP_NB_BANK_ERROR(15, INT) )

#ifndef UDD_ISOCHRONOUS_NB_BANK
# define UDD_ISOCHRONOUS_NB_BANK(ep) 2
#else
# if UDD_ISO_NB_BANK_ERROR
#  error UDD_ISOCHRONOUS_NB_BANK(ep) must be define within 1 to 3.
# endif
#endif

#ifndef UDD_BULK_NB_BANK
# define UDD_BULK_NB_BANK(ep) 2
#else
# if UDD_BULK_NB_BANK_ERROR
#  error UDD_BULK_NB_BANK must be define with 1 or 2.
# endif
#endif

#ifndef UDD_INTERRUPT_NB_BANK
# define UDD_INTERRUPT_NB_BANK(ep) 1
#else
# if UDD_INTERRUPT_NB_BANK_ERROR
#  error UDD_INTERRUPT_NB_BANK must be define with 1 or 2.
# endif
#endif


/**
 * \name Power management routine.
 */
//@{

#ifndef UDD_NO_SLEEP_MGR

//! Definition of sleep levels
#define USBHS_SLEEP_MODE_USB_SUSPEND  SLEEPMGR_WAIT_FAST
#define USBHS_SLEEP_MODE_USB_IDLE     SLEEPMGR_SLEEP_WFI

//! State of USB line
static bool udd_b_idle;
//! State of sleep manager
static bool udd_b_sleep_initialized = false;


/*! \brief Authorize or not the CPU powerdown mode
 *
 * \param b_idle true to authorize idle mode
 */
static void udd_sleep_mode(bool b_idle)
{
	if (!b_idle && udd_b_idle) {
		dbg_print("_S ");
		sleepmgr_unlock_mode(USBHS_SLEEP_MODE_USB_IDLE);
	}
	if (b_idle && !udd_b_idle) {
		dbg_print("_W ");
		sleepmgr_lock_mode(USBHS_SLEEP_MODE_USB_IDLE);
	}
	udd_b_idle = b_idle;
}
#else

static void udd_sleep_mode(bool b_idle)
{
	(void)b_idle;		//dc42 change to fix Eclipse error
}

#endif // UDD_NO_SLEEP_MGR

//@}

/**
 * \name VBus monitor routine
 */
//@{
#if OTG_VBUS_IO

# if !defined(UDD_NO_SLEEP_MGR) && !defined(USB_VBUS_WKUP)
/* Lock to SLEEPMGR_SLEEP_WFI if VBus not connected */
static bool b_vbus_sleep_lock = false;
/**
 * Lock sleep mode for VBus PIO pin change detection
 */
static void udd_vbus_monitor_sleep_mode(bool b_lock)
{
	if (b_lock && !b_vbus_sleep_lock) {
		b_vbus_sleep_lock = true;
		sleepmgr_lock_mode(SLEEPMGR_SLEEP_WFI);
	}
	if (!b_lock && b_vbus_sleep_lock) {
		b_vbus_sleep_lock = false;
		sleepmgr_unlock_mode(SLEEPMGR_SLEEP_WFI);
	}
}
# else
#  define udd_vbus_monitor_sleep_mode(lock)
# endif

/**
 * USB VBus pin change handler
 */
static void udd_vbus_handler(uint32_t id, uint32_t mask)
{
	/* PIO interrupt status has been cleared, just detect level */
	bool b_vbus_high = Is_otg_vbus_high();
	if (b_vbus_high) {
		udd_vbus_monitor_sleep_mode(false);
		udd_attach();
	} else {
		udd_vbus_monitor_sleep_mode(true);
		udd_detach();
	}
	UDC_VBUS_EVENT(b_vbus_high);
}

#endif
//@}

/**
 * \name Control endpoint low level management routine.
 *
 * This function performs control endpoint mangement.
 * It handle the SETUP/DATA/HANDSHAKE phases of a control transaction.
 */
//@{

//! Global variable to give and record information about setup request management
COMPILER_WORD_ALIGNED udd_ctrl_request_t udd_g_ctrlreq;

//! Bit definitions about endpoint control state machine for udd_ep_control_state
typedef enum {
	UDD_EPCTRL_SETUP                  = 0, //!< Wait a SETUP packet
	UDD_EPCTRL_DATA_OUT               = 1, //!< Wait a OUT data packet
	UDD_EPCTRL_DATA_IN                = 2, //!< Wait a IN data packet
	UDD_EPCTRL_HANDSHAKE_WAIT_IN_ZLP  = 3, //!< Wait a IN ZLP packet
	UDD_EPCTRL_HANDSHAKE_WAIT_OUT_ZLP = 4, //!< Wait a OUT ZLP packet
	UDD_EPCTRL_STALL_REQ              = 5, //!< STALL enabled on IN & OUT packet
} udd_ctrl_ep_state_t;

//! State of the endpoint control management
static udd_ctrl_ep_state_t udd_ep_control_state;

//! Total number of data received/sent during data packet phase with previous payload buffers
static uint16_t udd_ctrl_prev_payload_buf_cnt;

//! Number of data received/sent to/from udd_g_ctrlreq.payload buffer
static uint16_t udd_ctrl_payload_buf_cnt;

/**
 * \brief Reset control endpoint
 *
 * Called after a USB line reset or when UDD is enabled
 */
static void udd_reset_ep_ctrl(void);

/**
 * \brief Reset control endpoint management
 *
 * Called after a USB line reset or at the end of SETUP request (after ZLP)
 */
static void udd_ctrl_init(void);

//! \brief Managed reception of SETUP packet on control endpoint
static void udd_ctrl_setup_received(void);

//! \brief Managed reception of IN packet on control endpoint
static void udd_ctrl_in_sent(void);

//! \brief Managed reception of OUT packet on control endpoint
static void udd_ctrl_out_received(void);

//! \brief Managed underflow event of IN packet on control endpoint
static void udd_ctrl_underflow(void);

//! \brief Managed overflow event of OUT packet on control endpoint
static void udd_ctrl_overflow(void);

//! \brief Managed stall event of IN/OUT packet on control endpoint
static void udd_ctrl_stall_data(void);

//! \brief Send a ZLP IN on control endpoint
static void udd_ctrl_send_zlp_in(void);

//! \brief Send a ZLP OUT on control endpoint
static void udd_ctrl_send_zlp_out(void);

//! \brief Call callback associated to setup request
static void udd_ctrl_endofrequest(void);


/**
 * \brief Main interrupt routine for control endpoint
 *
 * This switchs control endpoint events to correct sub function.
 *
 * \return \c 1 if an event about control endpoint is occured, otherwise \c 0.
 */
static bool udd_ctrl_interrupt(void);

//@}


/**
 * \name Management of bulk/interrupt/isochronous endpoints
 *
 * The UDD manages the data transfer on endpoints:
 * - Start data tranfer on endpoint with USB Device DMA
 * - Send a ZLP packet if requested
 * - Call callback registered to signal end of transfer
 * The transfer abort and stall feature are supported.
 */
//@{
#if (0!=USB_DEVICE_MAX_EP)

//! Structure definition about job registered on an endpoint
typedef struct {
	union {
		//! Callback to call at the end of transfer
		udd_callback_trans_t call_trans;

		//! Callback to call when the endpoint halt is cleared
		udd_callback_halt_cleared_t call_nohalt;
	};
	//! Buffer located in internal RAM to send or fill during job
	uint8_t *buf;
	//! Size of buffer to send or fill
	iram_size_t buf_size;
	//!< Size of data transfered
	iram_size_t buf_cnt;
	//!< Size of data loaded (or prepared for DMA) last time
	iram_size_t buf_load;
	//! A job is registered on this endpoint
	uint8_t busy:1;
	//! A short packet is requested for this job on endpoint IN
	uint8_t b_shortpacket:1;
	//! A stall has been requested but not executed
	uint8_t stall_requested:1;
} udd_ep_job_t;


//! Array to register a job on bulk/interrupt/isochronous endpoint
static udd_ep_job_t udd_ep_job[USB_DEVICE_MAX_EP];

//! \brief Reset all job table
static void udd_ep_job_table_reset(void);

//! \brief Abort all endpoint jobs on going
static void udd_ep_job_table_kill(void);

#ifdef UDD_EP_FIFO_SUPPORTED
	/**
	 * \brief Fill banks and send them
	 *
	 * \param ep endpoint number of job to abort
	 */
	static void udd_ep_in_sent(udd_ep_id_t ep);

	/**
	 * \brief Store received banks
	 *
	 * \param ep endpoint number of job to abort
	 */
	static void udd_ep_out_received(udd_ep_id_t ep);
#endif

/**
 * \brief Abort endpoint job on going
 *
 * \param ep endpoint number of job to abort
 */
static void udd_ep_abort_job(udd_ep_id_t ep);

/**
 * \brief Call the callback associated to the job which is finished
 *
 * \param ptr_job job to complete
 * \param b_abort if true then the job has been aborted
 */
static void udd_ep_finish_job(udd_ep_job_t * ptr_job, bool b_abort, uint8_t ep_num);

#ifdef UDD_EP_DMA_SUPPORTED
	/**
	 * \brief Start the next transfer if necessary or complet the job associated.
	 *
	 * \param ep endpoint number without direction flag
	 */
	static void udd_ep_trans_done(udd_ep_id_t ep);
#endif

/**
 * \brief Main interrupt routine for bulk/interrupt/isochronous endpoints
 *
 * This switchs endpoint events to correct sub function.
 *
 * \return \c 1 if an event about bulk/interrupt/isochronous endpoints has occured, otherwise \c 0.
 */
static bool udd_ep_interrupt(void);

#endif // (0!=USB_DEVICE_MAX_EP)
//@}


//--------------------------------------------------------
//--- INTERNAL ROUTINES TO MANAGED GLOBAL EVENTS

/**
 * \internal
 * \brief Function called by USBHS interrupt to manage USB Device interrupts
 *
 * USB Device interrupt events are splited in three parts:
 * - USB line events (SOF, reset, suspend, resume, wakeup)
 * - control endpoint events (setup reception, end of data transfer, underflow, overflow, stall)
 * - bulk/interrupt/isochronous endpoints events (end of data transfer)
 *
 * Note:
 * Here, the global interrupt mask is not clear when an USB interrupt is enabled
 * because this one can not be occured during the USB ISR (=during INTX is masked).
 * See Technical reference $3.8.3 Masking interrupt requests in peripheral modules.
 */
#ifdef UHD_ENABLE
void udd_interrupt(void);
void udd_interrupt(void)
#else
ISR(UDD_USB_INT_FUN)
#endif
{
#ifndef UDD_NO_SLEEP_MGR
	/* For fast wakeup clocks restore
	 * In WAIT mode, clocks are switched to FASTRC.
	 * After wakeup clocks should be restored, before that ISR should not
	 * be served.
	 */
	if (!pmc_is_wakeup_clocks_restored() && !Is_udd_suspend()) {
		cpu_irq_disable();
		return;
	}
#endif

	if (Is_udd_sof()) {
		udd_ack_sof();
		if (Is_udd_full_speed_mode()) {
			udc_sof_notify();
		}
#ifdef UDC_SOF_EVENT
		UDC_SOF_EVENT();
#endif
		goto udd_interrupt_sof_end;
	}

	if (Is_udd_msof()) {
		udd_ack_msof();
		udc_sof_notify();
		goto udd_interrupt_sof_end;
	}

	dbg_print("%c ", udd_is_high_speed() ? 'H' : 'F');

	if (udd_ctrl_interrupt()) {
		goto udd_interrupt_end; // Interrupt acked by control endpoint managed
	}

#if (0 != USB_DEVICE_MAX_EP)
	if (udd_ep_interrupt()) {
		goto udd_interrupt_end; // Interrupt acked by bulk/interrupt/isochronous endpoint managed
	}
#endif

	// USB bus reset detection
	if (Is_udd_reset()) {
		udd_ack_reset();
		dbg_print("RST ");
		// Abort all jobs on-going
#if (USB_DEVICE_MAX_EP != 0)
		udd_ep_job_table_kill();
#endif
		// Reset USB Device Stack Core
		udc_reset();
		// Reset endpoint control
		udd_reset_ep_ctrl();
		// Reset endpoint control management
		udd_ctrl_init();
		goto udd_interrupt_end;
	}

	if (Is_udd_suspend_interrupt_enabled() && Is_udd_suspend()) {
		otg_unfreeze_clock();
		// The suspend interrupt is automatic acked when a wakeup occur
		udd_disable_suspend_interrupt();
		udd_enable_wake_up_interrupt();
		otg_freeze_clock(); // Mandatory to exit of sleep mode after a wakeup event
		udd_sleep_mode(false);  // Enter in SUSPEND mode
#ifdef UDC_SUSPEND_EVENT
		UDC_SUSPEND_EVENT();
#endif
		goto udd_interrupt_end;
	}

	if (Is_udd_wake_up_interrupt_enabled() && Is_udd_wake_up()) {
		// Ack wakeup interrupt and enable suspend interrupt
		otg_unfreeze_clock();
		// Check USB clock ready after suspend and eventually sleep USB clock
		while (!Is_otg_clock_usable()) {
			if (Is_udd_suspend()) {
				break; // In case of USB state change in HS
			}
		};
		// The wakeup interrupt is automatic acked when a suspend occur
		udd_disable_wake_up_interrupt();
		udd_enable_suspend_interrupt();
		udd_sleep_mode(true); // Enter in IDLE mode
#ifdef UDC_RESUME_EVENT
		UDC_RESUME_EVENT();
#endif
		goto udd_interrupt_end;
	}

udd_interrupt_end:
	dbg_print("\n\r");
udd_interrupt_sof_end:
	return;
}


bool udd_include_vbus_monitoring(void)
{
#if OTG_VBUS_IO
	return true;
#else
	return false;
#endif
}


void udd_enable(void)
{
	irqflags_t flags;

	flags = cpu_irq_save();

#ifdef UHD_ENABLE
	// DUAL ROLE INITIALIZATION
	if (otg_dual_enable()) {
		// The current mode has been started by otg_dual_enable()
		cpu_irq_restore(flags);
		return;
	}
#else
	// SINGLE DEVICE MODE INITIALIZATION
	/* Enable peripheral clock for USBHS */
	pmc_enable_periph_clk(ID_USBHS);

	sysclk_enable_usb();

	// Here, only the device mode is possible, then link USBHS interrupt to UDD interrupt
	NVIC_SetPriority((IRQn_Type) ID_USBHS, UDD_USB_INT_LEVEL);
	NVIC_EnableIRQ((IRQn_Type) ID_USBHS);

	// Always authorize asynchrone USB interrupts to exit of sleep mode
	// For SAM USB wake up device except BACKUP mode
	pmc_set_fast_startup_input(PMC_FSMR_USBAL);
#endif

#if (OTG_ID_IO) && (defined UHD_ENABLE)
	// Check that the device mode is selected by ID pin
	if (!Is_otg_id_device()) {
		cpu_irq_restore(flags);
		return; // Device is not the current mode
	}
#else
	// ID pin not used then force device mode
	USBHS->USBHS_CTRL = USBHS_CTRL_UIMOD_DEVICE;
#endif
	// Enable USB hardware
	otg_enable();

	// Set the USB speed requested by configuration file
#ifdef USB_DEVICE_LOW_SPEED
	udd_low_speed_enable();
#else
	udd_low_speed_disable();
#ifdef USB_DEVICE_HS_SUPPORT
	udd_high_speed_enable();
#else
	udd_high_speed_disable();
#endif
#endif // USB_DEVICE_LOW_SPEED

	otg_unfreeze_clock();
	// Check USB clock
	while (!Is_otg_clock_usable());

	// Reset internal variables
#if (0!=USB_DEVICE_MAX_EP)
	udd_ep_job_table_reset();
#endif

	otg_freeze_clock();

#ifndef UDD_NO_SLEEP_MGR
	if (!udd_b_sleep_initialized) {
		udd_b_sleep_initialized = true;
		// Initialize the sleep mode authorized for the USB suspend mode
		udd_b_idle = false;
		sleepmgr_lock_mode(USBHS_SLEEP_MODE_USB_SUSPEND);
	} else {
		udd_sleep_mode(false); // Enter idle mode
	}
#endif

#if OTG_VBUS_IO
	/* Initialize VBus monitor */
	otg_vbus_init(udd_vbus_handler);
	udd_vbus_monitor_sleep_mode(true);
	/* Force VBus interrupt when VBus is always high
	 * This is possible due to a short timing between a Host mode stop/start.
	 */
	if (Is_otg_vbus_high()) {
		udd_vbus_handler(USB_VBUS_PIO_ID, USB_VBUS_PIO_MASK);
	}
#else
	udd_attach();
#endif

	cpu_irq_restore(flags);
}


void udd_disable(void)
{
	irqflags_t flags;

#ifdef UHD_ENABLE
# if OTG_ID_IO
	if (Is_otg_id_host()) {
		// Freeze clock to switch mode
		otg_freeze_clock();
		udd_detach();
		otg_disable();
		return; // Host mode running, ignore UDD disable
	}
# else
	if (Is_otg_host_mode_forced()) {
		return; // Host mode running, ignore UDD disable
	}
#endif
#endif

	flags = cpu_irq_save();
	otg_unfreeze_clock();
	udd_detach();
#ifndef UDD_NO_SLEEP_MGR
	if (udd_b_sleep_initialized) {
		udd_b_sleep_initialized = false;
		sleepmgr_unlock_mode(USBHS_SLEEP_MODE_USB_SUSPEND);
	}
#endif

#ifndef UHD_ENABLE
	otg_disable();
	sysclk_disable_usb();
	pmc_disable_periph_clk(ID_USBHS);
	// Else the USB clock disable is done by UHC which manage USB dual role
#endif
	cpu_irq_restore(flags);
}


void udd_attach(void)
{
	irqflags_t flags;
	flags = cpu_irq_save();

	// At startup the USB bus state is unknown,
	// therefore the state is considered IDLE to not miss any USB event
	udd_sleep_mode(true);
	otg_unfreeze_clock();

	// This section of clock check can be improved with a chek of
	// USB clock source via sysclk()
	// Check USB clock because the source can be a PLL
	while (!Is_otg_clock_usable());

	// Authorize attach if Vbus is present
	udd_attach_device();

	// Enable USB line events
	udd_enable_reset_interrupt();
	udd_enable_suspend_interrupt();
	udd_enable_wake_up_interrupt();
	udd_enable_sof_interrupt();
#ifdef USB_DEVICE_HS_SUPPORT
	udd_enable_msof_interrupt();
#endif
	// Reset following interupts flag
	udd_ack_reset();
	udd_ack_sof();
	udd_ack_msof();

	// The first suspend interrupt must be forced
	// The first suspend interrupt is not detected else raise it
	udd_raise_suspend();

	udd_ack_wake_up();
	otg_freeze_clock();
	cpu_irq_restore(flags);
}


void udd_detach(void)
{
	otg_unfreeze_clock();

	// Detach device from the bus
	udd_detach_device();
	otg_freeze_clock();
	udd_sleep_mode(false);
}


bool udd_is_high_speed(void)
{
#ifdef USB_DEVICE_HS_SUPPORT
	return !Is_udd_full_speed_mode();
#else
	return false;
#endif
}


void udd_set_address(uint8_t address)
{
	udd_disable_address();
	udd_configure_address(address);
	udd_enable_address();
}


uint8_t udd_getaddress(void)
{
	return udd_get_configured_address();
}


uint16_t udd_get_frame_number(void)
{
	return udd_frame_number();
}

uint16_t udd_get_micro_frame_number(void)
{
	return udd_micro_frame_number();
}

void udd_send_remotewakeup(void)
{
#ifndef UDD_NO_SLEEP_MGR
	if (!udd_b_idle)
#endif
	{
		udd_sleep_mode(true); // Enter in IDLE mode
		otg_unfreeze_clock();
		udd_initiate_remote_wake_up();
	}
}


void udd_set_setup_payload(uint8_t *payload, uint16_t payload_size)
{
	udd_g_ctrlreq.payload = payload;
	udd_g_ctrlreq.payload_size = payload_size;
}


#if (0 != USB_DEVICE_MAX_EP)
bool udd_ep_alloc(udd_ep_id_t ep, uint8_t bmAttributes,
		uint16_t MaxEndpointSize)
{
	bool b_dir_in;
	uint16_t ep_allocated;
	uint8_t nb_bank, bank, i;

	b_dir_in = ep & USB_EP_DIR_IN;
	ep = ep & USB_EP_ADDR_MASK;

	if (ep > USB_DEVICE_MAX_EP) {
		return false;
	}
	if (Is_udd_endpoint_enabled(ep)) {
		return false;
	}
	dbg_print("alloc(%x, %d) ", ep, MaxEndpointSize);

	// Bank choise
	switch (bmAttributes & USB_EP_TYPE_MASK) {
	case USB_EP_TYPE_ISOCHRONOUS:
		nb_bank = UDD_ISOCHRONOUS_NB_BANK(ep);
		break;
	case USB_EP_TYPE_INTERRUPT:
		nb_bank = UDD_INTERRUPT_NB_BANK(ep);
		break;
	case USB_EP_TYPE_BULK:
		nb_bank = UDD_BULK_NB_BANK(ep);
		break;
	default:
		Assert(false);
		return false;
	}
	switch (nb_bank) {
	case 1:
		bank = USBHS_DEVEPTCFG_EPBK_1_BANK >>
				USBHS_DEVEPTCFG_EPBK_Pos;
		break;
	case 2:
		bank = USBHS_DEVEPTCFG_EPBK_2_BANK >>
				USBHS_DEVEPTCFG_EPBK_Pos;
		break;
	case 3:
		bank = USBHS_DEVEPTCFG_EPBK_3_BANK >>
				USBHS_DEVEPTCFG_EPBK_Pos;
		break;
	default:
		Assert(false);
		return false;
	}

	// Check if endpoint size is 8,16,32,64,128,256,512 or 1023
	Assert(MaxEndpointSize < 1024);
	Assert((MaxEndpointSize == 1023)
		|| !(MaxEndpointSize & (MaxEndpointSize - 1)));
	Assert(MaxEndpointSize >= 8);

	// Set configuration of new endpoint
	udd_configure_endpoint(ep, bmAttributes, (b_dir_in ? 1 : 0),
			MaxEndpointSize, bank);
	ep_allocated = 1 << ep;

	// Unalloc endpoints superior
	for (i = USB_DEVICE_MAX_EP; i > ep; i--) {
		if (Is_udd_endpoint_enabled(i)) {
			ep_allocated |= 1 << i;
			udd_disable_endpoint(i);
			udd_unallocate_memory(i);
		}
	}

	// Realloc/Enable endpoints
	for (i = ep; i <= USB_DEVICE_MAX_EP; i++) {
		if (ep_allocated & (1 << i)) {
			udd_ep_job_t *ptr_job = &udd_ep_job[i - 1];
			bool b_restart = ptr_job->busy;
			// Restart running job because
			// memory window slides up and its data is lost
			ptr_job->busy = false;
			// Re-allocate memory
			udd_allocate_memory(i);
			udd_enable_endpoint(i);
			if (!Is_udd_endpoint_configured(i)) {
				dbg_print("ErrRealloc%d ", i);
				if (NULL == ptr_job->call_trans) {
					return false;
				}
				if (Is_udd_endpoint_in(i)) {
					i |= USB_EP_DIR_IN;
				}
				ptr_job->call_trans(UDD_EP_TRANSFER_ABORT,
						ptr_job->buf_cnt, i);
				return false;
			}
			udd_enable_endpoint_bank_autoswitch(i);
			if (b_restart) {
				// Re-run the job remaining part
#  ifdef UDD_EP_FIFO_SUPPORTED
				if (!Is_udd_endpoint_dma_supported(i)
					&& !Is_udd_endpoint_in(i)) {
					ptr_job->buf_cnt -= ptr_job->buf_load;
				}
#  else
				ptr_job->buf_cnt -= ptr_job->buf_load;
#  endif
				b_restart = udd_ep_run(Is_udd_endpoint_in(i) ?
							(i | USB_EP_DIR_IN) : i,
						ptr_job->b_shortpacket,
						&ptr_job->buf[ptr_job->buf_cnt],
						ptr_job->buf_size
							- ptr_job->buf_cnt,
						ptr_job->call_trans);
				if (!b_restart) {
					dbg_print("ErrReRun%d ", i);
					return false;
				}
			}
		}
	}
	return true;
}


void udd_ep_free(udd_ep_id_t ep)
{
	uint8_t ep_index = ep & USB_EP_ADDR_MASK;
	if (USB_DEVICE_MAX_EP < ep_index) {
		return;
	}
	udd_disable_endpoint(ep_index);
	udd_unallocate_memory(ep_index);
	udd_ep_abort_job(ep);
	udd_ep_job[ep_index - 1].stall_requested = false;
}


bool udd_ep_is_halted(udd_ep_id_t ep)
{
	uint8_t ep_index = ep & USB_EP_ADDR_MASK;
	return Is_udd_endpoint_stall_requested(ep_index);
}


bool udd_ep_set_halt(udd_ep_id_t ep)
{
	uint8_t ep_index = ep & USB_EP_ADDR_MASK;
	udd_ep_job_t *ptr_job = &udd_ep_job[ep_index - 1];
	irqflags_t flags;

	if (USB_DEVICE_MAX_EP < ep_index) {
		return false;
	}

	if (Is_udd_endpoint_stall_requested(ep_index) // Endpoint stalled
			|| ptr_job->stall_requested) { // Endpoint stall is requested
		return true; // Already STALL
	}

	if (ptr_job->busy == true) {
		return false; // Job on going, stall impossible
	}

	flags = cpu_irq_save();
	if ((ep & USB_EP_DIR_IN) && (0 != udd_nb_busy_bank(ep_index))) {
		// Delay the stall after the end of IN transfer on USB line
		ptr_job->stall_requested = true;
#ifdef UDD_EP_FIFO_SUPPORTED
		udd_disable_in_send_interrupt(ep_index);
		udd_enable_endpoint_bank_autoswitch(ep_index);
#endif
		udd_enable_bank_interrupt(ep_index);
		udd_enable_endpoint_interrupt(ep_index);
		cpu_irq_restore(flags);
		return true;
	}
	// Stall endpoint immediately
	udd_disable_endpoint_bank_autoswitch(ep_index);
	udd_ack_stall(ep_index);
	udd_enable_stall_handshake(ep_index);
	cpu_irq_restore(flags);
	return true;
}


bool udd_ep_clear_halt(udd_ep_id_t ep)
{
	uint8_t ep_index = ep & USB_EP_ADDR_MASK;
	udd_ep_job_t *ptr_job = &udd_ep_job[ep_index - 1];
	bool b_stall_cleared = false;

	if (USB_DEVICE_MAX_EP < ep_index)
		return false;

	if (ptr_job->stall_requested) {
		// Endpoint stall has been requested but not done
		// Remove stall request
		ptr_job->stall_requested = false;
		udd_disable_bank_interrupt(ep_index);
		udd_disable_endpoint_interrupt(ep_index);
		b_stall_cleared = true;
	}
	if (Is_udd_endpoint_stall_requested(ep_index)) {
		if (Is_udd_stall(ep_index)) {
			udd_ack_stall(ep_index);
			// A packet has been stalled
			// then reset datatoggle
			udd_reset_data_toggle(ep_index);
		}
		// Disable stall
		udd_disable_stall_handshake(ep_index);
		udd_enable_endpoint_bank_autoswitch(ep_index);
		b_stall_cleared = true;
	}
	if (b_stall_cleared) {
		// If a job is register on clear halt action
		// then execute callback
		if (ptr_job->busy == true) {
			ptr_job->busy = false;
			ptr_job->call_nohalt();
		}
	}
	return true;
}


bool udd_ep_run(udd_ep_id_t ep, bool b_shortpacket,
		uint8_t * buf, iram_size_t buf_size,
		udd_callback_trans_t callback)
{
	bool b_dir_in = Is_udd_endpoint_in(ep & USB_EP_ADDR_MASK);
	udd_ep_job_t *ptr_job;
	irqflags_t flags;

	ep &= USB_EP_ADDR_MASK;
	if (USB_DEVICE_MAX_EP < ep) {
		return false;
	}

	// Get job about endpoint
	ptr_job = &udd_ep_job[ep - 1];

	if ((!Is_udd_endpoint_enabled(ep))
			|| Is_udd_endpoint_stall_requested(ep)
			|| ptr_job->stall_requested) {
		return false; // Endpoint is halted
	}

	flags = cpu_irq_save();
	if (ptr_job->busy == true) {
		cpu_irq_restore(flags);
		return false; // Job already on going
	}
	ptr_job->busy = true;
	cpu_irq_restore(flags);

	// No job running. Let's setup a new one.
	ptr_job->buf = buf;
	ptr_job->buf_size = buf_size;
	ptr_job->buf_cnt = 0;
	ptr_job->buf_load = 0;
	ptr_job->call_trans = callback;
	ptr_job->b_shortpacket = b_shortpacket || (buf_size == 0);

#ifdef UDD_EP_FIFO_SUPPORTED
	// No DMA support
	if (!Is_udd_endpoint_dma_supported(ep)) {
		dbg_print("ex%x.%c%d\n\r", ep, b_dir_in ? 'i':'o', buf_size);
		flags = cpu_irq_save();
		udd_enable_endpoint_interrupt(ep);
		if (b_dir_in) {
			udd_disable_endpoint_bank_autoswitch(ep);
			udd_enable_in_send_interrupt(ep);
		} else {
			udd_disable_endpoint_bank_autoswitch(ep);
			udd_enable_out_received_interrupt(ep);
		}
		cpu_irq_restore(flags);
		return true;
	}
#endif // UDD_EP_FIFO_SUPPORTED

#ifdef UDD_EP_DMA_SUPPORTED
	// Request first DMA transfer
	dbg_print("(exDMA%x) ", ep);
	if (buf && buf_size) {
		if (!b_dir_in) {
			_dcache_invalidate_prepare(buf, buf_size);
		} else {
			_dcache_flush(buf, buf_size);
		}
	}
	udd_ep_trans_done(ep);
	return true;
#endif
}


void udd_ep_abort(udd_ep_id_t ep)
{
	uint8_t ep_index = ep & USB_EP_ADDR_MASK;

#ifdef UDD_EP_FIFO_SUPPORTED
	if (!Is_udd_endpoint_dma_supported(ep_index)) {
		// Disable interrupts
		udd_disable_endpoint_interrupt(ep_index);
		udd_disable_out_received_interrupt(ep_index);
		udd_disable_in_send_interrupt(ep_index);
	} else
#endif
	{
		// Stop DMA transfer
		udd_disable_endpoint_dma_interrupt(ep_index);
		udd_endpoint_dma_set_control(ep_index, 0);
	}
	udd_disable_endpoint_interrupt(ep_index);
	// Kill IN banks
	__DSB();
	__ISB();
	if (ep & USB_EP_DIR_IN) {
		while(udd_nb_busy_bank(ep_index)) {
			udd_kill_last_in_bank(ep_index);
			while(Is_udd_kill_last(ep_index));
		}
	}
	udd_ep_abort_job(ep);
}


bool udd_ep_wait_stall_clear(udd_ep_id_t ep,
		udd_callback_halt_cleared_t callback)
{
	udd_ep_job_t *ptr_job;

	ep &= USB_EP_ADDR_MASK;
	if (USB_DEVICE_MAX_EP < ep) {
		return false;
	}

	ptr_job = &udd_ep_job[ep - 1];

	if (!Is_udd_endpoint_enabled(ep)) {
		return false; // Endpoint not enabled
	}

	// Wait clear halt endpoint
	if (ptr_job->busy == true) {
		return false; // Job already on going
	}

	if (Is_udd_endpoint_stall_requested(ep)
			|| ptr_job->stall_requested) {
		// Endpoint halted then registes the callback
		ptr_job->busy = true;
		ptr_job->call_nohalt = callback;
	} else {
		// endpoint not halted then call directly callback
		callback();
	}
	return true;
}
#endif // (0 != USB_DEVICE_MAX_EP)


#ifdef USB_DEVICE_HS_SUPPORT

void udd_test_mode_j(void)
{
	udd_enable_hs_test_mode();
	udd_enable_hs_test_mode_j();
}


void udd_test_mode_k(void)
{
	udd_enable_hs_test_mode();
	udd_enable_hs_test_mode_k();
}


void udd_test_mode_se0_nak(void)
{
	udd_enable_hs_test_mode();
}


void udd_test_mode_packet(void)
{
	uint8_t i;
	uint8_t *ptr_dest;
	const uint8_t *ptr_src;

	const uint8_t test_packet[] = {
		// 00000000 * 9
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		// 01010101 * 8
		0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
		// 01110111 * 8
		0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE,
		// 0, {111111S * 15}, 111111
		0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
				0xFF, 0xFF,
		// S, 111111S, {0111111S * 7}
		0x7F, 0xBF, 0xDF, 0xEF, 0xF7, 0xFB, 0xFD,
		// 00111111, {S0111111 * 9}, S0
		0xFC, 0x7E, 0xBF, 0xDF, 0xEF, 0xF7, 0xFB, 0xFD, 0x7E
	};

	// Reconfigure control endpoint to bulk IN endpoint
	udd_disable_endpoint(0);
	udd_configure_endpoint(0, USB_EP_TYPE_BULK, 1,
			64, USBHS_DEVEPTCFG_EPBK_1_BANK);
	udd_allocate_memory(0);
	udd_enable_endpoint(0);

	udd_enable_hs_test_mode();
	udd_enable_hs_test_mode_packet();

	// Send packet on endpoint 0
	ptr_dest = (uint8_t *) & udd_get_endpoint_fifo_access(0, 8);
	ptr_src = test_packet;

	for (i = 0; i < sizeof(test_packet); i++) {
		*ptr_dest++ = *ptr_src++;
	}
	udd_ack_fifocon(0);
}
#endif // USB_DEVICE_HS_SUPPORT



//--------------------------------------------------------
//--- INTERNAL ROUTINES TO MANAGED THE CONTROL ENDPOINT

static void udd_reset_ep_ctrl(void)
{
	irqflags_t flags;

	// Reset USB address to 0
	udd_configure_address(0);
	udd_enable_address();

	// Alloc and configure control endpoint
	udd_configure_endpoint(0,
		USB_EP_TYPE_CONTROL,
		0,
		USB_DEVICE_EP_CTRL_SIZE,
		USBHS_DEVEPTCFG_EPBK_1_BANK);

	udd_allocate_memory(0);
	udd_enable_endpoint(0);
	flags = cpu_irq_save();
	udd_enable_setup_received_interrupt(0);
	udd_enable_out_received_interrupt(0);
	udd_enable_endpoint_interrupt(0);
	cpu_irq_restore(flags);
}

static void udd_ctrl_init(void)
{
	irqflags_t flags;
	flags = cpu_irq_save();

	// In case of abort of IN Data Phase:
	// No need to abort IN transfer (rise TXINI),
	// because it is automatically done by hardware when a Setup packet is received.
	// But the interrupt must be disabled to don't generate interrupt TXINI
	// after SETUP reception.
	udd_disable_in_send_interrupt(0);
	cpu_irq_restore(flags);

	// In case of OUT ZLP event is no processed before Setup event occurs
	udd_ack_out_received(0);

	udd_g_ctrlreq.callback = NULL;
	udd_g_ctrlreq.over_under_run = NULL;
	udd_g_ctrlreq.payload_size = 0;
	udd_ep_control_state = UDD_EPCTRL_SETUP;
}


static void udd_ctrl_setup_received(void)
{
	irqflags_t flags;
	uint8_t i;

	if (UDD_EPCTRL_SETUP != udd_ep_control_state) {
		// May be a hidden DATA or ZLP phase or protocol abort
		udd_ctrl_endofrequest();

		// Reinitializes control endpoint management
		udd_ctrl_init();
	}
	// Fill setup request structure
	if (8 != udd_byte_count(0)) {
		udd_ctrl_stall_data();
		udd_ack_setup_received(0);
		return; // Error data number doesn't correspond to SETUP packet
	}

	uint16_t nb_data = udd_byte_count(0);
	volatile uint8_t *ptr = (uint8_t *) & udd_get_endpoint_fifo_access(0,8);
	for (i = 0; i < nb_data; i++) {
		((uint8_t*) &udd_g_ctrlreq.req)[i] = *ptr++;
	}
	// Manage LSB/MSB to fit with CPU usage
	udd_g_ctrlreq.req.wValue = le16_to_cpu(udd_g_ctrlreq.req.wValue);
	udd_g_ctrlreq.req.wIndex = le16_to_cpu(udd_g_ctrlreq.req.wIndex);
	udd_g_ctrlreq.req.wLength = le16_to_cpu(udd_g_ctrlreq.req.wLength);

	// Decode setup request
	if (udc_process_setup() == false) {
		// Setup request unknow then stall it
		udd_ctrl_stall_data();
		udd_ack_setup_received(0);
		return;
	}
	udd_ack_setup_received(0);

	if (Udd_setup_is_in()) {
		// IN data phase requested
		udd_ctrl_prev_payload_buf_cnt = 0;
		udd_ctrl_payload_buf_cnt = 0;
		udd_ep_control_state = UDD_EPCTRL_DATA_IN;
		udd_ctrl_in_sent(); // Send first data transfer
	} else {
		if (0 == udd_g_ctrlreq.req.wLength) {
			// No data phase requested
			// Send IN ZLP to ACK setup request
			udd_ctrl_send_zlp_in();
			return;
		}
		// OUT data phase requested
		udd_ctrl_prev_payload_buf_cnt = 0;
		udd_ctrl_payload_buf_cnt = 0;
		udd_ep_control_state = UDD_EPCTRL_DATA_OUT;
		// To detect a protocol error, enable nak interrupt on data IN phase
		udd_ack_nak_in(0);
		flags = cpu_irq_save();
		udd_enable_nak_in_interrupt(0);
		cpu_irq_restore(flags);
	}
}


static void udd_ctrl_in_sent(void)
{
	static bool b_shortpacket = false;
	uint16_t nb_remain;
	uint8_t i;
	volatile uint8_t *ptr_dest;
	volatile uint8_t *ptr_src;
	irqflags_t flags;

	flags = cpu_irq_save();
	udd_disable_in_send_interrupt(0);
	cpu_irq_restore(flags);

	if (UDD_EPCTRL_HANDSHAKE_WAIT_IN_ZLP == udd_ep_control_state) {
		// ZLP on IN is sent, then valid end of setup request
		udd_ctrl_endofrequest();
		// Reinitializes control endpoint management
		udd_ctrl_init();
		return;
	}
	Assert(udd_ep_control_state == UDD_EPCTRL_DATA_IN);

	nb_remain = udd_g_ctrlreq.payload_size - udd_ctrl_payload_buf_cnt;
	if (0 == nb_remain) {
		// All content of current buffer payload are sent
		// Update number of total data sending by previous playlaod buffer
		udd_ctrl_prev_payload_buf_cnt += udd_ctrl_payload_buf_cnt;
		if ((udd_g_ctrlreq.req.wLength == udd_ctrl_prev_payload_buf_cnt)
					|| b_shortpacket) {
			// All data requested are transfered or a short packet has been sent
			// then it is the end of data phase.
			// Generate an OUT ZLP for handshake phase.
			udd_ctrl_send_zlp_out();
			return;
		}
		// Need of new buffer because the data phase is not complete
		if ((!udd_g_ctrlreq.over_under_run)
				|| (!udd_g_ctrlreq.over_under_run())) {
			// Underrun then send zlp on IN
			// Here nb_remain=0 and allows to send a IN ZLP
		} else {
			// A new payload buffer is given
			udd_ctrl_payload_buf_cnt = 0;
			nb_remain = udd_g_ctrlreq.payload_size;
		}
	}
	// Continue transfer and send next data
	if (nb_remain >= USB_DEVICE_EP_CTRL_SIZE) {
		nb_remain = USB_DEVICE_EP_CTRL_SIZE;
		b_shortpacket = false;
	} else {
		b_shortpacket = true;
	}
	// Fill buffer of endpoint control
	ptr_dest = (uint8_t *) & udd_get_endpoint_fifo_access(0, 8);
	ptr_src = udd_g_ctrlreq.payload + udd_ctrl_payload_buf_cnt;
	// Critical section
	// Only in case of DATA IN phase abort without USB Reset signal after.
	// The IN data don't must be written in endpoint 0 DPRAM during
	// a next setup reception in same endpoint 0 DPRAM.
	// Thereby, an OUT ZLP reception must check before IN data write
	// and if no OUT ZLP is recevied the data must be written quickly (800us)
	// before an eventually ZLP OUT and SETUP reception
	flags = cpu_irq_save();
	if (Is_udd_out_received(0)) {
		// IN DATA phase aborted by OUT ZLP
		cpu_irq_restore(flags);
		udd_ep_control_state = UDD_EPCTRL_HANDSHAKE_WAIT_OUT_ZLP;
		return; // Exit of IN DATA phase
	}
	// Write quickly the IN data
	for (i = 0; i < nb_remain; i++) {
		*ptr_dest++ = *ptr_src++;
	}
	udd_ctrl_payload_buf_cnt += nb_remain;

	// Validate and send the data available in the control endpoint buffer
	__DSB();
	__ISB();
	udd_ack_in_send(0);
	udd_enable_in_send_interrupt(0);
	// In case of abort of DATA IN phase, no need to enable nak OUT interrupt
	// because OUT endpoint is already free and ZLP OUT accepted.
	cpu_irq_restore(flags);
}


static void udd_ctrl_out_received(void)
{
	irqflags_t flags;
	uint8_t i;
	uint16_t nb_data;

	if (UDD_EPCTRL_DATA_OUT != udd_ep_control_state) {
		if ((UDD_EPCTRL_DATA_IN == udd_ep_control_state)
				|| (UDD_EPCTRL_HANDSHAKE_WAIT_OUT_ZLP ==
						udd_ep_control_state)) {
			// End of SETUP request:
			// - Data IN Phase aborted,
			// - or last Data IN Phase hidden by ZLP OUT sending quiclky,
			// - or ZLP OUT received normaly.
			udd_ctrl_endofrequest();
		} else {
			// Protocol error during SETUP request
			udd_ctrl_stall_data();
		}
		// Reinitializes control endpoint management
		udd_ctrl_init();
		return;
	}
	// Read data received during OUT phase
	nb_data = udd_byte_count(0);
	if (udd_g_ctrlreq.payload_size < (udd_ctrl_payload_buf_cnt + nb_data)) {
		// Payload buffer too small
		nb_data = udd_g_ctrlreq.payload_size - udd_ctrl_payload_buf_cnt;
	}
	volatile uint8_t *ptr_src = (uint8_t *) & udd_get_endpoint_fifo_access(0, 8);
	volatile uint8_t *ptr_dest = udd_g_ctrlreq.payload + udd_ctrl_payload_buf_cnt;
	for (i = 0; i < nb_data; i++) {
		*ptr_dest++ = *ptr_src++;
	}
	udd_ctrl_payload_buf_cnt += nb_data;

	if ((USB_DEVICE_EP_CTRL_SIZE != nb_data)
			|| (udd_g_ctrlreq.req.wLength <=
					(udd_ctrl_prev_payload_buf_cnt +
							udd_ctrl_payload_buf_cnt))) {
		// End of reception because it is a short packet
		// Before send ZLP, call intermediat calback
		// in case of data receiv generate a stall
		udd_g_ctrlreq.payload_size = udd_ctrl_payload_buf_cnt;
		if (NULL != udd_g_ctrlreq.over_under_run) {
			if (!udd_g_ctrlreq.over_under_run()) {
				// Stall ZLP
				udd_ctrl_stall_data();
				// Ack reception of OUT to replace NAK by a STALL
				udd_ack_out_received(0);
				return;
			}
		}
		// Send IN ZLP to ACK setup request
		udd_ack_out_received(0);
		udd_ctrl_send_zlp_in();
		return;
	}

	if (udd_g_ctrlreq.payload_size == udd_ctrl_payload_buf_cnt) {
		// Overrun then request a new payload buffer
		if (!udd_g_ctrlreq.over_under_run) {
			// No callback availabled to request a new payload buffer
			udd_ctrl_stall_data();
			// Ack reception of OUT to replace NAK by a STALL
			udd_ack_out_received(0);
			return;
		}
		if (!udd_g_ctrlreq.over_under_run()) {
			// No new payload buffer delivered
			udd_ctrl_stall_data();
			// Ack reception of OUT to replace NAK by a STALL
			udd_ack_out_received(0);
			return;
		}
		// New payload buffer available
		// Update number of total data received
		udd_ctrl_prev_payload_buf_cnt += udd_ctrl_payload_buf_cnt;
		// Reinit reception on payload buffer
		udd_ctrl_payload_buf_cnt = 0;
	}
	// Free buffer of control endpoint to authorize next reception
	udd_ack_out_received(0);
	// To detect a protocol error, enable nak interrupt on data IN phase
	udd_ack_nak_in(0);
	flags = cpu_irq_save();
	udd_enable_nak_in_interrupt(0);
	cpu_irq_restore(flags);
}


static void udd_ctrl_underflow(void)
{
	if (Is_udd_out_received(0))
		return; // Underflow ignored if OUT data is received

	if (UDD_EPCTRL_DATA_OUT == udd_ep_control_state) {
		// Host want to stop OUT transaction
		// then stop to wait OUT data phase and wait IN ZLP handshake
		udd_ctrl_send_zlp_in();
	} else if (UDD_EPCTRL_HANDSHAKE_WAIT_OUT_ZLP == udd_ep_control_state) {
		// A OUT handshake is waiting by device,
		// but host want extra IN data then stall extra IN data
		udd_enable_stall_handshake(0);
	}
}


static void udd_ctrl_overflow(void)
{
	if (Is_udd_in_send(0))
		return; // Overflow ignored if IN data is received

	// The case of UDD_EPCTRL_DATA_IN is not managed
	// because the OUT endpoint is already free and OUT ZLP accepted

	if (UDD_EPCTRL_HANDSHAKE_WAIT_IN_ZLP == udd_ep_control_state) {
		// A IN handshake is waiting by device,
		// but host want extra OUT data then stall extra OUT data
		udd_enable_stall_handshake(0);
	}
}


static void udd_ctrl_stall_data(void)
{
	// Stall all packets on IN & OUT control endpoint
	udd_ep_control_state = UDD_EPCTRL_STALL_REQ;
	udd_enable_stall_handshake(0);
}


static void udd_ctrl_send_zlp_in(void)
{
	irqflags_t flags;

	udd_ep_control_state = UDD_EPCTRL_HANDSHAKE_WAIT_IN_ZLP;

	// Validate and send empty IN packet on control endpoint
	flags = cpu_irq_save();
	// Send ZLP on IN endpoint
	udd_ack_in_send(0);
	udd_enable_in_send_interrupt(0);
	// To detect a protocol error, enable nak interrupt on data OUT phase
	udd_ack_nak_out(0);
	udd_enable_nak_out_interrupt(0);
	cpu_irq_restore(flags);
}


static void udd_ctrl_send_zlp_out(void)
{
	irqflags_t flags;

	udd_ep_control_state = UDD_EPCTRL_HANDSHAKE_WAIT_OUT_ZLP;
	// No action is necessary to accept OUT ZLP
	// because the buffer of control endpoint is already free

	// To detect a protocol error, enable nak interrupt on data IN phase
	flags = cpu_irq_save();
	udd_ack_nak_in(0);
	udd_enable_nak_in_interrupt(0);
	cpu_irq_restore(flags);
}


static void udd_ctrl_endofrequest(void)
{
	// If a callback is registered then call it
	if (udd_g_ctrlreq.callback) {
		udd_g_ctrlreq.callback();
	}
}


static bool udd_ctrl_interrupt(void)
{

	if (!Is_udd_endpoint_interrupt(0)) {
		return false; // No interrupt events on control endpoint
	}

	dbg_print("0: ");

	// By default disable overflow and underflow interrupt
	udd_disable_nak_in_interrupt(0);
	udd_disable_nak_out_interrupt(0);

	// Search event on control endpoint
	if (Is_udd_setup_received(0)) {
		dbg_print("stup ");
		// SETUP packet received
		udd_ctrl_setup_received();
		return true;
	}
	if (Is_udd_in_send(0) && Is_udd_in_send_interrupt_enabled(0)) {
		dbg_print("in ");
		// IN packet sent
		udd_ctrl_in_sent();
		return true;
	}
	if (Is_udd_out_received(0)) {
		dbg_print("out ");
		// OUT packet received
		udd_ctrl_out_received();
		return true;
	}
	if (Is_udd_nak_out(0)) {
		dbg_print("nako ");
		// Overflow on OUT packet
		udd_ack_nak_out(0);
		udd_ctrl_overflow();
		return true;
	}
	if (Is_udd_nak_in(0)) {
		dbg_print("naki ");
		// Underflow on IN packet
		udd_ack_nak_in(0);
		udd_ctrl_underflow();
		return true;
	}
	dbg_print("n%x ", USBHS_ARRAY(USBHS_DEVEPTISR[0], 0));
	return false;
}


//--------------------------------------------------------
//--- INTERNAL ROUTINES TO MANAGED THE BULK/INTERRUPT/ISOCHRONOUS ENDPOINTS

#if (0 != USB_DEVICE_MAX_EP)

static void udd_ep_job_table_reset(void)
{
	uint8_t i;
	for (i = 0; i < USB_DEVICE_MAX_EP; i++) {
		udd_ep_job[i].busy = false;
		udd_ep_job[i].stall_requested = false;
	}
}


static void udd_ep_job_table_kill(void)
{
	uint8_t i;

	// For each endpoint, kill job
	for (i = 0; i < USB_DEVICE_MAX_EP; i++) {
		udd_ep_finish_job(&udd_ep_job[i], true, i + 1);
	}
}


static void udd_ep_abort_job(udd_ep_id_t ep)
{
	ep &= USB_EP_ADDR_MASK;

	// Abort job on endpoint
	udd_ep_finish_job(&udd_ep_job[ep - 1], true, ep);
}


static void udd_ep_finish_job(udd_ep_job_t * ptr_job, bool b_abort, uint8_t ep_num)
{
	if (ptr_job->busy == false) {
		return; // No on-going job
	}
	dbg_print("(JobE%x:%d) ", (ptr_job-udd_ep_job)+1, b_abort);
	ptr_job->busy = false;
	if (NULL == ptr_job->call_trans) {
		return; // No callback linked to job
	}
	if (Is_udd_endpoint_in(ep_num)) {
		ep_num |= USB_EP_DIR_IN;
	}
	ptr_job->call_trans((b_abort) ? UDD_EP_TRANSFER_ABORT :
			UDD_EP_TRANSFER_OK, ptr_job->buf_size, ep_num);
}

#ifdef UDD_EP_DMA_SUPPORTED
static void udd_ep_trans_done(udd_ep_id_t ep)
{
	uint32_t udd_dma_ctrl = 0;
	udd_ep_job_t *ptr_job;
	iram_size_t next_trans;
	irqflags_t flags;

	// Get job corresponding at endpoint
	ptr_job = &udd_ep_job[ep - 1];

	if (!ptr_job->busy) {
		return; // No job is running, then ignore it (system error)
	}

	if (ptr_job->buf_cnt != ptr_job->buf_size) {
		// Need to send or receiv other data
		next_trans = ptr_job->buf_size - ptr_job->buf_cnt;

		if (UDD_ENDPOINT_MAX_TRANS < next_trans) {
			// The USB hardware support a maximum
			// transfer size of UDD_ENDPOINT_MAX_TRANS Bytes
			next_trans = UDD_ENDPOINT_MAX_TRANS;

			// Set 0 to tranfer the maximum
			udd_dma_ctrl = USBHS_DEVDMACONTROL_BUFF_LENGTH(0);
		} else {
			udd_dma_ctrl = USBHS_DEVDMACONTROL_BUFF_LENGTH(next_trans);
		}
		if (Is_udd_endpoint_in(ep)) {
			if (0 != (next_trans % udd_get_endpoint_size(ep))) {
				// Enable short packet option
				// else the DMA transfer is accepted
				// and interrupt DMA valid but nothing is sent.
				udd_dma_ctrl |= USBHS_DEVDMACONTROL_END_B_EN;
				// No need to request another ZLP
				ptr_job->b_shortpacket = false;
			}
		} else {
			if ((USB_EP_TYPE_ISOCHRONOUS != udd_get_endpoint_type(ep))
					|| (next_trans <= (iram_size_t) udd_get_endpoint_size(ep))) {

				// Enable short packet reception
				udd_dma_ctrl |= USBHS_DEVDMACONTROL_END_TR_IT
						| USBHS_DEVDMACONTROL_END_TR_EN;
			}
		}

		// Start USB DMA to fill or read fifo of the selected endpoint
		udd_endpoint_dma_set_addr(ep, (uint32_t) & ptr_job->buf[ptr_job->buf_cnt]);
		udd_dma_ctrl |= USBHS_DEVDMACONTROL_END_BUFFIT |
				USBHS_DEVDMACONTROL_CHANN_ENB;


		// Disable IRQs to have a short sequence
		// between read of EOT_STA and DMA enable
		flags = cpu_irq_save();
		if (!(udd_endpoint_dma_get_status(ep)
				& USBHS_DEVDMASTATUS_END_TR_ST)) {
			dbg_print("dmaS%x ", ep);
			udd_endpoint_dma_set_control(ep, udd_dma_ctrl);
			ptr_job->buf_cnt += next_trans;
			ptr_job->buf_load = next_trans;
			udd_enable_endpoint_dma_interrupt(ep);
			cpu_irq_restore(flags);
			return;
		}
		cpu_irq_restore(flags);

		// Here a ZLP has been recieved
		// and the DMA transfer must be not started.
		// It is the end of transfer
		ptr_job->buf_size = ptr_job->buf_cnt;
	}
	if (Is_udd_endpoint_in(ep)) {
		if (ptr_job->b_shortpacket) {
			dbg_print("zlpS%x ", ep);
			// Need to send a ZLP (No possible with USB DMA)
			// enable interrupt to wait a free bank to sent ZLP
			udd_ack_in_send(ep);
			if (Is_udd_write_enabled(ep)) {
				// Force interrupt in case of ep already free
				udd_raise_in_send(ep);
			}
			udd_enable_in_send_interrupt(ep);
			udd_enable_endpoint_interrupt(ep);
			return;
		}
	} else {
		_dcache_invalidate(ptr_job->buf, ptr_job->buf_size);
	}
	dbg_print("dmaE ");
	// Call callback to signal end of transfer
	udd_ep_finish_job(ptr_job, false, ep);
}
#endif

#ifdef UDD_EP_FIFO_SUPPORTED
static void udd_ep_in_sent(udd_ep_id_t ep)
{
	udd_ep_job_t *ptr_job = &udd_ep_job[ep - 1];
	uint8_t *ptr_src = &ptr_job->buf[ptr_job->buf_cnt];
	uint8_t *ptr_dst = (uint8_t *) & udd_get_endpoint_fifo_access(ep, 8);
	uint32_t pkt_size = udd_get_endpoint_size(ep);
	uint32_t nb_data = 0, i;
	uint32_t nb_remain;
	irqflags_t flags;

	// All transfer done, including ZLP, Finish Job
	if (ptr_job->buf_cnt >= ptr_job->buf_size && !ptr_job->b_shortpacket) {
		flags = cpu_irq_save();
		udd_disable_in_send_interrupt(ep);
		udd_disable_endpoint_interrupt(ep);
		cpu_irq_restore(flags);

		ptr_job->buf_size = ptr_job->buf_cnt; // buf_size is passed to callback as XFR count
		udd_ep_finish_job(ptr_job, false, ep);
		return;
	} else {
		// ACK TXINI
		udd_ack_in_send(ep);
		// Fill FIFO
		ptr_dst = (uint8_t *) & udd_get_endpoint_fifo_access(ep, 8);
		ptr_src = &ptr_job->buf[ptr_job->buf_cnt];
		nb_remain = ptr_job->buf_size - ptr_job->buf_cnt;
		// Fill a bank even if no data (ZLP)
		nb_data = min(nb_remain, pkt_size);
		// Modify job information
		ptr_job->buf_cnt += nb_data;
		ptr_job->buf_load = nb_data;

		// Copy buffer to FIFO
		for (i = 0; i < nb_data; i++) {
			*ptr_dst++ = *ptr_src++;
		}
		// Switch to next bank
		__DSB();
		__ISB();
		udd_ack_fifocon(ep);
		// ZLP?
		if (nb_data < pkt_size) {
			ptr_job->b_shortpacket = false;
		}
	}
}

static void udd_ep_out_received(udd_ep_id_t ep)
{
	udd_ep_job_t *ptr_job = &udd_ep_job[ep - 1];
	uint32_t nb_data = 0, i;
	uint32_t nb_remain = ptr_job->buf_size - ptr_job->buf_cnt;
	uint32_t pkt_size = udd_get_endpoint_size(ep);
	uint8_t *ptr_src = (uint8_t *) & udd_get_endpoint_fifo_access(ep, 8);
	uint8_t *ptr_dst = &ptr_job->buf[ptr_job->buf_cnt];
	bool b_full = false, b_short = false;

	// Clear RX OUT
	udd_ack_out_received(ep);

	// Read byte count
	nb_data = udd_byte_count(ep);
	if (nb_data < pkt_size) {
		b_short = true;
	}
	//dbg_print("o%d ", ep);
	//dbg_print("%d ", nb_data);
	// Copy data if there is
	if (nb_data > 0) {
		if (nb_data >= nb_remain) {
			nb_data = nb_remain;
			b_full = true;
		}
		// Modify job information
		ptr_job->buf_cnt += nb_data;
		ptr_job->buf_load = nb_data;
		// Copy FIFO to buffer
		for (i = 0; i < nb_data; i++) {
			*ptr_dst++ = *ptr_src++;
		}
		__DSB();
		__ISB();
	}
	// Clear FIFO Status
	udd_ack_fifocon(ep);
	// Finish job on error or short packet
	if (b_full || b_short) {
		//dbg_print("EoO%d\n\r", ep);
		udd_disable_out_received_interrupt(ep);
		udd_disable_endpoint_interrupt(ep);
		ptr_job->buf_size = ptr_job->buf_cnt; // buf_size is passed to callback as XFR count
		udd_ep_finish_job(ptr_job, false, ep);
	}
}
#endif // #ifdef UDD_EP_FIFO_SUPPORTED

static bool udd_ep_interrupt(void)
{
	udd_ep_id_t ep;
	udd_ep_job_t *ptr_job;

	// For each endpoint different of control endpoint (0)
	for (ep = 1; ep <= USB_DEVICE_MAX_EP; ep++) {
		// Get job corresponding at endpoint
		ptr_job = &udd_ep_job[ep - 1];

#ifdef UDD_EP_DMA_SUPPORTED
		// Check DMA event
		if (Is_udd_endpoint_dma_interrupt_enabled(ep)
				&& Is_udd_endpoint_dma_interrupt(ep)) {
			uint32_t nb_remaining;
			if (udd_endpoint_dma_get_status(ep)
					& USBHS_DEVDMASTATUS_CHANN_ENB) {
				return true; // Ignore EOT_STA interrupt
			}
			dbg_print("dma%x: ", ep);
			udd_disable_endpoint_dma_interrupt(ep);
			// Save number of data no transfered
			nb_remaining = (udd_endpoint_dma_get_status(ep) &
					USBHS_DEVDMASTATUS_BUFF_COUNT_Msk)
					>> USBHS_DEVDMASTATUS_BUFF_COUNT_Pos;
			if (nb_remaining) {
				// Transfer no complete (short packet or ZLP) then:
				// Update number of data transfered
				ptr_job->buf_cnt -= nb_remaining;
				// Set transfer complete to stop the transfer
				ptr_job->buf_size = ptr_job->buf_cnt;
			}
			udd_ep_trans_done(ep);
			return true;
		}
#endif
#ifdef UDD_EP_FIFO_SUPPORTED
		// Check RXRDY and TXEMPTY event for none DMA endpoints
		if (!Is_udd_endpoint_dma_supported(ep)
				&& Is_udd_endpoint_interrupt_enabled(ep)) {
			dbg_print("ep%x: ", ep);
			// RXOUT: Full packet received
			if (Is_udd_out_received(ep)
				&& Is_udd_out_received_interrupt_enabled(ep)) {
				dbg_print("Out ");
				udd_ep_out_received(ep);
				return true;
			}
			// TXIN: packet sent
			if (Is_udd_in_send(ep)
					&& Is_udd_in_send_interrupt_enabled(ep)) {
				dbg_print("In ");
				udd_ep_in_sent(ep);
				return true;
			}
			// Errors: Abort?
			if (Is_udd_overflow(ep)
					|| Is_udd_underflow(ep)
					|| Is_udd_crc_error(ep)) {
				dbg_print("Err ");
				udd_ep_abort(ep);
				return true;
			}
		}
#endif // UDD_EP_FIFO_SUPPORTED
		// Check empty bank interrupt event
		if (Is_udd_endpoint_interrupt_enabled(ep)) {
			dbg_print("bg%x: ", ep);
			if (Is_udd_in_send_interrupt_enabled(ep)
					&& Is_udd_in_send(ep)) {
				dbg_print("I ");
				udd_disable_in_send_interrupt(ep);
				// One bank is free then send a ZLP
				udd_ack_in_send(ep);
				udd_ack_fifocon(ep);
				udd_ep_finish_job(ptr_job, false, ep);
				return true;
			}
			if (Is_udd_bank_interrupt_enabled(ep)
					&& (0 == udd_nb_busy_bank(ep))) {
				dbg_print("EoT ");
				// End of background transfer on IN endpoint
				udd_disable_bank_interrupt(ep);
				udd_disable_endpoint_interrupt(ep);

				Assert(ptr_job->stall_requested);
				// A stall has been requested during backgound transfer
				ptr_job->stall_requested = false;
				udd_disable_endpoint_bank_autoswitch(ep);
				udd_enable_stall_handshake(ep);
				udd_reset_data_toggle(ep);
				return true;
			}
		}
	}
	return false;
}
#endif // (0 != USB_DEVICE_MAX_EP)

//@}
