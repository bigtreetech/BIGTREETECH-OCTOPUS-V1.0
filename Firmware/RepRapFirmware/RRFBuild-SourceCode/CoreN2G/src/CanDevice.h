/*
 * CanDevice.h
 *
 *  Created on: 2 Sep 2020
 *      Author: David
 */

#ifndef SRC_CANDEVICE_H_
#define SRC_CANDEVICE_H_

#include <CoreIO.h>

#if SUPPORT_CAN

# include <CanId.h>
# include <General/Bitmap.h>

# ifdef RTOS
#  include <RTOSIface/RTOSIface.h>
# endif

constexpr unsigned int MaxTxBuffers = 6;			// maximum number of dedicated transmit buffers supported by this driver
constexpr unsigned int MaxRxBuffers = 4;			// maximum number of dedicated receive buffers supported by this driver

static_assert(MaxTxBuffers <= 31);					// the hardware allows up to 32 if there is no transmit FIFO but our code only supports up to 31 + a FIFO
static_assert(MaxRxBuffers <= 30);					// the hardware allows up to 64 but our code only supports up to 30 + the FIFOs

# if SAME70
constexpr unsigned int NumCanDevices = 2;			// this driver supports both CAN devices on the SAME70
typedef Mcan Can;
#else
constexpr unsigned int NumCanDevices = 1;			// on other MCUs we only support one CAN device
# endif

class CanMessageBuffer;
class CanTiming;

class CanDevice
{
public:
	enum class RxBufferNumber : uint32_t
	{
		fifo0 = 0, fifo1,
		buffer0, buffer1, buffer2, buffer3,
	};

	enum class TxBufferNumber : uint32_t
	{
		fifo = 0,
		buffer0, buffer1, buffer2, buffer3, buffer4, buffer5,
	};

	// Struct used to pass configuration constants, with default values
	struct Config
	{
		unsigned int dataSize = 64;											// must be one of: 8, 12, 16, 20, 24, 32, 48, 64
		unsigned int numTxBuffers = 2;
		unsigned int txFifoSize = 4;
		unsigned int numRxBuffers = 0;
		unsigned int rxFifo0Size = 16;
		unsigned int rxFifo1Size = 16;
		unsigned int numShortFilterElements = 0;
		unsigned int numExtendedFilterElements = 3;
		unsigned int txEventFifoSize = 16;

		// Test whether the data size is supported by the CAN hardware
		constexpr bool ValidDataSize() const noexcept
		{
			return dataSize >= 8
				&& (   (dataSize <= 24 && (dataSize & 3) == 0)
					|| (dataSize <= 64 && (dataSize & 15) == 0)
				   );
		}

		// Test whether this is a valid CAN configuration. Use this in a static_assert to check that a specified configuration is valid.
		constexpr bool IsValid() const noexcept
		{
			return ValidDataSize()
				&& numTxBuffers + txFifoSize <= 32							// maximum total Tx buffers supported is 32
				&& numTxBuffers <= MaxTxBuffers								// our code only allows 31 buffers + the FIFO
				&& numRxBuffers <= MaxRxBuffers								// the peripheral supports up to 64 buffers but our code only allows 30 buffers + the two FIFOs
				&& rxFifo0Size <= 64										// max 64 entries per receive FIFO
				&& rxFifo1Size <= 64										// max 64 entries per receive FIFO
				&& txEventFifoSize <= 32;									// max 32 entries in transmit event FIFO
		}

		// Return the number of words of memory occupied by the 11-bit filters
		// We round this up to the next multiple of 8 bytes to reduce the chance of the Tx and Rx buffers crossing cache lines
		constexpr size_t GetStandardFiltersMemSize() const noexcept
		{
			constexpr size_t StandardFilterElementSize = 1;					// one word each
			return ((numShortFilterElements * StandardFilterElementSize) + 1u) & (~1u);
		}

		// Return the number of words of memory occupied by the 29-bit filters
		constexpr size_t GetExtendedFiltersMemSize() const noexcept
		{
			constexpr size_t ExtendedFilterElementSize = 2;					// two words
			return numExtendedFilterElements * ExtendedFilterElementSize;
		}

		// Return the number of words of memory occupied by each transmit buffer
		constexpr size_t GetTxBufferSize() const noexcept
		{
			return (dataSize >> 2) + 2;										// each receive buffer has a 2-word header
		}

		// Return the number of words of memory occupied by each receive buffer
		constexpr size_t GetRxBufferSize() const noexcept
		{
			return (dataSize >> 2) + 2;										// each transmit buffer has a 2-word header
		}

		// Return the number of words of memory occupied by the transmit event FIFO
		constexpr size_t GetTxEventFifoMemSize() const noexcept
		{
			constexpr size_t TxEventEntrySize = 2;							// each transmit event entry is 2 words
			return txEventFifoSize * TxEventEntrySize;
		}

		// Return the total amount of buffer memory needed in 32-bit words. Must be constexpr so we can allocate memory statically in the correct segment.
		constexpr size_t GetMemorySize() const noexcept
		{
			return (numTxBuffers + txFifoSize) * GetTxBufferSize()
				+ (numRxBuffers + rxFifo0Size + rxFifo1Size) * GetRxBufferSize()
				+ GetStandardFiltersMemSize()
				+ GetExtendedFiltersMemSize()
				+ GetTxEventFifoMemSize();
		}
	};

	// Type of the callback function called when a transmi event with a nonzero message marker occurs
	typedef void (*TxEventCallbackFunction)(uint8_t marker, CanId id, uint16_t timeStamp) noexcept;

	// Initialise one of the CAN interfaces and return a pointer to the corresponding device. Returns null if device is already in use or device number is out of range.
	static CanDevice *Init(unsigned int p_whichCan, unsigned int p_whichPort, const Config& p_config, uint32_t *memStart, const CanTiming& timing, TxEventCallbackFunction p_txCallback) noexcept;

	// Set the extended ID mask. May only be used while the interface is disabled.
	void SetExtendedIdMask(uint32_t mask) noexcept;

	// Free the device
	void DeInit() noexcept;

	// Enable the device
	void Enable() noexcept;

	// Disable the device
	void Disable() noexcept;

	// Wait for a transmit buffer to become free, with timeout. Return true if it's free.
	bool IsSpaceAvailable(TxBufferNumber whichBuffer, uint32_t timeout) noexcept;

	// Queue a message for sending via a buffer or FIFO. If the buffer isn't free, cancel the previous message (or oldest message in the fifo) and send it anyway.
	void SendMessage(TxBufferNumber whichBuffer, uint32_t timeout, CanMessageBuffer *buffer) noexcept;

	// Receive a message in a buffer or fifo, with timeout. Returns true if successful, false if no message available even after the timeout period.
	bool ReceiveMessage(RxBufferNumber whichBuffer, uint32_t timeout, CanMessageBuffer *buffer) noexcept;

	// Check whether a message is available, returning true if it is
	bool IsMessageAvailable(RxBufferNumber whichBuffer) noexcept;

	// Set a short ID field filter element. To disable the filter element, use a zero mask parameter.
	// If whichBuffer is a buffer number not a fifo number, the mask field is ignored except that a zero mask disables the filter element; so only the XIDAM mask filters the ID.
	void SetShortFilterElement(unsigned int index, RxBufferNumber whichBuffer, uint32_t id, uint32_t mask) noexcept
		pre(index < NumShortFilterElements);

	// Set an extended ID field filter element. To disable the filter element, use a zero mask parameter.
	// If whichBuffer is a buffer number not a fifo number, the mask field is ignored except that a zero mask disables the filter element; so only the XIDAM mask filters the ID.
	void SetExtendedFilterElement(unsigned int index, RxBufferNumber whichBuffer, uint32_t id, uint32_t mask) noexcept
		pre(index < NumShortFilterElements);

	void GetLocalCanTiming(CanTiming& timing) noexcept;

	void SetLocalCanTiming(const CanTiming& timing) noexcept;

	void GetAndClearStats(unsigned int& rMessagesQueuedForSending, unsigned int& rMessagesReceived, unsigned int& rTxTimeouts,
							unsigned int& rMessagesLost, unsigned int& rBusOffCount, uint32_t& rLastCancelledId) noexcept;

	uint16_t ReadTimeStampCounter() noexcept
	{
#if SAME70
		return hw->MCAN_TSCV;
#else
		return hw->TSCV.reg;
#endif
	}

#if !SAME70
	uint16_t GetTimeStampPeriod() noexcept
	{
		return bitPeriod;
	}
#endif

	void PollTxEventFifo(TxEventCallbackFunction p_txCallback) noexcept;

	uint32_t GetErrorRegister() const noexcept;

#ifdef RTOS
	void Interrupt() noexcept;
#endif

	// Configuration constants. Need to be public because they are used to size static data in CanDevice.cpp
	static constexpr size_t Can0DataSize = 64;

private:
	struct TxEvent;
	struct StandardMessageFilterElement;
	struct ExtendedMessageFilterElement;
	class RxBufferHeader;
	class TxBufferHeader;

	static CanDevice devices[NumCanDevices];

	CanDevice() noexcept { }
	void DoHardwareInit() noexcept;
	void UpdateLocalCanTiming(const CanTiming& timing) noexcept;
	uint32_t GetRxBufferSize() const noexcept;
	uint32_t GetTxBufferSize() const noexcept;
	RxBufferHeader *GetRxFifo0Buffer(uint32_t index) const noexcept;
	RxBufferHeader *GetRxFifo1Buffer(uint32_t index) const noexcept;
	RxBufferHeader *GetRxBuffer(uint32_t index) const noexcept;
	TxBufferHeader *GetTxBuffer(uint32_t index) const noexcept;
	TxEvent *GetTxEvent(uint32_t index) const noexcept;

	void CopyMessageForTransmit(CanMessageBuffer *buffer, volatile TxBufferHeader *f) noexcept;
	void CopyReceivedMessage(CanMessageBuffer *buffer, const volatile RxBufferHeader *f) noexcept;

	Can *hw;													// address of the CAN peripheral we are using

	unsigned int whichCan;										// which CAN device we are
	unsigned int whichPort;										// which CAN port number we use, 0 or 1
	uint32_t nbtp;												//!< The NBTP register that gives the required normal bit timing
	uint32_t dbtp;												//!< The DBTP register that gives the required bit timing when we use BRS
	uint32_t statusMask;

	const Config *config;										//!< Configuration parameters
	volatile uint32_t *rx0Fifo;									//!< Receive message fifo start
	volatile uint32_t *rx1Fifo;									//!< Receive message fifo start
	volatile uint32_t *rxBuffers;								//!< Receive direct buffers start
	uint32_t *txBuffers;										//!< Transmit direct buffers start (the Tx fifo buffers follow them)
	TxEvent *txEventFifo;										//!< Transfer event fifo
	StandardMessageFilterElement *rxStdFilter;					//!< Standard filter List
	ExtendedMessageFilterElement *rxExtFilter;					//!< Extended filter List

	unsigned int messagesQueuedForSending;
	unsigned int messagesReceived;
	unsigned int txTimeouts;
	unsigned int messagesLost;									// count of received messages lost because the receive FIFO was full
	unsigned int busOffCount;									// count of the number of times we have reset due to bus off
	uint32_t lastCancelledId;

	TxEventCallbackFunction txCallback;							// function that gets called by the ISR when a transmit event for a message with a nonzero marker occurs

# ifdef RTOS
	// The following are all declared volatile because we care about when they are written
	volatile TaskHandle txTaskWaiting[MaxTxBuffers + 1];		// tasks waiting for each Tx buffer to become free, first entry is for the Tx FIFO
	volatile TaskHandle rxTaskWaiting[MaxRxBuffers + 2];		// tasks waiting for each Rx buffer to receive a message, first 2 entries are for the fifos
	std::atomic<uint32_t> rxBuffersWaiting;						// which Rx FIFOs and buffers tasks are waiting on
	std::atomic<uint32_t> txBuffersWaiting;						// which Tx FIFOs and buffers tasks are waiting on
# endif

#if !SAME70
	uint16_t bitPeriod;											// how many clocks in a CAN normal bit
#endif

	bool useFDMode;
};

#endif

#endif /* SRC_CANDEVICE_H_ */
