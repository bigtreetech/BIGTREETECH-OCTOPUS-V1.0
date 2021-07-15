/**
 * \file
 *
 * \brief SAM XDMA Controller (XDMAC) driver.
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

#include  "xdmac.h"

/**
 * \brief Configure DMA for a transfer.
 *
 * \param[out] xdmac Module hardware register base address pointer.
 * \param[in] channel_num The used channel number.
 * \param[in] cfg   The configuration for used channel
 */
void xdmac_configure_transfer(Xdmac *xdmac,
		uint32_t channel_num, xdmac_channel_config_t *cfg)
{
	Assert(xdmac);
	Assert(channel_num < XDMACCHID_NUMBER);
	Assert(cfg);
	
	xdmac_channel_get_interrupt_status( xdmac, channel_num);
	xdmac_channel_set_source_addr(xdmac, channel_num, cfg->mbr_sa);
	xdmac_channel_set_destination_addr(xdmac, channel_num, cfg->mbr_da);
	xdmac_channel_set_microblock_control(xdmac, channel_num, cfg->mbr_ubc);
	xdmac_channel_set_block_control(xdmac, channel_num, cfg->mbr_bc);
	xdmac_channel_set_datastride_mempattern(xdmac, channel_num, cfg->mbr_ds);
	xdmac_channel_set_source_microblock_stride(xdmac, channel_num, cfg->mbr_sus);
	xdmac_channel_set_destination_microblock_stride(xdmac, channel_num, cfg->mbr_dus);
	xdmac_channel_set_config(xdmac, channel_num, cfg->mbr_cfg );
}