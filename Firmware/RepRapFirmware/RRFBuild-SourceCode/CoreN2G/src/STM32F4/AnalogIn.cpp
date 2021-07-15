/*
 * AnalogInput.cpp
 *
 *  Created 30/7/2020
 *      Author: Andy
 */

/*
Read ADC values. We configure things so that the selected channels are constantly being converted.
Only those channels attached to ADC1 and ADC3 plus a single special case of the MCU temperature device on
ADC1 are currently supported.

Sample timing
We sample continuously up to 16 channels per ADC. We set the ADC clock to APB2/8 and sample each channel for 480 cycles
the conversion time is 12 cycles. This gives a per channel time of...
(480+12)/(84/8) uS = 47uS
Total time for for 16 channels 47*16 = 750uS or approx 1333 full samples per second.
Each channel is oversampled 16 times to increase the resolution by 2 bits to 14 bits
*/
#include <CoreImp.h>
#include <AnalogIn.h>

extern "C" void debugPrintf(const char* fmt, ...) __attribute__ ((format (printf, 1, 2)));

constexpr uint32_t NumADCs = 3;                          // Max supported ADCs
constexpr uint32_t OversampleBits = 2;                   // Number of extra bit of resolution
constexpr uint32_t Oversample = 16;                      // 4^OversampleBits
constexpr uint32_t MaxActiveChannels = 16;               // Max active ADC channels
constexpr uint32_t NumChannelsADC1 = ADC_CHANNEL_VREFINT+1;
constexpr uint32_t NumChannelsADC3 = 16;
constexpr AnalogChannelNumber ADC_1 = 0x10000;
constexpr AnalogChannelNumber ADC_2 = 0x20000;
constexpr AnalogChannelNumber ADC_3 = 0x30000;
constexpr uint32_t NumChannels[NumADCs+1] = {0, NumChannelsADC1, 0, NumChannelsADC3};

static int32_t ChanMap1[NumChannelsADC1];
static int32_t ChanMap3[NumChannelsADC3];
static uint32_t ChanValues[MaxActiveChannels*Oversample];
static constexpr int32_t *ChanMap[NumADCs+1] = {nullptr, ChanMap1, nullptr, ChanMap3};
static uint8_t NumActiveChannels[NumADCs+1] = {0, 0, 0, 0};
static bool Adc1Running = false;
static bool Adc3Running = false;

// Configuration structures for the ADC and Dma
static ADC_HandleTypeDef Adc1Handle = {};
static ADC_HandleTypeDef Adc3Handle = {};
static DMA_HandleTypeDef Dma1Handle = {};
static DMA_HandleTypeDef Dma3Handle = {};

/* Private Functions */
static AnalogChannelNumber GetAdcChannel(PinName pin)
{
    uint32_t function = pinmap_function(pin, PinMap_ADC);
    if (function == static_cast<uint32_t>(NC)) return NO_ADC;
    // we return the ADC number in the high 16 bits and the channel number in the low
    ADC_TypeDef* adc = (ADC_TypeDef *)pinmap_peripheral(pin, PinMap_ADC);

    // We only support ADC3 and ADC1 at the moment
    if (adc == ADC1)
        return (ADC_1 | STM_PIN_CHANNEL(function));
#if 0
    else if (adc == ADC2)
        return (ADC_2 | STM_PIN_CHANNEL(function));
#endif
    else if (adc == ADC3)
        return (ADC_3 | STM_PIN_CHANNEL(function));
    else
    {
        return NO_ADC;
    }
}


static void ConfigureDma(DMA_HandleTypeDef& DmaHandle, DMA_Stream_TypeDef *inst, uint32_t chan )
{
    DmaHandle.Instance = inst;

    DmaHandle.Init.Channel  = chan;
    DmaHandle.Init.Direction = DMA_PERIPH_TO_MEMORY;
    DmaHandle.Init.PeriphInc = DMA_PINC_DISABLE;
    DmaHandle.Init.MemInc = DMA_MINC_ENABLE;
    DmaHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    DmaHandle.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    DmaHandle.Init.Mode = DMA_CIRCULAR;
    DmaHandle.Init.Priority = DMA_PRIORITY_LOW;
    DmaHandle.Init.FIFOMode = DMA_FIFOMODE_DISABLE;         
    DmaHandle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_HALFFULL;
    DmaHandle.Init.MemBurst = DMA_MBURST_SINGLE;
    DmaHandle.Init.PeriphBurst = DMA_PBURST_SINGLE; 

    HAL_DMA_Init(&DmaHandle);
}

/**
  * @brief ADC MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration
  * @param hadc: ADC handle pointer
  * @retval None
  */
void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc)
{
  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* ADC Periph clock enable */
  if (hadc->Instance == ADC1) {
#ifdef __HAL_RCC_ADC1_CLK_ENABLE
    __HAL_RCC_ADC1_CLK_ENABLE();
#endif
#ifdef __HAL_RCC_ADC12_CLK_ENABLE
    __HAL_RCC_ADC12_CLK_ENABLE();
#endif
  }
#ifdef ADC2
  else if (hadc->Instance == ADC2) {
#ifdef __HAL_RCC_ADC2_CLK_ENABLE
    __HAL_RCC_ADC2_CLK_ENABLE();
#endif
#ifdef __HAL_RCC_ADC12_CLK_ENABLE
    __HAL_RCC_ADC12_CLK_ENABLE();
#endif
  }
#endif
#ifdef ADC3
  else if (hadc->Instance == ADC3) {
#ifdef __HAL_RCC_ADC3_CLK_ENABLE
    __HAL_RCC_ADC3_CLK_ENABLE();
#endif
#ifdef __HAL_RCC_ADC34_CLK_ENABLE
    __HAL_RCC_ADC34_CLK_ENABLE();
#endif
#if defined(ADC345_COMMON)
    __HAL_RCC_ADC345_CLK_ENABLE();
#endif
  }
#endif
#ifdef ADC4
  else if (hadc->Instance == ADC4) {
#ifdef __HAL_RCC_ADC34_CLK_ENABLE
    __HAL_RCC_ADC34_CLK_ENABLE();
#endif
#if defined(ADC345_COMMON)
    __HAL_RCC_ADC345_CLK_ENABLE();
#endif
  }
#endif
#ifdef ADC5
  else if (hadc->Instance == ADC5) {
#if defined(ADC345_COMMON)
    __HAL_RCC_ADC345_CLK_ENABLE();
#endif
  }
#endif
#ifdef __HAL_RCC_ADC_CLK_ENABLE
  __HAL_RCC_ADC_CLK_ENABLE();
#endif
  /* For STM32F1xx and STM32H7xx, ADC prescaler is configured in
     SystemClock_Config (variant.cpp) */
#if defined(__HAL_RCC_ADC_CONFIG) && !defined(STM32F1xx) && !defined(STM32H7xx)
  /* ADC Periph interface clock configuration */
  __HAL_RCC_ADC_CONFIG(RCC_ADCCLKSOURCE_SYSCLK);
#endif
}

/**
  * @brief  DeInitializes the ADC MSP.
  * @param  hadc: ADC handle
  * @retval None
  */
void HAL_ADC_MspDeInit(ADC_HandleTypeDef *hadc)
{
#ifdef __HAL_RCC_ADC_FORCE_RESET
  __HAL_RCC_ADC_FORCE_RESET();
#endif
#ifdef __HAL_RCC_ADC_RELEASE_RESET
  __HAL_RCC_ADC_RELEASE_RESET();
#endif

  if (hadc->Instance == ADC1) {
#ifdef __HAL_RCC_ADC1_FORCE_RESET
    __HAL_RCC_ADC1_FORCE_RESET();
#endif
#ifdef __HAL_RCC_ADC1_RELEASE_RESET
    __HAL_RCC_ADC1_RELEASE_RESET();
#endif
#ifdef __HAL_RCC_ADC12_FORCE_RESET
    __HAL_RCC_ADC12_FORCE_RESET();
#endif
#ifdef __HAL_RCC_ADC12_RELEASE_RESET
    __HAL_RCC_ADC12_RELEASE_RESET();
#endif
#ifdef __HAL_RCC_ADC1_CLK_DISABLE
    __HAL_RCC_ADC1_CLK_DISABLE();
#endif
#ifdef __HAL_RCC_ADC12_CLK_DISABLE
    __HAL_RCC_ADC12_CLK_DISABLE();
#endif
  }
#ifdef ADC2
  else if (hadc->Instance == ADC2) {
#ifdef __HAL_RCC_ADC2_FORCE_RESET
    __HAL_RCC_ADC2_FORCE_RESET();
#endif
#ifdef __HAL_RCC_ADC2_RELEASE_RESET
    __HAL_RCC_ADC2_RELEASE_RESET();
#endif
#ifdef __HAL_RCC_ADC12_FORCE_RESET
    __HAL_RCC_ADC12_FORCE_RESET();
#endif
#ifdef __HAL_RCC_ADC12_RELEASE_RESET
    __HAL_RCC_ADC12_RELEASE_RESET();
#endif
#ifdef __HAL_RCC_ADC2_CLK_DISABLE
    __HAL_RCC_ADC2_CLK_DISABLE();
#endif
#ifdef __HAL_RCC_ADC2_CLK_DISABLE
    __HAL_RCC_ADC2_CLK_DISABLE();
#endif
  }
#endif
#ifdef ADC3
  else if (hadc->Instance == ADC3) {
#ifdef __HAL_RCC_ADC3_FORCE_RESET
    __HAL_RCC_ADC3_FORCE_RESET();
#endif
#ifdef __HAL_RCC_ADC3_RELEASE_RESET
    __HAL_RCC_ADC3_RELEASE_RESET();
#endif
#ifdef __HAL_RCC_ADC34_FORCE_RESET
    __HAL_RCC_ADC34_FORCE_RESET();
#endif
#ifdef __HAL_RCC_ADC34_RELEASE_RESET
    __HAL_RCC_ADC34_RELEASE_RESET();
#endif
#ifdef __HAL_RCC_ADC3_CLK_DISABLE
    __HAL_RCC_ADC3_CLK_DISABLE();
#endif
#ifdef __HAL_RCC_ADC34_CLK_DISABLE
    __HAL_RCC_ADC34_CLK_DISABLE();
#endif
#if defined(ADC345_COMMON)
    __HAL_RCC_ADC345_FORCE_RESET();
    __HAL_RCC_ADC345_RELEASE_RESET();
    __HAL_RCC_ADC345_CLK_DISABLE();
#endif
  }
#endif
#ifdef ADC4
  else if (hadc->Instance == ADC4) {
#ifdef __HAL_RCC_ADC34_FORCE_RESET
    __HAL_RCC_ADC34_FORCE_RESET();
#endif
#ifdef __HAL_RCC_ADC34_RELEASE_RESET
    __HAL_RCC_ADC34_RELEASE_RESET();
#endif
#ifdef __HAL_RCC_ADC34_CLK_DISABLE
    __HAL_RCC_ADC34_CLK_DISABLE();
#endif
#if defined(ADC345_COMMON)
    __HAL_RCC_ADC345_FORCE_RESET();
    __HAL_RCC_ADC345_RELEASE_RESET();
    __HAL_RCC_ADC345_CLK_DISABLE();
#endif
  }
#endif
#ifdef ADC5
  else if (hadc->Instance == ADC5) {
#if defined(ADC345_COMMON)
    __HAL_RCC_ADC345_FORCE_RESET();
    __HAL_RCC_ADC345_RELEASE_RESET();
    __HAL_RCC_ADC345_CLK_DISABLE();
#endif
  }
#endif
#ifdef __HAL_RCC_ADC_CLK_DISABLE
  __HAL_RCC_ADC_FORCE_RESET();
  __HAL_RCC_ADC_RELEASE_RESET();
  __HAL_RCC_ADC_CLK_DISABLE();
#endif
}


static void ConfigureAdc(ADC_HandleTypeDef& AdcHandle, ADC_TypeDef *inst, uint32_t chanCount)
{
    // Adc converts channels, continuously and
    // captured to RAM via DMA
    AdcHandle.Instance = inst;
    // consider using ADC_CLOCK_SYNC_PCLK_DIV8
    AdcHandle.Init.ClockPrescaler        = ADC_CLOCK_SYNC_PCLK_DIV8;      /* (A)synchronous clock mode, input ADC clock divided */
    AdcHandle.Init.Resolution            = ADC_RESOLUTION_12B;            /* 12-bit resolution for converted data */
    AdcHandle.Init.DataAlign             = ADC_DATAALIGN_RIGHT;           /* Right-alignment for converted data */
    AdcHandle.Init.ScanConvMode          = ENABLE;                        /* Sequencer Enabled */
    AdcHandle.Init.EOCSelection          = DISABLE;                       /* EOC flag picked-up to indicate conversion end */
#if !defined(STM32F1xx) && !defined(STM32F2xx) && !defined(STM32F4xx) && \
    !defined(STM32F7xx) && !defined(STM32F373xC) && !defined(STM32F378xx)
    AdcHandle.Init.LowPowerAutoWait      = DISABLE;                       /* Auto-delayed conversion feature disabled */
#endif
#if !defined(STM32F1xx) && !defined(STM32F2xx) && !defined(STM32F3xx) && \
    !defined(STM32F4xx) && !defined(STM32F7xx) && !defined(STM32G4xx) && \
    !defined(STM32H7xx) && !defined(STM32L4xx) && !defined(STM32WBxx)
    AdcHandle.Init.LowPowerAutoPowerOff  = DISABLE;                       /* ADC automatically powers-off after a conversion and automatically wakes-up when a new conversion is triggered */
#endif
#ifdef ADC_CHANNELS_BANK_A
    AdcHandle.Init.ChannelsBank          = ADC_CHANNELS_BANK_A;
#endif
    AdcHandle.Init.ContinuousConvMode    = ENABLE;                        /* Continuous mode enabled */
#if !defined(STM32F0xx) && !defined(STM32L0xx)
    AdcHandle.Init.NbrOfConversion       = chanCount;                     /* Specifies the number of ranks that will be converted within the regular group sequencer. */
#endif
    AdcHandle.Init.DiscontinuousConvMode = DISABLE;                       /* Disable discontinuous mode */
#if !defined(STM32F0xx) && !defined(STM32G0xx) && !defined(STM32L0xx)
    AdcHandle.Init.NbrOfDiscConversion   = 0;                             
#endif
    AdcHandle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    AdcHandle.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T1_CC1;

#if !defined(STM32F1xx)
    //AdcHandle.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE; /* Parameter discarded because software trigger chosen */
#endif
#if !defined(STM32F1xx) && !defined(STM32H7xx) && \
    !defined(STM32F373xC) && !defined(STM32F378xx)
    AdcHandle.Init.DMAContinuousRequests = ENABLE;                        /* DMA continuous mode enabled */
#endif
#ifdef ADC_CONVERSIONDATA_DR
    AdcHandle.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DR;      /* Regular Conversion data stored in DR register only */
#endif
#ifdef ADC_OVR_DATA_OVERWRITTEN
    AdcHandle.Init.Overrun               = ADC_OVR_DATA_OVERWRITTEN;      /* DR register is overwritten with the last conversion result in case of overrun */
#endif
#ifdef ADC_LEFTBITSHIFT_NONE
    AdcHandle.Init.LeftBitShift          = ADC_LEFTBITSHIFT_NONE;         /* No bit shift left applied on the final ADC convesion data */
#endif

#if defined(STM32F0xx)
    AdcHandle.Init.SamplingTimeCommon    = samplingTime;
#endif
#if defined(STM32G0xx)
    AdcHandle.Init.SamplingTimeCommon1   = samplingTime;              /* Set sampling time common to a group of channels. */
    AdcHandle.Init.SamplingTimeCommon2   = samplingTime;              /* Set sampling time common to a group of channels, second common setting possible.*/
    AdcHandle.Init.TriggerFrequencyMode  = ADC_TRIGGER_FREQ_HIGH;
#endif
#if defined(STM32L0xx)
    AdcHandle.Init.LowPowerFrequencyMode = DISABLE;                       /* To be enabled only if ADC clock < 2.8 MHz */
    AdcHandle.Init.SamplingTime          = samplingTime;
#endif
#if !defined(STM32F0xx) && !defined(STM32F1xx) && !defined(STM32F2xx) && \
    !defined(STM32F3xx) && !defined(STM32F4xx) && !defined(STM32F7xx) && \
    !defined(STM32L1xx)
    AdcHandle.Init.OversamplingMode      = DISABLE;
  /* Adc3Handle.Init.Oversample ignore for STM32L0xx as oversampling disabled */
  /* Adc3Handle.Init.Oversampling ignored for other as oversampling disabled */
#endif
#if defined(ADC_CFGR_DFSDMCFG) && defined(DFSDM1_Channel0)
    AdcHandle.Init.DFSDMConfig           = ADC_DFSDM_MODE_DISABLE;        /* ADC conversions are not transferred by DFSDM. */
#endif
#ifdef ADC_TRIGGER_FREQ_HIGH
    AdcHandle.Init.TriggerFrequencyMode  = ADC_TRIGGER_FREQ_HIGH;
#endif

    AdcHandle.State = HAL_ADC_STATE_RESET;
    AdcHandle.Lock = HAL_UNLOCKED;
    /* Some other ADC_HandleTypeDef fields exists but not required */
    if (HAL_ADC_Init(&AdcHandle) != HAL_OK) 
    {
        debugPrintf("ADC Init failed\n");
        return;
    }
}

static uint32_t GetActiveChannels(int32_t *cm, uint32_t sz)
{
    uint32_t cnt = 0;
    for(uint32_t i = 0; i < sz; i++)
        if (cm[i] != -1)
            cnt++;
    return cnt;
}

static uint32_t AddActiveChannels(ADC_HandleTypeDef& AdcHandle, int32_t *cm, uint32_t sz, uint32_t dataOffset)
{
    ADC_ChannelConfTypeDef  AdcChannelConf = {};
    AdcChannelConf.SamplingTime = ADC_SAMPLETIME_480CYCLES;

    int32_t sampleOffset = 0;
    for(uint32_t i = 0; i < sz; i++)
    {
        if (cm[i] != -1)
        {
            // include this channel
            AdcChannelConf.Channel = i;
            AdcChannelConf.Rank = ++sampleOffset;
            HAL_ADC_ConfigChannel(&AdcHandle, &AdcChannelConf);
            // record the location of the sample
            cm[i] = dataOffset++;
        }
    }
    return dataOffset;
}


static void ConfigureChannels()
{
    // Reset everything
    if (Adc3Running)
    {
        HAL_ADC_Stop_DMA(&Adc3Handle);
        // Unfortunately we can't just restart the DMA as it seems to restart at the same channel
        // it stopped at which causes a skew in the memory contents. I'm not sure what will 
        // reset the ADC to match the DMA transfer, but calling Deinit does the job. Unfortuately
        // it also resets ADC1, so we need to restart that as well!
        HAL_ADC_DeInit(&Adc3Handle);
    }
    if (Adc1Running)
    {
        HAL_ADC_Stop_DMA(&Adc1Handle);
        HAL_ADC_DeInit(&Adc1Handle);
    }
    uint32_t Active3 = GetActiveChannels(ChanMap3, NumChannelsADC3);
    uint32_t Active1 = GetActiveChannels(ChanMap1, NumChannelsADC1);
    if (Active3 + Active1 > MaxActiveChannels)
    {
        debugPrintf("Too many active ADC channels\n");
        return;
    }
    if (Active3 > 0)
    {
        __HAL_RCC_ADC3_CLK_ENABLE();
        // setup the ADC for that number of channels
        ConfigureAdc(Adc3Handle, ADC3, Active3);
        AddActiveChannels(Adc3Handle, ChanMap3, NumChannelsADC3, Active1*Oversample);
        // All done restart sampling
        HAL_ADC_Start_DMA(&Adc3Handle, ChanValues + Active1*Oversample, Active3*Oversample);
        Adc3Running = true;
    }
    NumActiveChannels[3] = Active3;
    if (Active1 > 0)
    {
        __HAL_RCC_ADC1_CLK_ENABLE();
        // setup the ADC for that number of channels
        ConfigureAdc(Adc1Handle, ADC1, Active1);
        AddActiveChannels(Adc1Handle, ChanMap1, NumChannelsADC1, 0);
        // All done restart sampling
        HAL_ADC_Start_DMA(&Adc1Handle, ChanValues, Active1*Oversample);
        Adc1Running = true;
    }
    NumActiveChannels[1] = Active1;
}

namespace LegacyAnalogIn
{
    // Module initialisation
    void AnalogInInit()
    {
        // Initially no channels are mapped
        for(uint32_t i = 0; i < NumChannelsADC1; i++)
            ChanMap1[i] = -1;
        for(uint32_t i = 0; i < NumChannelsADC3; i++)
            ChanMap3[i] = -1;

        __HAL_RCC_DMA2_CLK_ENABLE();
        ConfigureDma(Dma1Handle, DMA2_Stream4, DMA_CHANNEL_0);
        ConfigureDma(Dma3Handle, DMA2_Stream0, DMA_CHANNEL_2);
        __HAL_LINKDMA(&Adc1Handle, DMA_Handle, Dma1Handle);
        __HAL_LINKDMA(&Adc3Handle, DMA_Handle, Dma3Handle);
    }

    // Enable or disable a channel. Use AnalogCheckReady to make sure the ADC is ready before calling this.
    void AnalogInEnableChannel(AnalogChannelNumber channel, bool enable)
    {
        if (channel == NO_ADC) 
        {
            //debugPrintf("Enable bad ADC channel %d\n", static_cast<int>(channel));
            return;
        }
        AnalogChannelNumber AdcNo = (channel >> 16);
        channel &= 0xffff;
        if (AdcNo > NumADCs || channel >= NumChannels[AdcNo])
        {
            debugPrintf("Enable bad ADC channel %d %d\n", static_cast<int>(AdcNo), static_cast<int>(channel));
            return;
        }
        ChanMap[AdcNo][channel] = (enable ? 0 : -1);
        ConfigureChannels();
    }

    // Read the most recent 12-bit result from a channel
    uint16_t AnalogInReadChannel(AnalogChannelNumber channel)
    {
        if (channel == NO_ADC)
            return 0;
        AnalogChannelNumber AdcNo = (channel >> 16);
        channel &= 0xffff;
        uint32_t *pSamples;
        uint32_t step;
        if (AdcNo > NumADCs || channel >= NumChannels[AdcNo])
        {
            debugPrintf("Read bad ADC channel %d %d\n", static_cast<int>(AdcNo), static_cast<int>(channel));
            return 0;
        }
        pSamples = &ChanValues[ChanMap[AdcNo][channel]];
        step = NumActiveChannels[AdcNo];
        uint32_t val = 0;
        for(uint32_t i = 0; i < Oversample; i++)
        {
            val += *pSamples;
            pSamples += step;
        }
        // decimate
        return val >> OversampleBits;
    }


    // Start converting the enabled channels
    void AnalogInStartConversion(uint32_t channels)
    {

    }




    // Finalise a conversion
//    void AnalogInFinaliseConversion()
//    {

//    }


    // Check whether all conversions have been completed since the last call to AnalogStartConversion
    bool AnalogInCheckReady(uint32_t channels)
    {
        return true;
    }

    // Convert an Arduino Due analog pin number to the corresponding ADC channel number
    AnalogChannelNumber PinToAdcChannel(uint32_t pin)
    {
        return GetAdcChannel(static_cast<PinName>(pin));
    }

    // Get the temperature measurement channel
    AnalogChannelNumber GetTemperatureAdcChannel()
    {
        return (ADC_1 | ADC_CHANNEL_TEMPSENSOR);
    }

    // Get the temperature measurement channel
    AnalogChannelNumber GetVREFAdcChannel()
    {
        return (ADC_1 | ADC_CHANNEL_VREFINT);
    }
}
// End
