/*
 * FreeRTOS+TCP V2.0.1
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

//SD: Created New LPC17xx driver (adapted from the LPC18xx driver) with zero_copy


/* Standard includes. */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

/* FreeRTOS+TCP includes. */
#include "FreeRTOS_IP.h"
#include "FreeRTOS_Sockets.h"
#include "FreeRTOS_IP_Private.h"
#include "NetworkBufferManagement.h"
#include "NetworkInterface.h"

/* @brief Function prototype for a MS delay function. Board layers or example code may
*        define this function as needed.
*/
typedef void (*p_msDelay_func_t)(uint32_t);


TaskHandle_t RRfInitialiseEMACTask(TaskFunction_t pxTaskCode); // defined in RTOSPlusTCPEthernetInterface

//****************

/* LPCOpen includes. */

#include "chip.h"
#include "enet_17xx_40xx.h"
#include "lpc_phy.h"

#ifndef    EMAC_MAX_BLOCK_TIME_MS
    #define    EMAC_MAX_BLOCK_TIME_MS    100ul
#endif

#ifndef	PHY_LS_HIGH_CHECK_TIME_MS
	/* Check if the LinkSStatus in the PHY is still high after 5 seconds of not
	receiving packets. */
	#define PHY_LS_HIGH_CHECK_TIME_MS	5000
#endif

#ifndef	PHY_LS_LOW_CHECK_TIME_MS
	/* Check if the LinkSStatus in the PHY is still low every second. */
	#define PHY_LS_LOW_CHECK_TIME_MS	1000
#endif

#ifndef configUSE_RMII
	#define configUSE_RMII 1
#endif

#ifndef configNUM_RX_DESCRIPTORS
	#error please define configNUM_RX_DESCRIPTORS in your FreeRTOSIPConfig.h
#endif

#ifndef configNUM_TX_DESCRIPTORS
	#error please define configNUM_TX_DESCRIPTORS in your FreeRTOSIPConfig.h
#endif

#ifndef NETWORK_IRQHandler
	#error NETWORK_IRQHandler must be defined to the name of the function that is installed in the interrupt vector table to handle Ethernet interrupts.
#endif

#ifndef iptraceEMAC_TASK_STARTING
	#define iptraceEMAC_TASK_STARTING()	do { } while( 0 )
#endif

///* Define the bits of .StatusInfo that indicate a reception error. */
// Status bits:
//ENET_RINFO_SIZE(n)            Data size in bytes
//ENET_RINFO_CTRL_FRAME         Control Frame
//ENET_RINFO_VLAN               VLAN Frame
//ENET_RINFO_FAIL_FILT          RX Filter Failed
//ENET_RINFO_MCAST              Multicast Frame
//ENET_RINFO_BCAST              Broadcast Frame
//ENET_RINFO_CRC_ERR            CRC Error in Frame
//ENET_RINFO_SYM_ERR            Symbol Error from PHY
//ENET_RINFO_LEN_ERR            Length Error
//ENET_RINFO_RANGE_ERR          Range Error (exceeded max. size)
//ENET_RINFO_ALIGN_ERR          Alignment Error
//ENET_RINFO_OVERRUN            Receive overrun
//ENET_RINFO_NO_DESCR           No new Descriptor available
//ENET_RINFO_LAST_FLAG          Last Fragment in Frame
//ENET_RINFO_ERR                Error Occured (OR of all errors)

#define nwRX_STATUS_ERROR_BITS \
    (   ENET_RINFO_CRC_ERR | \
        ENET_RINFO_SYM_ERR | \
        ENET_RINFO_LEN_ERR | \
        ENET_RINFO_ALIGN_ERR | \
        ENET_RINFO_OVERRUN )


/* Define the EMAC status bits that should trigger an interrupt. */
#define nwDMA_INTERRUPT_MASK \
(\
    ENET_INT_RXOVERRUN      /* Overrun Error in RX Queue */   | \
    ENET_INT_RXERROR        /* Receive Error */               | \
    ENET_INT_RXDONE         /* Receive Done */                | \
    ENET_INT_TXUNDERRUN     /* Transmit Underrun */           | \
    ENET_INT_TXERROR        /* Transmit Error */              | \
    ENET_INT_TXDONE )        /* Transmit Done */

//Other Interrupt Triggers available:
//ENET_INT_RXFINISHED     /* RX Finished Process Descriptors */
//ENET_INT_TXFINISHED     /* TX Finished Process Descriptors */
//ENET_INT_SOFT           /* Software Triggered Interrupt */
//ENET_INT_WAKEUP         /* Wakeup Event Interrupt */


/* Interrupt events to process.  Currently only the RX/TX events are processed
although code for other events is included to allow for possible future
expansion. */
#define EMAC_IF_RX_EVENT        1UL
#define EMAC_IF_TX_EVENT        2UL
#define EMAC_IF_ERR_EVENT       4UL
#define EMAC_IF_ALL_EVENT       ( EMAC_IF_RX_EVENT | EMAC_IF_TX_EVENT | EMAC_IF_ERR_EVENT )



 /* If ipconfigETHERNET_DRIVER_FILTERS_FRAME_TYPES is set to 1, then the Ethernet
 driver will filter incoming packets and only pass the stack those packets it
 considers need processing. */
#if ipconfigETHERNET_DRIVER_FILTERS_FRAME_TYPES == 0
    #define ipCONSIDER_FRAME_FOR_PROCESSING( pucEthernetBuffer ) eConsiderFrameForProcessing( ( pucEthernetBuffer ) )
#else
    #define ipCONSIDER_FRAME_FOR_PROCESSING( pucEthernetBuffer ) eProcessBuffer
#endif

#if( ipconfigZERO_COPY_RX_DRIVER == 0 ) || ( ipconfigZERO_COPY_TX_DRIVER == 0 )
	#error This is a zero copy driver only
#endif

#if( configUSE_RMII != 1 )
    #error This driver assumes RMII
#endif

#ifndef configPLACE_IN_SECTION_RAM
	#define configPLACE_IN_SECTION_RAM
/*
	#define configPLACE_IN_SECTION_RAM	__attribute__ ((section(".ramfunc")))
*/
#endif

/*-----------------------------------------------------------*/

/*
 * Delay function passed into the library.  The implementation uses FreeRTOS
 * calls so the scheduler must be started before the driver can be used.
 */
static void prvDelay( uint32_t ulMilliSeconds );

/*
 * Initialises the Tx and Rx descriptors respectively.
 */
static void prvSetupTxDescriptors( void );
static void prvSetupRxDescriptors( void );

/*
 * A task that processes received frames.
 */
static void prvEMACHandlerTask( void *pvParameters );

/*
 * Sets up the MAC with the results of an auto-negotiation.
 */
static BaseType_t prvSetLinkSpeed( void );

/*
 * Sometimes the DMA will report received data as being longer than the actual
 * received from length.  This function checks the reported length and corrects
 * if if necessary.
 */
static void prvRemoveTrailingBytes( NetworkBufferDescriptor_t *pxDescriptor );

/*-----------------------------------------------------------*/

/* Bit map of outstanding ETH interrupt events for processing.  Currently only
the Rx and Tx interrupt is handled, although code is included for other events
to enable future expansion. */
static volatile uint32_t ulISREvents = 0;

/* A copy of PHY register 1: 'PHY_REG_01_BMSR' */
uint32_t ulPHYLinkStatus = 0;

/* Tx descriptors and index. */
//SD:TX Descriptors and Statuses
//SD:: Manual states that base address of Descriptors are to be 4 byte aligned. Base address of statuses are to be 8 byte aligned
static __attribute__ ((used,section("AHBSRAM0"))) ENET_TXDESC_T xDMATxDescriptors[ configNUM_TX_DESCRIPTORS ] __attribute__ ( ( aligned( 4 ) ) );
static __attribute__ ((used,section("AHBSRAM0"))) ENET_TXSTAT_T xDMATxStatuses[ configNUM_TX_DESCRIPTORS ] __attribute__ ( ( aligned( 8 ) ) );

/* ulNextFreeTxDescriptor is declared volatile, because it is accessed from
to different tasks. */
static volatile uint32_t ulNextFreeTxDescriptor;
static uint32_t ulTxDescriptorToClear;

/* Rx descriptors and index. */
//SD:RX Descriptors and Statuses are seperated
static __attribute__ ((used,section("AHBSRAM0"))) ENET_RXDESC_T xDMARxDescriptors[ configNUM_RX_DESCRIPTORS ] __attribute__ ( ( aligned( 4 ) ) );
static __attribute__ ((used,section("AHBSRAM0"))) ENET_RXSTAT_T xDMARxStatuses[ configNUM_RX_DESCRIPTORS ] __attribute__ ( ( aligned( 8 ) ) );

/* The handle of the task that processes Rx packets.  The handle is required so
the task can be notified when new packets arrive. */
static TaskHandle_t xRxHanderTask = NULL;

/* xTXDescriptorSemaphore is a counting semaphore with
a maximum count of configNUM_TX_DESCRIPTORS, which is the number of
DMA TX descriptors. */
static SemaphoreHandle_t xTXDescriptorSemaphore = NULL;

///Debugging
#if defined(COLLECT_NETDRIVER_ERROR_STATS)
    uint32_t numNetworkDroppedRXPacketsDueToNoBuffer = 0;
    uint32_t numNetworkDroppedTXPacketsDueToNoBuffer = 0;

    volatile uint32_t numNetworkRXIntOverrunErrors = 0; //hardware producted overrun error
    uint32_t numNetworkCRCErrors = 0; //ENET_RINFO_CRC_ERR
    uint32_t numNetworkSYMErrors = 0; //ENET_RINFO_SYM_ERR
    uint32_t numNetworkLENErrors = 0; //ENET_RINFO_LEN_ERR
    uint32_t numNetworkALIGNErrors = 0; //ENET_RINFO_ALIGN_ERR
    uint32_t numNetworkOVERRUNErrors = 0; //ENET_RINFO_OVERRUN

    uint32_t numRejectedStackPackets = 0; //number packets rejected by the TCP/IP stack
#endif

/*-----------------------------------------------------------*/






BaseType_t xNetworkInterfaceInitialise( void )
{
    BaseType_t xReturn = pdPASS;
    static BaseType_t xHasHWInitialised = pdFALSE;
    
	if( xHasHWInitialised == pdFALSE )
	{
		xHasHWInitialised = pdTRUE;
        
		NVIC_DisableIRQ( ETHERNET_IRQn );

        Chip_ENET_Init(LPC_ETHERNET, true); //init RMII
        
        //by default Chip_ENET_Init will set frame size to max it can handle
        //so we will set if based on the value we get from +TCP
        LPC_ETHERNET->MAC.MAXF = ipTOTAL_ETHERNET_FRAME_SIZE;

        /* Setup MII clock rate and PHY address */
        Chip_ENET_SetupMII(LPC_ETHERNET, Chip_ENET_FindMIIDiv(LPC_ETHERNET, 2500000), 1);

        /* Save MAC address. */
		Chip_ENET_SetADDR( LPC_ETHERNET, FreeRTOS_GetMACAddress() );

        /* Clear all MAC address hash entries. */
        LPC_ETHERNET->RXFILTER.HashFilterH = 0;
        LPC_ETHERNET->RXFILTER.HashFilterL = 0;
        
        /* Initialise the descriptors. */
        prvSetupTxDescriptors();
        prvSetupRxDescriptors();

        /* lpc17xx Enable RX/TX after descriptors are setup */
        Chip_ENET_TXEnable(LPC_ETHERNET);
        Chip_ENET_RXEnable(LPC_ETHERNET);
        
        //Accept perfect match and broadcast frames
        Chip_ENET_EnableRXFilter(LPC_ETHERNET, ENET_RXFILTERCTRL_APE | ENET_RXFILTERCTRL_ABE);

        /* Enable MAC interrupts. */
        Chip_ENET_EnableInt(LPC_ETHERNET, nwDMA_INTERRUPT_MASK);
        
        uint8_t retry = 3;
        while(retry > 0)
        {
            if( lpc_phy_init( pdTRUE, prvDelay ) == SUCCESS )
            {
                break;
            }
            
            prvDelay(100);
            retry--;
        }

        /* Auto-negotiate was already started.  Wait for it to complete. */
        xReturn = prvSetLinkSpeed();
        
        if( xTXDescriptorSemaphore == NULL )
        {
            /* Create a counting semaphore, with a value of 'configNUM_TX_DESCRIPTORS'
            and a maximum of 'configNUM_TX_DESCRIPTORS'. */
            xTXDescriptorSemaphore = xSemaphoreCreateCounting( ( UBaseType_t ) configNUM_TX_DESCRIPTORS, ( UBaseType_t ) configNUM_TX_DESCRIPTORS );
            configASSERT( xTXDescriptorSemaphore );
        }

        /* Guard against the task being created more than once and the
        descriptors being initialised more than once. */
        if( xRxHanderTask == NULL )
        {
            //xReturn = xTaskCreate( prvEMACHandlerTask, "EMAC", nwRX_TASK_STACK_SIZE, NULL, configMAX_PRIORITIES - 1, &xRxHanderTask );
            xRxHanderTask = RRfInitialiseEMACTask(prvEMACHandlerTask);
            configASSERT( xRxHanderTask != NULL ); // ensure the Task was created
            
            /* Enable interrupts in the NVIC now the task is created. */
            NVIC_SetPriority( ETHERNET_IRQn, configMAC_INTERRUPT_PRIORITY );
            NVIC_EnableIRQ( ETHERNET_IRQn );
        }
    }

	/* Once prvEMACHandlerTask() has started, the variable
	'ulPHYLinkStatus' will be updated by that task. 
	The IP-task will keep on calling this function untill
	it finally returns pdPASS.
	Only then can the DHCP-procedure start (if configured). */
	if( ( ulPHYLinkStatus & PHY_LINK_CONNECTED ) != 0 )
	{
		xReturn = pdPASS;
        static bool firstInit = true;
        if(firstInit)
        {
            /*
             Note: From Errata sheet Rev. 10.4 — 17 March 2020
             
             The TxConsumeIndex register is not updated correctly (from 0 to 1) after the first frame is sent.
             After the next frame sent, the TxConsumeIndex register is updated by two (from 0 to 2).
             This only happens the very first time, so subsequent updates are correct (even those from 0 to 1,
             after wrapping the value to 0 once the value of TxDescriptorNumber has been reached
            
             Work-around:
             Software can correct this situation in many ways; for example, sending a dummy frame after initialization.
             */
            
            //send a dummy frame
            NetworkBufferDescriptor_t *pxNetworkBuffer = pxGetNetworkBufferWithDescriptor( 64, ( TickType_t ) 0 );
            if( pxNetworkBuffer != NULL )
            {
                pxNetworkBuffer->ulIPAddress = 0; // 0.0.0.0 should be non-routable.
                xNetworkInterfaceOutput( pxNetworkBuffer, pdTRUE );
            }

            firstInit = false;
        }
	}
	else
	{
		xReturn = pdFAIL;

	}
    

	return xReturn;
}
/*-----------------------------------------------------------*/

#define BUFFER_SIZE ( ipTOTAL_ETHERNET_FRAME_SIZE + ipBUFFER_PADDING )
static __attribute__ ((used,section("AHBSRAM0"))) uint8_t ucBuffers[ ipconfigNUM_NETWORK_BUFFER_DESCRIPTORS ][ BUFFER_SIZE ];

/* Next provide the vNetworkInterfaceAllocateRAMToBuffers() function, which
 simply fills in the pucEthernetBuffer member of each descriptor. */
void vNetworkInterfaceAllocateRAMToBuffers(NetworkBufferDescriptor_t pxNetworkBuffers[ ipconfigNUM_NETWORK_BUFFER_DESCRIPTORS ] )
{
    BaseType_t x;
    
    for( x = 0; x < ipconfigNUM_NETWORK_BUFFER_DESCRIPTORS; x++ )
    {
        /* pucEthernetBuffer is set to point ipBUFFER_PADDING bytes in from the beginning of the allocated buffer. */
        pxNetworkBuffers[ x ].pucEthernetBuffer = &( ucBuffers[ x ][ ipBUFFER_PADDING ] );
        
        /* The following line is also required, but will not be required in future versions. */
        *( ( uint32_t * ) &ucBuffers[ x ][ 0 ] ) = ( uint32_t ) &( pxNetworkBuffers[ x ] );
    }
}

/*-----------------------------------------------------------*/

configPLACE_IN_SECTION_RAM
static void vClearTXBuffers()
{
uint32_t ulLastDescriptor = ulNextFreeTxDescriptor;
size_t uxCount = ( ( size_t ) configNUM_TX_DESCRIPTORS ) - uxSemaphoreGetCount( xTXDescriptorSemaphore );
	NetworkBufferDescriptor_t *pxNetworkBuffer;
	uint8_t *ucPayLoad;

    /* This function is called after a TX-completion interrupt.
    It will release each Network Buffer used in xNetworkInterfaceOutput().
    'uxCount' represents the number of descriptors given to DMA for transmission.*/
    
    
    while( uxCount > ( size_t ) 0u )
    {
        if( ( ulTxDescriptorToClear == ulLastDescriptor ) && ( uxCount != ( size_t ) configNUM_TX_DESCRIPTORS ) )
        {
            break;
        }

        ucPayLoad = ( uint8_t * )xDMATxDescriptors[ ulTxDescriptorToClear ].Packet;
        if( ucPayLoad != NULL )
        {
            /* Packet points to a pucEthernetBuffer of a Network Buffer descriptor. */
            pxNetworkBuffer = pxPacketBuffer_to_NetworkBuffer( ucPayLoad );

            configASSERT( pxNetworkBuffer != NULL );

            vReleaseNetworkBufferAndDescriptor( pxNetworkBuffer ) ;
            xDMATxDescriptors[ ulTxDescriptorToClear ].Packet = ( uint32_t )0u;
        }

        /* Move onto the next descriptor, wrapping if necessary. */
        ulTxDescriptorToClear++;
        if( ulTxDescriptorToClear >= configNUM_TX_DESCRIPTORS )
        {
            ulTxDescriptorToClear = 0;
        }

        uxCount--;
        /* Tell the counting semaphore that one more TX descriptor is available. */
        xSemaphoreGive( xTXDescriptorSemaphore );
    }
}

/*-----------------------------------------------------------*/

configPLACE_IN_SECTION_RAM
BaseType_t xNetworkInterfaceOutput( NetworkBufferDescriptor_t * const pxDescriptor, BaseType_t bReleaseAfterSend )
{
BaseType_t xReturn = pdFAIL;
const TickType_t xBlockTimeTicks = pdMS_TO_TICKS( 50 );

    /* Attempt to obtain access to a Tx descriptor. */
    /* Open a do {} while ( 0 ) loop to be able to call break. */
    do
    {
        if( xTXDescriptorSemaphore == NULL )
        {
            break;
        }
        if( xSemaphoreTake( xTXDescriptorSemaphore, xBlockTimeTicks ) != pdPASS )
        {
            /* Time-out waiting for a free TX descriptor. */
            numNetworkDroppedTXPacketsDueToNoBuffer++;
            break;
        }
        
        uint16_t consumeIndex = Chip_ENET_GetTXConsumeIndex(LPC_ETHERNET);
        uint16_t produceIndex = Chip_ENET_GetTXProduceIndex(LPC_ETHERNET);

        //See if there is any Free TX slots left
        if(Chip_ENET_GetFreeDescNum(LPC_ETHERNET, produceIndex, consumeIndex, configNUM_TX_DESCRIPTORS) == 0)
        {
            /* The semaphore was taken, the TX DMA-descriptor is still not available.
            Actually that should not occur, as it was already confirmed free in vClearTXBuffers(). */
            xSemaphoreGive( xTXDescriptorSemaphore );
        }
        else
        {
            
            /* bReleaseAfterSend should always be set when using the zero copy driver. */
            configASSERT( bReleaseAfterSend != pdFALSE );

            /* The DMA's descriptor to point directly to the data in the
            network buffer descriptor.  The data is not copied. */
            xDMATxDescriptors[ produceIndex ].Packet = ( uint32_t ) pxDescriptor->pucEthernetBuffer;
            
            /* The DMA descriptor will 'own' this Network Buffer, until it has been sent.  So don't release it now. */
            bReleaseAfterSend = pdFALSE;

            //TX Control options:
            //ENET_TCTRL_SIZE(n)       Size of data buffer in bytes
            //ENET_TCTRL_OVERRIDE      Override Default MAC Registers
            //ENET_TCTRL_HUGE          Enable Huge Frame
            //ENET_TCTRL_PAD           Pad short Frames to 64 bytes
            //ENET_TCTRL_CRC           Append a hardware CRC to Frame
            //ENET_TCTRL_LAST          Last Descriptor for TX Frame
            //ENET_TCTRL_INT           Generate TxDone Interrupt
            xDMATxDescriptors[produceIndex].Control = ENET_TCTRL_SIZE(pxDescriptor->xDataLength) | ENET_TCTRL_PAD | ENET_TCTRL_INT  | ENET_TCTRL_CRC | ENET_TCTRL_LAST; // size and generate interrupt and last descriptor (SD::last cause tcpip library is handing the packetisation and we will always get a size which fits our MTU)
            
            Chip_ENET_IncTXProduceIndex(LPC_ETHERNET); //trigger buffer to transmit...increase the TXProduceIndex
            
            iptraceNETWORK_INTERFACE_TRANSMIT();

            /* Move onto the next descriptor, wrapping if necessary. */
            ulNextFreeTxDescriptor++;
            if( ulNextFreeTxDescriptor >= configNUM_TX_DESCRIPTORS )
            {
                ulNextFreeTxDescriptor = 0;
            }

            /* The Tx has been initiated. */
            xReturn = pdPASS;
        }
    } while( 0 );

    /* The buffer has been sent so can be released. (when using zero copy bReleaseAfterSend will be false and buffer will be release after the TX interrupt has been received*/
    if( bReleaseAfterSend != pdFALSE )
    {
        vReleaseNetworkBufferAndDescriptor( pxDescriptor );
    }

	return xReturn;
}
/*-----------------------------------------------------------*/

static void prvDelay( uint32_t ulMilliSeconds )
{
	/* Ensure the scheduler was started before attempting to use the scheduler to
	create a delay. */
	configASSERT( xTaskGetSchedulerState() == taskSCHEDULER_RUNNING );

	vTaskDelay( pdMS_TO_TICKS( ulMilliSeconds ) );
}
/*-----------------------------------------------------------*/

static void prvSetupTxDescriptors( void )
{
    BaseType_t x;

      /* Start with Tx descriptors and statuses clear. */
    memset( ( void * ) xDMATxDescriptors, 0, sizeof( xDMATxDescriptors ) );
    memset( ( void * ) xDMATxStatuses, 0, sizeof( xDMATxStatuses ) );


    /* Index to the next Tx descriptor to use. */
    ulNextFreeTxDescriptor = 0ul;

    /* Index to the next Tx descriptor to clear ( after transmission ). */
    ulTxDescriptorToClear = 0ul;

    for( x = 0; x < configNUM_TX_DESCRIPTORS; x++ )
    {
            /*  We do not allocate a buffer here to the descriptor in Zero Copy.
                The PACKET will be set when data is ready to transmit.
                Currently the memset above will have set it to NULL. */

        xDMATxDescriptors[x].Control = 0;
        xDMATxStatuses[x].StatusInfo = 0xFFFFFFFF;
    }

    /* Point the DMA to the base of the descriptor and status list. */
    Chip_ENET_InitTxDescriptors(LPC_ETHERNET, xDMATxDescriptors, xDMATxStatuses, configNUM_TX_DESCRIPTORS);
}
/*-----------------------------------------------------------*/

static void prvSetupRxDescriptors( void )
{
    BaseType_t x;
	NetworkBufferDescriptor_t *pxNetworkBuffer;
    
    /* Clear RX descriptor list. */
    memset( ( void * )  xDMARxDescriptors, 0, sizeof( xDMARxDescriptors ) );
    memset( ( void * )  xDMARxStatuses, 0, sizeof( xDMARxStatuses ) );

    //Build List of Buffers
    for( x = 0; x < configNUM_RX_DESCRIPTORS; x++ )
    {
        /* Allocate a buffer of the largest possible frame size as it is not known what size received frames will be. */

        pxNetworkBuffer = pxGetNetworkBufferWithDescriptor( BUFFER_SIZE, 0 );

        /* During start-up there should be enough Network Buffers available, so it is safe to use configASSERT().
        In case this assert fails, please check: configNUM_RX_DESCRIPTORS,
        ipconfigNUM_NETWORK_BUFFER_DESCRIPTORS, and in case BufferAllocation_2.c
        is included, check the amount of available heap. */
        configASSERT( pxNetworkBuffer != NULL );

        /* Pass the actual buffer to DMA. */
        xDMARxDescriptors[x].Packet = (uint32_t) pxNetworkBuffer->pucEthernetBuffer;

        /* Use an assert to check the allocation as +TCP applications will often
        not use a malloc failed hook as the TCP stack will recover from
        allocation failures. */
        configASSERT( xDMARxDescriptors[x].Packet );

        xDMARxDescriptors[x].Control = ENET_RCTRL_SIZE(ipTOTAL_ETHERNET_FRAME_SIZE) | ENET_RCTRL_INT; //size and trigger interrupt when done
        xDMARxStatuses[x].StatusInfo = 0xFFFFFFFF;
        xDMARxStatuses[x].StatusHashCRC = 0xFFFFFFFF;

    }

    Chip_ENET_InitRxDescriptors(LPC_ETHERNET, xDMARxDescriptors, xDMARxStatuses, configNUM_RX_DESCRIPTORS);

}
/*-----------------------------------------------------------*/
configPLACE_IN_SECTION_RAM
static void prvRemoveTrailingBytes( NetworkBufferDescriptor_t *pxDescriptor )
{
    size_t xExpectedLength;
    IPPacket_t *pxIPPacket;

    pxIPPacket = ( IPPacket_t * ) pxDescriptor->pucEthernetBuffer;
    /* Look at the actual length of the packet, translate it to a host-endial notation. */
    xExpectedLength = sizeof( EthernetHeader_t ) + ( size_t ) FreeRTOS_htons( pxIPPacket->xIPHeader.usLength );

    if( xExpectedLength == ( pxDescriptor->xDataLength + 4 ) )
    {
        pxDescriptor->xDataLength -= 4;
    }
    else
    {
        if( pxDescriptor->xDataLength > xExpectedLength )
        {
            pxDescriptor->xDataLength = ( size_t ) xExpectedLength;
        }
    }
}
/*-----------------------------------------------------------*/
configPLACE_IN_SECTION_RAM
BaseType_t xGetPhyLinkStatus( void )
{
    BaseType_t xReturn;
    
	if( ( ulPHYLinkStatus & PHY_LINK_CONNECTED ) == 0 )
	{
		xReturn = pdFALSE;
	}
	else
	{
		xReturn = pdTRUE;
	}

	return xReturn;
}
/*-----------------------------------------------------------*/

configPLACE_IN_SECTION_RAM
static BaseType_t prvNetworkInterfaceInput()
{
    BaseType_t xReturn = pdFAIL;

    const TickType_t xDescriptorWaitTime = pdMS_TO_TICKS( 50u );
    uint16_t consumeIdx = Chip_ENET_GetRXConsumeIndex(LPC_ETHERNET); //consume index for this frame

    if(ulPHYLinkStatus & PHY_LINK_CONNECTED )
    {
        xReturn = pdTRUE;
        //always leave enough buffers for TX not yet allocated
        const UBaseType_t uxMinimumBuffersRemaining = (configNUM_TX_DESCRIPTORS - uxSemaphoreGetCount(xTXDescriptorSemaphore));
        if( uxGetNumberOfFreeNetworkBuffers() > uxMinimumBuffersRemaining )
        {
            NetworkBufferDescriptor_t *pxNewDescriptor = pxGetNetworkBufferWithDescriptor( BUFFER_SIZE, xDescriptorWaitTime );
            if( pxNewDescriptor == NULL )
            {
                // timed out waiting for a buffer. Dropping packet. We already checked free buffers above so shouldnt get here.
                # if defined(COLLECT_NETDRIVER_ERROR_STATS)
                    numNetworkDroppedRXPacketsDueToNoBuffer++;
                #endif
                iptraceETHERNET_RX_EVENT_LOST();
            }
            else
            {
                uint32_t ulStatus = xDMARxStatuses[ consumeIdx ].StatusInfo; //get status about packet


                /* Replace the character buffer 'Packet'. */
                const uint8_t *pucBuffer = ( const uint8_t * const ) ( xDMARxDescriptors[ consumeIdx ].Packet );
                xDMARxDescriptors[ consumeIdx ].Packet = ( uint32_t ) pxNewDescriptor->pucEthernetBuffer;

                /* 'Packet' contained the address of a 'pucEthernetBuffer' that
                belongs to a Network Buffer.  Find the original Network Buffer. */
                NetworkBufferDescriptor_t *pxDescriptor = pxPacketBuffer_to_NetworkBuffer( pucBuffer );
                
                /* This zero-copy driver makes sure that every 'xDMARxDescriptors' contains
                a reference to a Network Buffer at any time.
                In case it runs out of Network Buffers, a DMA buffer won't be replaced,
                and the received messages is dropped. */
                configASSERT( pxDescriptor != NULL );

                if( pxDescriptor != NULL )
                {
                    /* Get the reported frame length. */
                    uint16_t usLength = ENET_RINFO_SIZE( ulStatus );
                    //FreeRTOS_debug_printf( ( "prvNetworkInterfaceInput: Pkt len: %d\n", usLength  ));

                    pxDescriptor->xDataLength = ( size_t ) usLength;
                    /* It is possible that more data was copied than
                    actually makes up the frame.  If this is the case
                    adjust the length to remove any trailing bytes. */
                    prvRemoveTrailingBytes( pxDescriptor );

                    /* Pass the data to the TCP/IP task for processing. */
                    IPStackEvent_t xRxEvent = { eNetworkRxEvent, NULL };
                    xRxEvent.pvData = ( void * ) pxDescriptor;
                    
                    if( xSendEventStructToIPTask( &xRxEvent, xDescriptorWaitTime ) == pdFALSE )
                    {
                        /* Could not send the descriptor into the TCP/IP
                        stack, it must be released. */
                        numRejectedStackPackets++;
                        vReleaseNetworkBufferAndDescriptor( pxDescriptor );
                        iptraceETHERNET_RX_EVENT_LOST();
                    }
                    else
                    {
                        iptraceNETWORK_INTERFACE_RECEIVE();
                    }
                }
            }
        }
        else
        {
            //No buffers available
            # if defined(COLLECT_NETDRIVER_ERROR_STATS)
                numNetworkDroppedRXPacketsDueToNoBuffer++;
            #endif
            iptraceETHERNET_RX_EVENT_LOST();
        }
    }
    /* Got here because received data was sent to the IP task or the
     data contained an error and was discarded.  Give the descriptor
     back to the DMA. */

    //reset the StatusInfo and HashCRC
    xDMARxStatuses[ consumeIdx ].StatusInfo = 0xFFFFFFFF;
    xDMARxStatuses[ consumeIdx ].StatusHashCRC = 0xFFFFFFFF;

    Chip_ENET_IncRXConsumeIndex(LPC_ETHERNET); //Update consume index

	return xReturn;
}
/*-----------------------------------------------------------*/


//Checks if a frame has errors or should be processed by the IPStack. If not the frame is dropped.
static inline bool processFrame()
{

    const uint16_t consumeIdx = Chip_ENET_GetRXConsumeIndex(LPC_ETHERNET);
    const uint32_t ulStatus = xDMARxStatuses[ consumeIdx ].StatusInfo;

    if( ( ulStatus & nwRX_STATUS_ERROR_BITS ) != 0 )
    {
        //Packet has errors, will be dropped
        #if defined(COLLECT_NETDRIVER_ERROR_STATS)
            if(ulStatus & ENET_RINFO_CRC_ERR ) numNetworkCRCErrors++;
            if(ulStatus & ENET_RINFO_SYM_ERR ) numNetworkSYMErrors++;
            if(ulStatus & ENET_RINFO_LEN_ERR ) numNetworkLENErrors++;
            if(ulStatus & ENET_RINFO_ALIGN_ERR ) numNetworkALIGNErrors++;
            if(ulStatus & ENET_RINFO_OVERRUN ) numNetworkOVERRUNErrors++;
        #endif
    }
    else if(ipCONSIDER_FRAME_FOR_PROCESSING( (const uint8_t * const) (xDMARxDescriptors[ consumeIdx ].Packet) ) == eProcessBuffer )
    {
        return true; // process this packet
    }

            
    //drop the packet. The buffer is already allocated so just increment the consume index to reuse it.

    //reset descriptors StatusInfo and HashCRC
    xDMARxStatuses[ consumeIdx ].StatusInfo = 0xFFFFFFFF;
    xDMARxStatuses[ consumeIdx ].StatusHashCRC = 0xFFFFFFFF;
    Chip_ENET_IncRXConsumeIndex(LPC_ETHERNET); //Update consume index

    return false;
}


configPLACE_IN_SECTION_RAM
void NETWORK_IRQHandler( void )
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    const uint32_t ulRxInterruptMask = ENET_INT_RXDONE | ENET_INT_RXERROR | ENET_INT_RXOVERRUN;   // Receive related interrupt
    const uint32_t ulTxInterruptMask = ENET_INT_TXDONE | ENET_INT_TXERROR | ENET_INT_TXUNDERRUN; // Transmit related interrupt


    configASSERT( xRxHanderTask );

    /* Get pending interrupts */
    uint32_t ulDMAStatus = Chip_ENET_GetIntStatus(LPC_ETHERNET);

    /* RX group interrupt(s). */
    if( ( ulDMAStatus & ulRxInterruptMask ) != 0x00 )
    {
        uint16_t consumeIndex = Chip_ENET_GetRXConsumeIndex(LPC_ETHERNET);
        const uint16_t produceIndex = Chip_ENET_GetRXProduceIndex(LPC_ETHERNET);
        const uint16_t pending = Chip_ENET_GetFillDescNum(LPC_ETHERNET, produceIndex, consumeIndex, configNUM_TX_DESCRIPTORS);

        if (ulDMAStatus & ENET_INT_RXOVERRUN)
        {
            Chip_ENET_RXDisable(LPC_ETHERNET); /* Temporarily disable RX */
            Chip_ENET_ResetRXLogic(LPC_ETHERNET); /* Reset the RX side */
            
            for(uint8_t i=0; i<pending; i++)
            {
                //clear out pending
                consumeIndex = Chip_ENET_GetRXConsumeIndex(LPC_ETHERNET);
                xDMARxStatuses[ consumeIndex ].StatusInfo = 0xFFFFFFFF;
                xDMARxStatuses[ consumeIndex ].StatusHashCRC = 0xFFFFFFFF;
                Chip_ENET_IncRXConsumeIndex(LPC_ETHERNET); //Update consume index
            }

            Chip_ENET_RXEnable(LPC_ETHERNET);
            
            # if defined(COLLECT_NETDRIVER_ERROR_STATS)
                numNetworkRXIntOverrunErrors++;
            #endif
        }
        else
        {
            ulISREvents |= EMAC_IF_RX_EVENT; /* Remember that an RX event has happened. */
            vTaskNotifyGiveFromISR( xRxHanderTask, &xHigherPriorityTaskWoken );
        }
    }

    /* TX group interrupt(s). */
    if( ( ulDMAStatus & ulTxInterruptMask ) != 0x00 )
    {
        ulISREvents |= EMAC_IF_TX_EVENT; /* Remember that a TX event has happened. */
        vTaskNotifyGiveFromISR( xRxHanderTask, &xHigherPriorityTaskWoken );
    }

    /* Clear pending interrupts */
    Chip_ENET_ClearIntStatus(LPC_ETHERNET, ulDMAStatus);

    /* Context switch needed? */
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}
/*-----------------------------------------------------------*/

static void updateLinkSpeed(uint32_t ulPhyStatus)
{
    /* Set interface speed and duplex. */
    if( ( ulPhyStatus & PHY_LINK_SPEED100 ) != 0x00 )
    {
        Chip_ENET_Set100Mbps( LPC_ETHERNET );
    }
    else
    {
        Chip_ENET_Set10Mbps( LPC_ETHERNET );
    }

    if( ( ulPhyStatus & PHY_LINK_FULLDUPLX ) != 0x00 )
    {
        Chip_ENET_SetFullDuplex( LPC_ETHERNET );
    }
    else
    {
        Chip_ENET_SetHalfDuplex( LPC_ETHERNET );
    }
}

static BaseType_t prvSetLinkSpeed( void )
{
    BaseType_t xReturn = pdFAIL;
    TickType_t xTimeOnEntering;
    uint32_t ulPhyStatus;
    const TickType_t xAutoNegotiateDelay = pdMS_TO_TICKS( 5000UL );

    /* Ensure polling does not starve lower priority tasks by temporarily
	setting the priority of this task to that of the idle task. */
    //vTaskPrioritySet( NULL, tskIDLE_PRIORITY );
    vTaskPrioritySet( NULL, tskIDLE_PRIORITY+1 );// IDLE is never called so idle + 1

	xTimeOnEntering = xTaskGetTickCount();
    
    do
	{
		ulPhyStatus = lpcPHYStsPoll();

		if( ( ulPhyStatus & PHY_LINK_CONNECTED ) != 0x00 )
		{
            ulPHYLinkStatus = ulPhyStatus;
            updateLinkSpeed(ulPhyStatus);
			xReturn = pdPASS;
			break;
        } else {
            //Phy Not Connected
        }
	} while( ( xTaskGetTickCount() - xTimeOnEntering ) < xAutoNegotiateDelay );

	/* Reset the priority of this task back to its original value. */
	vTaskPrioritySet( NULL, ipconfigIP_TASK_PRIORITY );

	return xReturn;
}

configPLACE_IN_SECTION_RAM
static void prvEMACHandlerTask( void *pvParameters )
{
    TimeOut_t xPhyTime;
    TickType_t xPhyRemTime;
    BaseType_t xResult = 0;
    const TickType_t xBlockTime = pdMS_TO_TICKS( EMAC_MAX_BLOCK_TIME_MS );

    /* Remove compiler warning about unused parameter. */
    ( void ) pvParameters;

    /* A possibility to set some additional task properties. */
    iptraceEMAC_TASK_STARTING();

    vTaskSetTimeOutState( &xPhyTime );
    xPhyRemTime = pdMS_TO_TICKS( PHY_LS_LOW_CHECK_TIME_MS );

    for( ;; )
    {
        xResult = ( BaseType_t ) 0;
        ulTaskNotifyTake( pdFALSE, xBlockTime );
        
        if( ( ulISREvents & EMAC_IF_TX_EVENT ) != 0 )
        {
            ulISREvents &= ~EMAC_IF_TX_EVENT;
            /* Check if DMA packets have been delivered. */
            vClearTXBuffers();
        }

        
        const uint16_t consumeIndex = Chip_ENET_GetRXConsumeIndex(LPC_ETHERNET);
        const uint16_t produceIndex = Chip_ENET_GetRXProduceIndex(LPC_ETHERNET);
        const uint16_t pending = Chip_ENET_GetFillDescNum(LPC_ETHERNET, produceIndex, consumeIndex, configNUM_TX_DESCRIPTORS);

        if( ( ulISREvents & EMAC_IF_RX_EVENT ) != 0 || pending > 0 )
        {
            ulISREvents &= ~EMAC_IF_RX_EVENT;

            for(uint8_t i=0; i<pending; i++)
            {
                if(processFrame())
                {
                    xResult = prvNetworkInterfaceInput();
                }
            }
        }

        
        //Check PHY status
        if( xResult > 0 )
        {
            /* A packet was received. No need to check for the PHY status now,
            but set a timer to check it later on. */
            vTaskSetTimeOutState( &xPhyTime );
            xPhyRemTime = pdMS_TO_TICKS( PHY_LS_HIGH_CHECK_TIME_MS );
            xResult = 0;
        }
        else if( xTaskCheckForTimeOut( &xPhyTime, &xPhyRemTime ) != pdFALSE )
        {
            uint32_t ulStatus = lpcPHYStsPoll();

            //check if the link state has changed
            if( ( ulPHYLinkStatus & PHY_LINK_CONNECTED ) != ( ulStatus & PHY_LINK_CONNECTED ) )
            {
                if( (ulStatus & PHY_LINK_CONNECTED) == 0 )
                {
                    //lost link, inform IP-Task we lost the network
                    FreeRTOS_NetworkDown();
                }
                else
                {
                    //link up
                    updateLinkSpeed(ulStatus);
                }
            }
            ulPHYLinkStatus = ulStatus;
            
            vTaskSetTimeOutState( &xPhyTime );
            if( ( ulPHYLinkStatus & PHY_LINK_CONNECTED ) != 0 )
            {
                xPhyRemTime = pdMS_TO_TICKS( PHY_LS_HIGH_CHECK_TIME_MS ); //check PHY less often now that the link is up
            }
            else
            {
                xPhyRemTime = pdMS_TO_TICKS( PHY_LS_LOW_CHECK_TIME_MS );
            }
        }
        
        
        
    }
}

/*-----------------------------------------------------------*/
