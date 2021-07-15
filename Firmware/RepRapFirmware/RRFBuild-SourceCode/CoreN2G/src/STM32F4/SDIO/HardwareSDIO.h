#ifndef __HARDWARESDIO_H
#define __HARDWARESDIO_H
#include "Core.h"
#include "FreeRTOS.h"
#include "task.h"
#include "RTOSIface/RTOSIface.h"


#define SD_PRESENT               ((uint8_t)0x01)
#define SD_NOT_PRESENT           ((uint8_t)0x00)

#define MSD_OK                   ((uint8_t)0x00)
#define MSD_ERROR                ((uint8_t)0x01)
#define SD_TRANSFER_OK           ((uint8_t)0x00)
#define SD_TRANSFER_BUSY         ((uint8_t)0x01)
#define SD_PRESENT               ((uint8_t)0x01)
#define SD_NOT_PRESENT           ((uint8_t)0x00)
#define SD_DATATIMEOUT           ((uint32_t)100000000)
extern "C" void DMA2_Stream6_IRQHandler(void);
extern "C" void DMA2_Stream3_IRQHandler(void);
extern "C" void SDIO_IRQHandler(void);
extern "C" void HAL_SD_TxCpltCallback(SD_HandleTypeDef *hsdio);
extern "C" void HAL_SD_RxCpltCallback(SD_HandleTypeDef *hsdio);

class HardwareSDIO
{
public:
    HardwareSDIO() noexcept;

    uint8_t Init(void) noexcept;
    uint8_t ReadBlocks(uint32_t *pData, uint32_t ReadAddr, uint32_t NumOfBlocks, uint32_t Timeout) noexcept;
    uint8_t WriteBlocks(uint32_t *pData, uint32_t WriteAddr, uint32_t NumOfBlocks, uint32_t Timeout) noexcept;
    uint8_t Erase(uint32_t StartAddr, uint32_t EndAddr) noexcept;
    uint8_t GetCardState(void) noexcept;
    void GetCardInfo(HAL_SD_CardInfoTypeDef *CardInfo) noexcept;
    uint8_t IsDetected(void) noexcept;
    static HardwareSDIO SDIO1;

private:
    void initDmaStream(DMA_HandleTypeDef& hdma, DMA_Stream_TypeDef *inst, uint32_t chan, IRQn_Type irq, uint32_t dir, uint32_t minc) noexcept;
    uint8_t tryInit(bool highspeed) noexcept;
    SD_HandleTypeDef hsd;
    DMA_HandleTypeDef dmaRx;
    DMA_HandleTypeDef dmaTx;
    TaskHandle waitingTask;

    friend void DMA2_Stream6_IRQHandler();
    friend void DMA2_Stream3_IRQHandler();
    friend void HAL_SD_TxCpltCallback(SD_HandleTypeDef *hsdio);
    friend void HAL_SD_RxCpltCallback(SD_HandleTypeDef *hsdio);
    friend void SDIO_IRQHandler();
};

#endif
