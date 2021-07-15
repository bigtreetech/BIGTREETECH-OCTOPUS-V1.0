/*
 * TMCSoftUart.cpp
 * Software UART implementations for TMC22XX chips for the LPC17XX MCU.
 * 
 * Note: The DMA version of this code is based upon an original implementation from Artem-B:
 * https://github.com/Artem-B/TMC2208Stepper/tree/soft-uart
 * However this version differs considerably to avoid problems with the original implementation
 * and in particular to allow it to run without disabling interrupts during operation.
 * 
 * This version re-worked for STM32 DMA controllers.
 * 
 *  Created on: 1 Aug 2020
 *      Author: gloomyandy
 */

#include "RepRapFirmware.h"

#if SUPPORT_TMC22xx
#include "TMCSoftUART.h"
#include "TMC22xx.h"
#include "Platform/RepRap.h"
#include "HardwareTimer.h"
#include "Movement/Move.h"
#include "Movement/StepTimer.h"
#include "Cache.h"

// Soft UART implementation
#if TMC_SOFT_UART

#define SU_OVERSAMPLE 4

static constexpr uint32_t SU_BAUD_RATE = DriversBaudRate;
static constexpr uint32_t SU_MAX_BYTES = 8;
static constexpr uint32_t SU_GAP_BYTES = 1;
static constexpr uint32_t SU_GAP_BITS = 4;
static constexpr uint32_t SU_FRAME_LENGTH = 10;
static constexpr uint32_t SU_MAX_RETRY = 0;

enum class SUStates
{
	idle,
	writing,
	reading,
	complete,
	error
};
static volatile SUStates SUState = SUStates::idle;
static HardwareTimer SUTimer(TIM1);
static Pin SUPin;
static volatile uint32_t *SUPinSetClrPtr;
static volatile uint32_t *SUPinReadPtr;
static uint32_t SUPinBit;
static uint32_t SUSetBit;
static uint32_t SUClrBit;
static uint32_t SUWriteCnt;
static uint8_t* SUWritePtr;
static uint32_t SUReadCnt;
static uint8_t* SUReadPtr;
static uint32_t SUBitCnt;
DMA_HandleTypeDef SUDma;
static uint32_t SUPeriod;

uint32_t SUDmaBits[((SU_MAX_BYTES+SU_GAP_BYTES)*SU_FRAME_LENGTH)*SU_OVERSAMPLE];

static void SetupPins()
{
    GPIO_TypeDef *port = get_GPIO_Port(STM_PORT(SUPin));
    uint32_t pinNo = STM_PIN(SUPin);
    SUPinSetClrPtr = &(port->BSRR);
    SUPinBit = 1 << pinNo;
    SUSetBit = SUPinBit;
    SUClrBit = SUPinBit << 16;
    SUPinReadPtr = &(port->IDR);
}

static void WriteByte(uint8_t val)
{
    // place one bye of data into the DMA buffer
    // Start bit
    SUDmaBits[SUBitCnt++] = SUClrBit;
    // data bits
    for(int i = 0; i < 8; i++)
    {
        if (val & 1)
            SUDmaBits[SUBitCnt++] = SUSetBit;
        else
            SUDmaBits[SUBitCnt++] = SUClrBit;
        val >>= 1;
    }
    // stop bit
    SUDmaBits[SUBitCnt++] = SUSetBit;
}

static uint32_t DecodeBytes(uint8_t *outp, uint32_t outlen)
{
    // Take an in memory oversampled capture of the output from the TMC22XX device, down sample
    // it and extract the original data bytes.
    uint32_t inlen = (outlen + SU_GAP_BYTES)*SU_FRAME_LENGTH*SU_OVERSAMPLE;
    uint32_t mask = SUPinBit;
    uint8_t data;
    uint32_t outcnt = 0;
    uint32_t outbit = 0;
    int lastedge = 0;
    int midpoint = (SU_OVERSAMPLE + 1)/2;
    bool lastbit = (SUDmaBits[lastedge + midpoint] & mask) != 0;
    for(uint32_t i = 0; i < inlen; i++)
    {
        bool thisbit = (SUDmaBits[lastedge + midpoint] & mask) != 0;
        // process the current bit
        if (outbit == 0)
        {
            // start bit must be zero
            if (!thisbit)
            {
                data = 0;
                outbit = 1;
            } 
        } 
        else if (++outbit < SU_FRAME_LENGTH)
        {
            // data bits
            data >>= 1;
            if (thisbit)
                data |= 0x80;
        }
        else if (thisbit)
        {
            // got valid stop bit, data byte complete
            *outp++ = data;
            if (++outcnt >= outlen)
                break;
            outbit = 0;
        }
        else
            // invalid stop bit, give up
            break; 

        if (thisbit != lastbit) 
        {
            // Bit flipped. Resync last_edge.
            lastedge += midpoint;
            while(((SUDmaBits[lastedge] & mask) != 0) == thisbit)
                lastedge--;
            lastedge++;
        }
        // Advance to the (expected) edge of the next bit.
        lastedge += SU_OVERSAMPLE;
        lastbit = thisbit;       
    }
    return outcnt;
}

static void DmaInterrupt(DMA_HandleTypeDef *_hdma)
{
    switch(SUState)
    {
    case SUStates::idle:
        break;
    case SUStates::writing:
        // we get called at the end of writing
        SUTimer.pause();
        pinMode(SUPin, INPUT_PULLUP);
        SUDma.Init.Direction = DMA_PERIPH_TO_MEMORY;
        HAL_DMA_Start_IT(&SUDma, (uint32_t)SUPinReadPtr, (uint32_t)SUDmaBits, sizeof(SUDmaBits)/sizeof(uint32_t));
    	SUTimer.setOverflow(SUPeriod - 1, TICK_FORMAT);
        SUTimer.setCount(0, TICK_FORMAT);
	    SUState = SUStates::reading;
        SUTimer.resume();
        break;
    case SUStates::reading:
        // Last bit of read operation captured
        SUTimer.pause();
        SUState = SUStates::complete;
        pinMode(SUPin, OUTPUT_HIGH);
        break;
    case SUStates::complete:
    case SUStates::error:
        break;
    }
}

static void DmaStart()
{
    uint8_t *p = SUWritePtr;
    SUBitCnt = 0;
    // The timing of the first stop bit is critical as it sets the timing of the remaining bits
    // to ensure this is as accurate as possible we insert a number of dummy high bits before
    // the first start bit.
    for(uint32_t i = 0; i < SU_GAP_BITS; i++)
        SUDmaBits[SUBitCnt++] = SUSetBit;
    // Pre buffer the write data
    for(uint32_t i = 0; i < SUWriteCnt; i++)
    {
        WriteByte(*p++);
    }
    // The TMC driver will wait for 8 bits of time before sending the reply. We pad the output
    // data by half of this time.
    for(uint32_t i = 0; i < SU_GAP_BITS; i++)
        SUDmaBits[SUBitCnt++] = SUSetBit;
    pinMode(SUPin, OUTPUT_HIGH);
    SUDma.Init.Direction = DMA_MEMORY_TO_PERIPH;
    HAL_DMA_Start_IT(&SUDma, (uint32_t)SUDmaBits, (uint32_t)SUPinSetClrPtr, SUBitCnt);
	SUTimer.setOverflow(SUPeriod*SU_OVERSAMPLE - 1, TICK_FORMAT);
    SUTimer.setCount(0, TICK_FORMAT);
	SUState = SUStates::writing;
    SUTimer.resume();
}


void TMCSoftUARTAbort() noexcept
{
	SUState = SUStates::idle;
	if (SUPin != NoPin)
    	pinMode(SUPin, OUTPUT_HIGH);
}

void TMCSoftUARTStartTransfer(uint8_t driver, volatile uint8_t *WritePtr, uint32_t WriteCnt, volatile uint8_t *ReadPtr, uint32_t ReadCnt) noexcept
{
	SUPin = TMC_PINS[driver];
	if (SUPin != NoPin)
	{
        SetupPins();
        SUWritePtr = (uint8_t *)WritePtr;
        SUWriteCnt = WriteCnt;
        SUReadPtr = (uint8_t *)ReadPtr;
        SUReadCnt = ReadCnt;
        DmaStart();
	}
}

bool TMCSoftUARTCheckComplete() noexcept
{
	if (SUState == SUStates::complete)
	{
        pinMode(SUPin, OUTPUT_HIGH);
		SUState = SUStates::idle;
        uint32_t cnt = DecodeBytes(SUReadPtr, SUReadCnt);
        if (cnt <= 0 || cnt != SUReadCnt)
        {
            //debugPrintf("SU read error expected %d got %d retry %d\n", SUReadCnt, cnt, SURetryCnt);
            // data error
            return false;
        }
		// I/O complete
        return true;
	}
    return false;
}

void TMCSoftUARTInit() noexcept
{
    uint32_t period = SUTimer.getTimerClkFreq()/(SU_BAUD_RATE*SU_OVERSAMPLE);
	//debugPrintf("SU base freq %d setting period %d\n", static_cast<int>(SUTimer.getTimerClkFreq()), static_cast<int>(period));
    SUPeriod = period;
	SUTimer.setOverflow(period*SU_OVERSAMPLE, TICK_FORMAT);
    SUTimer.setCount(0, TICK_FORMAT);
    __HAL_TIM_ENABLE_DMA(&(HardwareTimer_Handle[get_timer_index(TIM1)]->handle), TIM_DMA_UPDATE);
    __HAL_RCC_DMA2_CLK_ENABLE();    
    SUDma.Instance                 = DMA2_Stream5;
    SUDma.Init.Channel             = DMA_CHANNEL_6;
    SUDma.Init.Direction           = DMA_MEMORY_TO_PERIPH;
    SUDma.Init.PeriphInc           = DMA_PINC_DISABLE;
    SUDma.Init.MemInc              = DMA_MINC_ENABLE;
    SUDma.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    SUDma.Init.MemDataAlignment    = DMA_MDATAALIGN_WORD;
    SUDma.Init.Mode                = DMA_NORMAL;
    SUDma.Init.Priority            = DMA_PRIORITY_VERY_HIGH;
    SUDma.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;         
    SUDma.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
    SUDma.Init.MemBurst            = DMA_MBURST_SINGLE;
    SUDma.Init.PeriphBurst         = DMA_PBURST_SINGLE;
    HAL_DMA_Init(&SUDma);
    HAL_DMA_RegisterCallback(&SUDma, HAL_DMA_XFER_CPLT_CB_ID, DmaInterrupt);
	for(size_t i = 0; i < NumDirectDrivers; i++)
		if (TMC_PINS[i] != NoPin)
			pinMode(TMC_PINS[i], OUTPUT_HIGH);

	SUPin = NoPin;
	SUState = SUStates::idle;
    NVIC_EnableIRQ(DMA2_Stream5_IRQn);
}

void TMCSoftUARTShutdown() noexcept
{
	TMCSoftUARTAbort();
}


extern "C" void DMA2_Stream5_IRQHandler()
{
    HAL_DMA_IRQHandler(&SUDma);    
}

#endif
#endif
