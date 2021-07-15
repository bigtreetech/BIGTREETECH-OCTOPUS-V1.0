
#include "HardwareSDIO.h"
#include "CoreImp.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

extern "C" void debugPrintf(const char* fmt, ...) __attribute__ ((format (printf, 1, 2)));

HardwareSDIO HardwareSDIO::SDIO1;

extern "C" void HAL_SD_TxCpltCallback(SD_HandleTypeDef *hsdio)
{
  TaskBase::GiveFromISR(HardwareSDIO::SDIO1.waitingTask);
}

extern "C" void HAL_SD_RxCpltCallback(SD_HandleTypeDef *hsdio)
{
  TaskBase::GiveFromISR(HardwareSDIO::SDIO1.waitingTask);
}    

extern "C" void DMA2_Stream3_IRQHandler()
{
  HAL_DMA_IRQHandler(&(HardwareSDIO::SDIO1.dmaRx));    
}

extern "C" void DMA2_Stream6_IRQHandler()
{
  HAL_DMA_IRQHandler(&(HardwareSDIO::SDIO1.dmaTx));    
}

extern "C" void HAL_SD_AbortCallback(SD_HandleTypeDef *hsd) {
}

extern "C" void SDIO_IRQHandler()
{
  HAL_SD_IRQHandler(&(HardwareSDIO::SDIO1.hsd));
}

HardwareSDIO::HardwareSDIO() noexcept
{   
}


void HardwareSDIO::initDmaStream(DMA_HandleTypeDef& hdma, DMA_Stream_TypeDef *inst, uint32_t chan, IRQn_Type irq, uint32_t dir, uint32_t minc) noexcept
{
  hdma.Instance                 = inst;
  
  hdma.Init.Channel             = chan;
  hdma.Init.Direction           = dir;
  hdma.Init.PeriphInc           = DMA_PINC_DISABLE;
  hdma.Init.MemInc              = minc;
  hdma.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
  hdma.Init.MemDataAlignment    = DMA_MDATAALIGN_WORD;
  hdma.Init.Mode                = DMA_PFCTRL;
  hdma.Init.Priority            = DMA_PRIORITY_LOW;
  hdma.Init.FIFOMode            = DMA_FIFOMODE_ENABLE;         
  hdma.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
  hdma.Init.MemBurst            = DMA_MBURST_INC4;
  hdma.Init.PeriphBurst         = DMA_PBURST_INC4;
  
  if (HAL_DMA_Init(&hdma) != HAL_OK)
  {
    debugPrintf("SDIO Failed to init DMA\n");
    delay(5000);
  }
  NVIC_EnableIRQ(irq);
}

uint8_t HardwareSDIO::tryInit(bool highspeed) noexcept
{
  uint8_t sd_state = MSD_OK;
  /* HAL SD initialization */
  hsd.Instance = SDIO;
  hsd.Init.ClockEdge = SDIO_CLOCK_EDGE_RISING;
  hsd.Init.ClockBypass = (highspeed ? SDIO_CLOCK_BYPASS_ENABLE : SDIO_CLOCK_BYPASS_DISABLE);
  hsd.Init.ClockPowerSave = SDIO_CLOCK_POWER_SAVE_DISABLE;
  hsd.Init.BusWide = SDIO_BUS_WIDE_1B;
  hsd.Init.HardwareFlowControl = SDIO_HARDWARE_FLOW_CONTROL_DISABLE;
  hsd.Init.ClockDiv = 0;
  sd_state = HAL_SD_Init(&hsd);
  /* Configure SD Bus width (4 bits mode selected) */
  if (sd_state == MSD_OK) {
    /* Enable wide operation */
    if (HAL_SD_ConfigWideBusOperation(&hsd, SDIO_BUS_WIDE_4B) != HAL_OK) {
      debugPrintf("Failed to select wide bus mode highspeed %d\n", highspeed);
      sd_state = MSD_ERROR;
    }
  }

  return sd_state;
}


/**
  * @brief  Initializes the SD card device.
  * @retval SD status
  */
uint8_t HardwareSDIO::Init(void) noexcept
{
  uint8_t sd_state = MSD_OK;
  /* Check if the SD card is plugged in the slot */
  if (IsDetected() != SD_PRESENT) {
    return MSD_ERROR;
  }
  __HAL_RCC_SDIO_CLK_ENABLE();
  pinmap_pinout(PC_8, PinMap_SD);
  pinmap_pinout(PC_9, PinMap_SD);
  pinmap_pinout(PC_10, PinMap_SD);
  pinmap_pinout(PC_11, PinMap_SD);
  pinmap_pinout(PC_12, PinMap_SD);
  pinmap_pinout(PD_2, PinMap_SD);

  NVIC_EnableIRQ(SDIO_IRQn);
  // DMA setup
  __HAL_RCC_DMA2_CLK_ENABLE();
  initDmaStream(dmaRx, DMA2_Stream3, DMA_CHANNEL_4, DMA2_Stream3_IRQn, DMA_PERIPH_TO_MEMORY, DMA_MINC_ENABLE);
  initDmaStream(dmaTx, DMA2_Stream6, DMA_CHANNEL_4, DMA2_Stream6_IRQn, DMA_MEMORY_TO_PERIPH, DMA_MINC_ENABLE);
  __HAL_LINKDMA(&hsd, hdmarx, dmaRx);
  __HAL_LINKDMA(&hsd, hdmatx, dmaTx);
  waitingTask = 0;
  // Some SD cards are not happy writing when using 48MHz
  // so for now we stick with 24.
#if 0
  // try to init in highspeed mode
  sd_state = tryInit(true);
  if (sd_state != MSD_OK)
    // switch to standard speed
    sd_state = tryInit(false);
#else
  sd_state = tryInit(false);
#endif
  return sd_state;
}

/**
  * @brief  Reads block(s) from a specified address in an SD card, in polling mode.
  * @param  pData: Pointer to the buffer that will contain the data to transmit
  * @param  ReadAddr: Address from where data is to be read
  * @param  NumOfBlocks: Number of SD blocks to read
  * @param  Timeout: Timeout for read operation
  * @retval SD status
  */
uint8_t HardwareSDIO::ReadBlocks(uint32_t *pData, uint32_t ReadAddr, uint32_t NumOfBlocks, uint32_t Timeout) noexcept
{
  uint8_t sd_state = MSD_OK;
  uint32_t start = millis();

  while(HAL_SD_GetCardState(&hsd) != HAL_SD_CARD_TRANSFER)
  {
    if (millis() - start > 5000)
    {
      debugPrintf("SDIO Card not ready on read\n");
      return MSD_ERROR;
    }
  }
  
  waitingTask = TaskBase::GetCallerTaskHandle();
  HAL_StatusTypeDef stat = HAL_SD_ReadBlocks_DMA(&hsd, (uint8_t *)pData, ReadAddr, NumOfBlocks);
  if (stat != HAL_OK) {
    debugPrintf("SDIO Read %d len %d error %d code %x\n", (int)ReadAddr, (int)NumOfBlocks, stat, (unsigned)HAL_SD_GetError(&hsd));
    return MSD_ERROR;
  }
  if(!TaskBase::Take(Timeout)) // timed out
  {
      sd_state = MSD_ERROR;
      debugPrintf("SDIO Read SD timeout\n");
  }
  waitingTask = 0;
  return sd_state;
}

/**
  * @brief  Writes block(s) to a specified address in an SD card, in polling mode.
  * @param  pData: Pointer to the buffer that will contain the data to transmit
  * @param  WriteAddr: Address from where data is to be written
  * @param  NumOfBlocks: Number of SD blocks to write
  * @param  Timeout: Timeout for write operation
  * @retval SD status
  */
uint8_t HardwareSDIO::WriteBlocks(uint32_t *pData, uint32_t WriteAddr, uint32_t NumOfBlocks, uint32_t Timeout) noexcept
{
  uint8_t sd_state = MSD_OK;
  uint32_t start = millis();
  while(HAL_SD_GetCardState(&hsd) != HAL_SD_CARD_TRANSFER)
  {
    if (millis() - start > 5000)
    {
      debugPrintf("SDIO Card not ready on write\n");
      return MSD_ERROR;
    }
  }
  waitingTask = TaskBase::GetCallerTaskHandle();
  HAL_StatusTypeDef stat = HAL_SD_WriteBlocks_DMA(&hsd, (uint8_t *)pData, WriteAddr, NumOfBlocks);
  if (stat != HAL_OK) {
    debugPrintf("SDIO Write %d len %d error %d\n", (int)WriteAddr, (int)NumOfBlocks, stat);
    return MSD_ERROR;
  }
  if(!TaskBase::Take(Timeout)) // timed out
  {
      sd_state = MSD_ERROR;
      debugPrintf("SDIO Write SD timeout\n");
  }
  waitingTask = 0;

  return sd_state;
}



/**
  * @brief  Erases the specified memory area of the given SD card.
  * @param  StartAddr: Start byte address
  * @param  EndAddr: End byte address
  * @retval SD status
  */
uint8_t HardwareSDIO::Erase(uint32_t StartAddr, uint32_t EndAddr) noexcept
{
  uint8_t sd_state = MSD_OK;

  if (HAL_SD_Erase(&hsd, StartAddr, EndAddr) != HAL_OK) {
    sd_state = MSD_ERROR;
  }

  return sd_state;
}

/**
  * @brief  Gets the current SD card data status.
  * @param  None
  * @retval Data transfer state.
  *          This value can be one of the following values:
  *            @arg  SD_TRANSFER_OK: No data transfer is acting
  *            @arg  SD_TRANSFER_BUSY: Data transfer is acting
  */
uint8_t HardwareSDIO::GetCardState(void) noexcept
{
  return ((HAL_SD_GetCardState(&hsd) == HAL_SD_CARD_TRANSFER ) ?
    SD_TRANSFER_OK : SD_TRANSFER_BUSY);
}

/**
  * @brief  Get SD information about specific SD card.
  * @param  CardInfo: Pointer to HAL_SD_CardInfoTypedef structure
  * @retval None
  */
void HardwareSDIO::GetCardInfo(HAL_SD_CardInfoTypeDef *CardInfo) noexcept
{
  /* Get SD card Information */
  HAL_SD_GetCardInfo(&hsd, CardInfo);
}


/**
 * @brief  Detects if SD card is correctly plugged in the memory slot or not.
 * @param  None
 * @retval Returns if SD is detected or not
 */
uint8_t HardwareSDIO::IsDetected(void) noexcept
{
  __IO uint8_t status = SD_PRESENT;
  return status;
}