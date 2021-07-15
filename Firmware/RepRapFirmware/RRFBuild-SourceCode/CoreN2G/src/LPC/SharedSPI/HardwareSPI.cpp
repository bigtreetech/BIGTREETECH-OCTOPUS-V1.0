//Hardware SPI
#include "HardwareSPI.h"
#include "chip.h"

#include "DMA.h"

#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

#define SPI0_FUNCTION  PINSEL_FUNC_2 //SSP
#define SPI1_FUNCTION  PINSEL_FUNC_2

#define SPI_TIMEOUT       15000
// Pin usage, SSP1 has a fixed set of pins SSP0 has two alternatives for each pin
static constexpr Pin SSP1Pins[] = {SPI1_SCK, SPI1_MISO, SPI1_MOSI, SPI1_SSEL};
static Pin SSP0Pins[] = {SPI0_SCK, SPI0_MISO, SPI0_MOSI, SPI0_SSEL};

//SSP Status Register Bits
constexpr uint8_t SR_TFE = (1<<0); //Transmit FIFO Empty. This bit is 1 is the Transmit FIFO is empty, 0 if not.
constexpr uint8_t SR_TNF = (1<<1); //Transmit FIFO Not Full. This bit is 0 if the Tx FIFO is full, 1 if not.
constexpr uint8_t SR_RNE = (1<<2); //Receive FIFO Not Empty. This bit is 0 if the Receive FIFO is empty, 1 if not
constexpr uint8_t SR_RFF = (1<<3); //Receive FIFO Full. This bit is 1 if the Receive FIFO is full, 0 if not.
constexpr uint8_t SR_BSY = (1<<4); //Busy. This bit is 0 if the SSPn controller is idle, or 1 if it is currently sending/receiving a frame and/or the Tx FIFO is not empty.

HardwareSPI HardwareSPI::SSP0(LPC_SSP0, SSP0Pins);
HardwareSPI HardwareSPI::SSP1(LPC_SSP1, (Pin *)SSP1Pins);

//#define SSPI_DEBUG
extern "C" void debugPrintf(const char* fmt, ...) __attribute__ ((format (printf, 1, 2)));

// Flush the TX fifo. Note this code makes use of "reserved" registers
// these are actually test registers for the ARM PrimeCell Synchronous Serial
// Port (PL022), which is used to provide SSP devices on the LPC1768 device.
// For details see: 
// http://infocenter.arm.com/help/topic/com.arm.doc.ddi0194g/DDI0194G_ssp_pl022_r1p3_trm.pdf 
#define SSPTCR(SSP) ((__IO uint32_t *)((__IO uint8_t *)(SSP) + 0x80))
#define SSPTDR(SSP) ((__IO uint32_t *)((__IO uint8_t *)(SSP) + 0x8C))

static inline void flushTxFifo(LPC_SSP_T* sspDevice) noexcept
{
    if (sspDevice->SR & SR_TFE) return;
    // enable test mode access to the TX fifo 
    *SSPTCR(sspDevice) |= 0x2;
    //debugPrintf("status reg %x\n", LPC_SSP0->SR);
    int cnt = 8;
    while(!(sspDevice->SR & SR_TFE) && cnt-- > 0)
    {
        (void)(*SSPTDR(sspDevice));
    }
    // back to normal mode
    *SSPTCR(sspDevice) &= ~2;
    //debugPrintf("status reg %x cnt %d\n", LPC_SSP0->SR, cnt);
}

static inline void flushRxFifo(LPC_SSP_T* sspDevice) noexcept
{
    while(sspDevice->SR & SR_RNE)
    {
        (void)sspDevice->DR;
    }
}

void HardwareSPI::flushRx() noexcept
{
    flushRxFifo(ssp);
}

// Disable the device and flush any data from the fifos
void HardwareSPI::disable() noexcept
{
#ifdef SSPI_DEBUG
    if( (ssp->SR & SR_BSY) ) debugPrintf("SPI Busy\n");
    if( !(ssp->SR & SR_TFE) ) debugPrintf("SPI Tx Not Empty\n");
    if( (ssp->SR & SR_RNE) ) debugPrintf("SPI Rx Not Empty\n");
#endif

    Chip_SSP_DMA_Disable(ssp);
    // enable so we can flush the queues
    Chip_SSP_Enable(ssp);
    flushTxFifo(ssp);
    flushRxFifo(ssp);
    Chip_SSP_Disable(ssp);
    Chip_SSP_ClearIntPending(ssp, SSP_INT_CLEAR_BITMASK);
}

// Wait for transmitter empty returning true if timed out
//static inline bool waitForTxEmpty(LPC_SSP_TypeDef* sspDevice)
bool HardwareSPI::waitForTxEmpty() noexcept
{
    int timeout = SPI_TIMEOUT;
    while (!(ssp->SR & SR_TFE) ) // TNF = 0 if full
    {
        if (!timeout--)
        {
            return true;
        }
    }
    return false;
}

static inline CHIP_SSP_BITS_T getSSPBits(uint8_t bits) noexcept
{
    //we will only support 8 or 16bit
    
    if(bits == 16) return SSP_BITS_16;
    
    return SSP_BITS_8;
}

#define SPI_CPHA  (1 << 0) //Phase Control
#define SPI_CPOL  (1 << 1) //Clock Polarity


//Mode 0 - CPOL=0  - produces a steady state low value on the SCK pin
//       - CPHA=0  - data is captured on the first clock edge transition
#define SPI_MODE_0  0

//Mode 1 - CPOL=0  - produces a steady state low value on the SCK pin
//       - CPHA=1  - data is captured on the second clock edge transition
#define SPI_MODE_1  (SPI_CPHA)

//Mode 2 - CPOL=1  - a steady state high value is placed on the CLK pin when data is not being transferred
//       - CPHA=0  - data is captured on the first clock edge transition
#define SPI_MODE_2  (SPI_CPOL)

//Mode 3 - CPOL=1  - a steady state high value is placed on the CLK pin when data is not being transferred
//       - CPHA=1  - data is captured on the second clock edge transition
#define SPI_MODE_3  (SPI_CPOL | SPI_CPHA)

static inline CHIP_SSP_CLOCK_MODE_T getSSPMode(uint8_t spiMode) noexcept
{
    switch(spiMode)
    {

        case SPI_MODE_0: //CPHA=0, CPOL=0
            return SSP_CLOCK_CPHA0_CPOL0;
        case SPI_MODE_1: //CPHA=1, CPOL=0
            return SSP_CLOCK_CPHA1_CPOL0;
        case SPI_MODE_2: //CPHA=0, CPOL=1
            return SSP_CLOCK_CPHA0_CPOL1;
        case SPI_MODE_3: //CPHA=1, CPOL=1 
            return SSP_CLOCK_CPHA1_CPOL1;
    }
    
    return SSP_CLOCK_CPHA0_CPOL0;
}

extern "C"  void SSP0_IRQHandler(void) noexcept
{
    Chip_SSP_DMA_Disable(LPC_SSP0);
    Chip_SSP_Disable(LPC_SSP0);
    HardwareSPI *s = &HardwareSPI::SSP0;
    if (s->callback) s->callback(s);    
}

extern "C"  void SSP1_IRQHandler(void) noexcept
{
    Chip_SSP_DMA_Disable(LPC_SSP1);
    Chip_SSP_Disable(LPC_SSP1);
    HardwareSPI *s = &HardwareSPI::SSP1;
    if (s->callback) s->callback(s);
}    

// Called on completion of a blocking transfer
void transferComplete(HardwareSPI *spiDevice) noexcept
{
    BaseType_t higherPriorityTaskWoken = pdFALSE;
    vTaskNotifyGiveFromISR(spiDevice->waitingTask, &higherPriorityTaskWoken);
    portYIELD_FROM_ISR(higherPriorityTaskWoken);
}

void HardwareSPI::configurePins(bool hardwareCS) noexcept
{
    // Attach the SSP module to the I/O pins, note that SSP0 can use pins either on port 0 or port 1
    for(int i = 0; i < (hardwareCS ? 4 : 3); i++)
    {
        uint8_t port = pins[i] >> 5;
        uint8_t pin = pins[i] & 0x1f;
        Chip_IOCON_PinMux(LPC_IOCON, port, pin, IOCON_MODE_INACT, (port == 0 ? IOCON_FUNC2 : IOCON_FUNC3));
    }
}

void HardwareSPI::initPins(Pin sck, Pin miso, Pin mosi, Pin cs) noexcept
{
    if(ssp == LPC_SSP0)
    {
        SSP0Pins[0] = sck;
        SSP0Pins[1] = miso;
        SSP0Pins[2] = mosi;
        SSP0Pins[3] = cs;        
    }    
}

void HardwareSPI::configureBaseDevice() noexcept
{
    InitialiseDMA();
    if(ssp == LPC_SSP0)
    {
        Chip_Clock_SetPCLKDiv(SYSCTL_PCLK_SSP0, SYSCTL_CLKDIV_1); //set SPP peripheral clock to PCLK/1
        Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_SSP0); //enable power and clocking
        AttachDMAChannelInterruptHandler(DMA_USE_DEVICE_INTERRUPT, DMA_SSP0_RX); //attach to the RX complete DMA Intettrupt handler
        NVIC_EnableIRQ(SSP0_IRQn);
    }
    else if (ssp == LPC_SSP1)
    {
        Chip_Clock_SetPCLKDiv(SYSCTL_PCLK_SSP1, SYSCTL_CLKDIV_1); //set SPP peripheral clock to PCLK/1
        Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_SSP1); //enable power and clocking
        AttachDMAChannelInterruptHandler(DMA_USE_DEVICE_INTERRUPT, DMA_SSP1_RX); //attach to the RX complete DMA Intettrupt handler
        NVIC_EnableIRQ(SSP1_IRQn);
    }
}

void HardwareSPI::configureMode(uint32_t deviceMode, uint32_t bits, uint32_t clockMode, uint32_t bitRate) noexcept
{
    Chip_SSP_Set_Mode(ssp, deviceMode);
    Chip_SSP_SetFormat(ssp, bits, SSP_FRAMEFORMAT_SPI, clockMode);
    Chip_SSP_SetBitRate(ssp, bitRate);
    Chip_SSP_DMA_Disable(ssp);
    Chip_SSP_Enable(ssp);    
}

void HardwareSPI::configureDevice(uint32_t deviceMode, uint32_t bits, uint32_t clockMode, uint32_t bitRate, bool hardwareCS) noexcept
{
    disable();
    Chip_SSP_Disable(ssp);
    configureBaseDevice();
    configurePins(hardwareCS);
    configureMode(deviceMode, bits, clockMode, bitRate);
}


//setup the master device.
void HardwareSPI::configureDevice(uint32_t bits, uint32_t clockMode, uint32_t bitRate) noexcept
{
    disable();
    Chip_SSP_Disable(ssp);
    if (needInit)
    {
        configureBaseDevice();
        configurePins(false);
        needInit = false;
    }
    configureMode(SSP_MODE_MASTER, getSSPBits(bits), getSSPMode(clockMode), bitRate);
}


HardwareSPI::HardwareSPI(LPC_SSP_T *sspDevice, Pin* spiPins) noexcept :needInit(true), pins(spiPins)
{
    ssp = sspDevice;    
}

void HardwareSPI::startTransfer(const uint8_t *tx_data, uint8_t *rx_data, size_t len, SPICallbackFunction ioComplete) noexcept
{    
    static uint8_t dontCareRX = 0;
    static uint8_t dontCareTX = 0xFF;
    
    DMA_Channel_t chanRX;
    DMA_Channel_t chanTX;
    
    Chip_SSP_Enable(ssp);    
    
    if(ssp == LPC_SSP0)
    {
        chanRX = DMA_SSP0_RX;
        chanTX = DMA_SSP0_TX;
    }
    else
    {
        chanRX = DMA_SSP1_RX;
        chanTX = DMA_SSP1_TX;
    }
    
    if(rx_data != nullptr)
    {
        SspDmaRxTransfer(chanRX, rx_data, len);
    }
    else
    {
        SspDmaRxTransferNI(chanRX, &dontCareRX, len); //No Increment mode, dont care about received data, overwrite dontCareRX
    }
        
    if(tx_data != nullptr)
    {
        SspDmaTxTransfer(chanTX, tx_data, len);
    }
    else
    {
        SspDmaTxTransferNI(chanTX, &dontCareTX, len); //No Increment mode, send 0xFF
    }
    callback = ioComplete;
    Chip_SSP_DMA_Enable(ssp);
}

void HardwareSPI::stopTransfer() noexcept
{
    Chip_SSP_DMA_Disable(ssp);
    flushRxFifo(ssp);
    flushTxFifo(ssp);
}

spi_status_t HardwareSPI::transceivePacket(const uint8_t *tx_data, uint8_t *rx_data, size_t len) noexcept
{
    waitingTask = xTaskGetCurrentTaskHandle();
    startTransfer(tx_data, rx_data, len, transferComplete);
    spi_status_t ret = SPI_OK;
    const TickType_t xDelay = SPITimeoutMillis / portTICK_PERIOD_MS; //timeout
    if( ulTaskNotifyTake(pdTRUE, xDelay) == 0) // timed out
    {
        ret = SPI_ERROR_TIMEOUT;
    }
    Chip_SSP_DMA_Disable(ssp);
    return ret;
}
