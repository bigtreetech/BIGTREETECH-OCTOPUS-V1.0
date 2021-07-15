/*
 * Dmac.cpp
 *
 *  Created on: 6 Sep 2018
 *      Author: David
 */

#include <CoreIO.h>

#if SAME5x
# include <hri_mclk_e54.h>
#elif SAMC21
# include <hri_mclk_c21.h>
#else
# error Unsupported processor
#endif

#include <DmacManager.h>
#include <RTOSIface/RTOSIface.h>
#include <Cache.h>

constexpr NvicPriority TempNvicPriorityDMA = 4;			// temporary DMA interrupt priority, low enough to allow FreeRTOS system calls

// Descriptors for all used DMAC channels
alignas(16) static DmacDescriptor descriptor_section[NumDmaChannelsSupported];

// Write back descriptors for all used DMAC channels
alignas(16) static DmacDescriptor write_back_section[NumDmaChannelsSupported];

// Array containing callbacks for DMAC channels
static DmaCallbackFunction dmaChannelCallbackFunctions[NumDmaChannelsSupported];
static CallbackParameter callbackParams[NumDmaChannelsSupported];

// Initialize the DMA controller
void DmacManager::Init() noexcept
{
	hri_mclk_set_AHBMASK_DMAC_bit(MCLK);

#if SAME5x
	DMAC->CTRL.reg &= ~DMAC_CTRL_DMAENABLE;
#elif SAMC21
	DMAC->CTRL.reg &= ~(DMAC_CTRL_DMAENABLE | DMAC_CTRL_CRCENABLE);
#else
# error Unsupported processor
#endif
	DMAC->CRCCTRL.reg = 0;

	DMAC->CTRL.reg |= DMAC_CTRL_SWRST;
	while ((DMAC->CTRL.reg & DMAC_CTRL_SWRST) != 0) { }

	DMAC->CTRL.reg = DMAC_CTRL_LVLEN0 | DMAC_CTRL_LVLEN1 | DMAC_CTRL_LVLEN2 | DMAC_CTRL_LVLEN3;

#if SAME5x
	DMAC->PRICTRL0.reg =  DMAC_PRICTRL0_RRLVLEN0 | DMAC_PRICTRL0_RRLVLEN1 | DMAC_PRICTRL0_RRLVLEN2 | DMAC_PRICTRL0_RRLVLEN3
							| DMAC_PRICTRL0_QOS0(0x02) | DMAC_PRICTRL0_QOS1(0x02)| DMAC_PRICTRL0_QOS2(0x02)| DMAC_PRICTRL0_QOS3(0x02);
#elif SAMC21
	DMAC->PRICTRL0.reg = DMAC_PRICTRL0_RRLVLEN0 | DMAC_PRICTRL0_RRLVLEN1 | DMAC_PRICTRL0_RRLVLEN2 | DMAC_PRICTRL0_RRLVLEN3;
	DMAC->QOSCTRL.reg = DMAC_QOSCTRL_WRBQOS(0x02) | DMAC_QOSCTRL_FQOS(0x02) | DMAC_QOSCTRL_DQOS(0x02);
#endif

	DMAC->BASEADDR.reg = reinterpret_cast<uint32_t>(descriptor_section);
	DMAC->WRBADDR.reg = reinterpret_cast<uint32_t>(write_back_section);

#if SAME5x
	// SAME5x DMAC has 5 contiguous IRQ numbers
	for (unsigned int i = 0; i < 5; i++)
	{
		NVIC_DisableIRQ((IRQn)(DMAC_0_IRQn + i));
		NVIC_ClearPendingIRQ((IRQn)(DMAC_0_IRQn + i));
		NVIC_SetPriority((IRQn)(DMAC_0_IRQn + i), TempNvicPriorityDMA);
		NVIC_EnableIRQ((IRQn)(DMAC_0_IRQn + i));
	}
#elif SAMC21
	NVIC_DisableIRQ(DMAC_IRQn);
	NVIC_ClearPendingIRQ(DMAC_IRQn);
	NVIC_SetPriority(DMAC_IRQn, TempNvicPriorityDMA);
	NVIC_EnableIRQ(DMAC_IRQn);
#else
# error Unsupported processor
#endif

	DMAC->CTRL.reg |= DMAC_CTRL_DMAENABLE;
}

void DmacManager::SetBtctrl(const uint8_t channel, const uint16_t val) noexcept
{
	descriptor_section[channel].BTCTRL.reg = val;
}

void DmacManager::SetDestinationAddress(const uint8_t channel, volatile void *const dst) noexcept
{
	descriptor_section[channel].DSTADDR.reg = reinterpret_cast<uint32_t>(dst);
}

void DmacManager::SetSourceAddress(const uint8_t channel, const volatile void *const src) noexcept
{
	descriptor_section[channel].SRCADDR.reg = reinterpret_cast<uint32_t>(src);
}

void DmacManager::SetDataLength(const uint8_t channel, const uint32_t amount) noexcept
{
	const uint8_t beat_size = descriptor_section[channel].BTCTRL.bit.BEATSIZE;

	if (descriptor_section[channel].BTCTRL.bit.DSTINC)
	{
		descriptor_section[channel].DSTADDR.reg += amount << beat_size;
	}

	if (descriptor_section[channel].BTCTRL.bit.SRCINC)
	{
		descriptor_section[channel].SRCADDR.reg += amount << beat_size;
	}

	descriptor_section[channel].BTCNT.reg = amount;
}

void DmacManager::SetTriggerSource(uint8_t channel, DmaTrigSource source) noexcept
{
#if SAME5x
	DMAC->Channel[channel].CHCTRLA.reg = DMAC_CHCTRLA_TRIGSRC((uint32_t)source) | DMAC_CHCTRLA_TRIGACT_BURST
											| DMAC_CHCTRLA_BURSTLEN_SINGLE | DMAC_CHCTRLA_THRESHOLD_1BEAT;
#elif SAMC21
	AtomicCriticalSectionLocker lock;
	DMAC->CHID.reg = channel;
	DMAC->CHCTRLB.reg = DMAC_CHCTRLB_TRIGSRC((uint8_t)source) | DMAC_CHCTRLB_TRIGACT_BEAT;
#else
# error Unsupported processor
#endif
}

void DmacManager::SetTriggerSourceSercomRx(uint8_t channel, uint8_t sercomNumber) noexcept
{
	const uint32_t source = GetSercomRxTrigSource(sercomNumber);
#if SAME5x
	DMAC->Channel[channel].CHCTRLA.reg = DMAC_CHCTRLA_TRIGSRC(source) | DMAC_CHCTRLA_TRIGACT_BURST
											| DMAC_CHCTRLA_BURSTLEN_SINGLE | DMAC_CHCTRLA_THRESHOLD_1BEAT;
#elif SAMC21
	AtomicCriticalSectionLocker lock;
	DMAC->CHID.reg = channel;
	DMAC->CHCTRLB.reg = DMAC_CHCTRLB_TRIGSRC((uint8_t)source) | DMAC_CHCTRLB_TRIGACT_BEAT;
#else
# error Unsupported processor
#endif
}

// Transmit
void DmacManager::SetTriggerSourceSercomTx(uint8_t channel, uint8_t sercomNumber) noexcept
{
	const uint32_t source = GetSercomTxTrigSource(sercomNumber);
#if SAME5x
	DMAC->Channel[channel].CHCTRLA.reg = DMAC_CHCTRLA_TRIGSRC(source) | DMAC_CHCTRLA_TRIGACT_BURST
											| DMAC_CHCTRLA_BURSTLEN_SINGLE | DMAC_CHCTRLA_THRESHOLD_1BEAT;
#elif SAMC21
	AtomicCriticalSectionLocker lock;
	DMAC->CHID.reg = channel;
	DMAC->CHCTRLB.reg = DMAC_CHCTRLB_TRIGSRC((uint8_t)source) | DMAC_CHCTRLB_TRIGACT_BEAT;
#else
# error Unsupported processor
#endif
}

void DmacManager::SetArbitrationLevel(uint8_t channel, uint8_t level) noexcept
{
#if SAME5x
	DMAC->Channel[channel].CHPRILVL.reg = level;
#elif SAMC21
	AtomicCriticalSectionLocker lock;
	DMAC->CHID.reg = channel;
	DMAC->CHCTRLB.reg = (DMAC->CHCTRLB.reg & ~DMAC_CHCTRLB_LVL_Msk) | (level << DMAC_CHCTRLB_LVL_Pos);
#else
# error Unsupported processor
#endif
}

void DmacManager::EnableChannel(const uint8_t channel, DmaPriority priority) noexcept
{
	descriptor_section[channel].DESCADDR.reg = 0;
	descriptor_section[channel].BTCTRL.bit.VALID = 1;
	Cache::FlushBeforeDMASend(&descriptor_section[channel], sizeof(descriptor_section[channel]));

#if SAME5x
	DMAC->Channel[channel].CHPRILVL.reg = priority;
	DMAC->Channel[channel].CHCTRLA.bit.ENABLE = 1;
#elif SAMC21
	AtomicCriticalSectionLocker lock;
	DMAC->CHID.reg = channel;
	DMAC->CHCTRLB.bit.LVL = priority;
	DMAC->CHCTRLA.bit.ENABLE = 1;
#else
# error Unsupported processor
#endif
}

// Disable a channel. Also clears its status and disables its interrupts.
// On the SAME5x it is sometimes impossible to disable a channel. So we now return true if disabling it succeeded, false it it is still enabled.
bool DmacManager::DisableChannel(const uint8_t channel) noexcept
{
	unsigned int i = 0;
	bool disabled;
#if SAME5x
	DmacChannel& chan = DMAC->Channel[channel];
	do
	{
		chan.CHCTRLA.bit.ENABLE = 0;
		disabled = (chan.CHCTRLA.bit.ENABLE == 0);
	}
	while (!disabled && ++i < 10);
	chan.CHINTENCLR.reg = DMAC_CHINTENCLR_TCMPL | DMAC_CHINTENCLR_TERR | DMAC_CHINTENCLR_SUSP;
#elif SAMC21
	AtomicCriticalSectionLocker lock;
	DMAC->CHID.reg = channel;
	do
	{
		DMAC->CHCTRLA.bit.ENABLE = 0;
		disabled = (DMAC->CHCTRLA.bit.ENABLE == 0);
	}
	while (!disabled && ++i < 10);
	DMAC->CHINTFLAG.reg = DMAC_CHINTENCLR_TCMPL | DMAC_CHINTENCLR_TERR | DMAC_CHINTENCLR_SUSP;
#else
# error Unsupported processor
#endif
	return disabled;
}

void DmacManager::SetInterruptCallback(uint8_t channel, DmaCallbackFunction fn, CallbackParameter param) noexcept
{
	AtomicCriticalSectionLocker lock;
	dmaChannelCallbackFunctions[channel] = fn;
	callbackParams[channel] = param;
}

void DmacManager::EnableCompletedInterrupt(const uint8_t channel) noexcept
{
#if SAME5x
	DMAC->Channel[channel].CHINTFLAG.reg = DMAC_CHINTENCLR_TCMPL | DMAC_CHINTENCLR_TERR | DMAC_CHINTENCLR_SUSP;
	DMAC->Channel[channel].CHINTENSET.reg = DMAC_CHINTENSET_TCMPL | DMAC_CHINTENSET_TERR;
#elif SAMC21
	AtomicCriticalSectionLocker lock;
	DMAC->CHID.reg = channel;
	DMAC->CHINTENCLR.reg = DMAC_CHINTENCLR_TCMPL | DMAC_CHINTENCLR_TERR | DMAC_CHINTENCLR_SUSP;
	DMAC->CHINTENSET.reg = DMAC_CHINTENSET_TCMPL | DMAC_CHINTENSET_TERR;
#else
# error Unsupported processor
#endif
}

void DmacManager::DisableCompletedInterrupt(const uint8_t channel) noexcept
{
#if SAME5x
	DMAC->Channel[channel].CHINTENCLR.reg = DMAC_CHINTENSET_TCMPL | DMAC_CHINTENSET_TERR;
#elif SAMC21
	AtomicCriticalSectionLocker lock;
	DMAC->CHID.reg = channel;
	DMAC->CHINTENCLR.reg = DMAC_CHINTENSET_TCMPL | DMAC_CHINTENSET_TERR;
#else
# error Unsupported processor
#endif
}

uint8_t DmacManager::GetAndClearChannelStatus(uint8_t channel) noexcept
{
#if SAME5x
	const uint8_t ret = DMAC->Channel[channel].CHINTFLAG.reg;
	DMAC->Channel[channel].CHINTFLAG.reg = ret;
	return ret;
#elif SAMC21
	AtomicCriticalSectionLocker lock;
	DMAC->CHID.reg = channel;
	const uint8_t ret = DMAC->CHINTFLAG.reg;
	DMAC->CHINTFLAG.reg = ret;
	return ret;
#else
# error Unsupported processor
#endif
}

uint16_t DmacManager::GetBytesTransferred(uint8_t channel) noexcept
{
	Cache::InvalidateAfterDMAReceive(&write_back_section[channel].BTCNT, sizeof(write_back_section[channel].BTCNT));
	return descriptor_section[channel].BTCNT.reg - write_back_section[channel].BTCNT.reg;
}

#if SAME5x

// Internal DMAC interrupt handler
static inline void CommonDmacHandler(uint8_t channel) noexcept
{
	const uint8_t intflag = DMAC->Channel[channel].CHINTFLAG.reg & DMAC->Channel[channel].CHINTENSET.reg & (DMAC_CHINTFLAG_SUSP | DMAC_CHINTFLAG_TCMPL | DMAC_CHINTFLAG_TERR);
	if (intflag != 0)					// should always be true
	{
		DMAC->Channel[channel].CHINTFLAG.reg = intflag;
		const DmaCallbackFunction fn = dmaChannelCallbackFunctions[channel];
		if (fn != nullptr)
		{
			fn(callbackParams[channel], (DmaCallbackReason)intflag);
		}
	}
}

extern "C" void DMAC_0_Handler() noexcept
{
	CommonDmacHandler(0);
}

extern "C" void DMAC_1_Handler() noexcept
{
	CommonDmacHandler(1);
}

extern "C" void DMAC_2_Handler() noexcept
{
	CommonDmacHandler(2);
}

extern "C" void DMAC_3_Handler() noexcept
{
	CommonDmacHandler(3);
}

extern "C" void DMAC_4_Handler() noexcept
{
	uint16_t intPend;
	while (((intPend = DMAC->INTPEND.reg) & (DMAC_INTPEND_SUSP | DMAC_INTPEND_TCMPL | DMAC_INTPEND_TERR)) != 0)
	{
		CommonDmacHandler(intPend & DMAC_INTPEND_ID_Msk);
	}
}

#elif SAMC21

extern "C" void DMAC_Handler() noexcept
{
	uint16_t intPend;
	while (((intPend = DMAC->INTPEND.reg) & (DMAC_INTPEND_SUSP | DMAC_INTPEND_TCMPL | DMAC_INTPEND_TERR)) != 0)
	{
		const size_t channel = intPend & DMAC_INTPEND_ID_Msk;
		DMAC->CHID.reg = channel;
		const uint8_t intflag = DMAC->CHINTFLAG.reg & DMAC->CHINTENSET.reg & (DMAC_CHINTFLAG_SUSP | DMAC_CHINTFLAG_TCMPL | DMAC_CHINTFLAG_TERR);
		if (intflag != 0)					// should always be true
		{
			DMAC->CHINTFLAG.reg = intflag;
			const DmaCallbackFunction fn = dmaChannelCallbackFunctions[channel];
			if (fn != nullptr)
			{
				fn(callbackParams[channel], (DmaCallbackReason)intflag);
			}
		}
	}
}

#else
# error Unsupported processor
#endif

// End
