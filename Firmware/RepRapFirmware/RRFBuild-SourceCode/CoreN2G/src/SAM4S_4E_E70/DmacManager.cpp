/*
 * DmacManager.cpp
 *
 *  Created on: 12 Sep 2018
 *      Author: David
 *
 * The purpose of this module is to service the DMA Complete interrupt from the XDMAC on the SAME70
 * and route the interrupts caused by the various DMA channels to the corresponding drivers.
 */

#include <CoreIO.h>
#include "DmacManager.h"

#if SAME70
# include <pmc/pmc.h>

namespace DmacManager
{
	static DmaCallbackFunction callbackFunctions[NumDmaChannelsSupported] = { 0 };
	static CallbackParameter callbackParameters[NumDmaChannelsSupported];

	void Init() noexcept
	{
		pmc_enable_periph_clk(ID_XDMAC);
		for (unsigned int i = 0; i < NumDmaChannelsSupported; ++i)
		{
			XDMAC->XDMAC_CHID[i].XDMAC_CID = 0xFFFFFFFF;	// disable all XDMAC interrupts from the channel
		}
		NVIC_EnableIRQ(XDMAC_IRQn);
	}

	void SetInterruptCallback(DmaChannel channel, DmaCallbackFunction fn, CallbackParameter param) noexcept
	{
		if (channel < NumDmaChannelsSupported)
		{
			callbackFunctions[channel] = fn;
			callbackParameters[channel] = param;
		}
	}
}

// DMAC interrupt service routine
extern "C" void XDMAC_Handler() noexcept
{
	uint32_t pendingChannels = XDMAC->XDMAC_GIS;
	for (size_t i = 0; i < NumDmaChannelsSupported; ++i)
	{
		if ((pendingChannels & 1u) != 0)
		{
			if (DmacManager::callbackFunctions[i] != nullptr)
			{
				DmacManager::callbackFunctions[i](DmacManager::callbackParameters[i], DmaCallbackReason::none);	// we rely on the callback to clear the interrupt
			}
			else
			{
				XDMAC->XDMAC_CHID[i].XDMAC_CID = 0xFFFFFFFF;							// no callback, so just clear the interrupt
			}
		}
		pendingChannels >>= 1;
	}
}

#endif

// End
