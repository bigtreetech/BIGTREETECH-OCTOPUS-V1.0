/***************************************************************************************************
                                   ExploreEmbedded    
*****************************************************************************************************
 * File:   extintr.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: File contains the functions for configuring and using the LPC1768 External Interrupts.


The libraries have been tested on ExploreEmbedded development boards. We strongly believe that the 
library works on any of development boards for respective controllers. However, ExploreEmbedded 
disclaims any kind of hardware failure resulting out of usage of libraries, directly or indirectly.
Files may be subject to change without prior notice. The revision history contains the information 
related to updates. 


GNU GENERAL PUBLIC LICENSE: 
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>. 

Errors and omissions should be reported to codelibraries@exploreembedded.com
 
 SD: Modified to handle GPIO interrupts and support RRF
 
***************************************************************************************************/
#include "chip.h"
#include "stdutils.h"
#include "gpio.h"
#include "CoreImp.h"
#include "Interrupts.h"

constexpr size_t MaxExtIntEntries = 5;
struct InterruptCallback
{
    StandardCallbackFunction func;
    CallbackParameter param;
    
    InterruptCallback() noexcept : func(nullptr) { }
};


//support only 3 callbacks to save memory
static InterruptCallback callbacks[MaxExtIntEntries] __attribute__((section ("AHBSRAM0")));
Pin ExternalInterruptPins[MaxExtIntEntries] = {NoPin, NoPin, NoPin, NoPin, NoPin};


//Function from WInterrupts from RRF adapted for LPC.


bool attachInterrupt(Pin pin, StandardCallbackFunction callback, enum InterruptMode mode, CallbackParameter param) noexcept
{
    //Port 0 and Port 2 can provide a single interrupt for any combination of port pins.
    //GPIO INTS call EINT3 handler!!

    const uint8_t portNumber = (pin>>5);  //Divide the pin number by 32 go get the PORT number
    const uint8_t var_pinNumber_u8 = pin & 0x1f;  //lower 5-bits contains the bit number of a 32bit port

    // Set callback function and parameter
    size_t slot = MaxExtIntEntries;
    for(size_t i=0; i<MaxExtIntEntries; i++)
    {
        //find a free slot
        if(ExternalInterruptPins[i] == NoPin)
        {
            slot = i; //found a free slot
            break;
        }
    }
    
    if(slot == MaxExtIntEntries) return false; // No Free External Int slots available.

    //ensure pin is on Port 0 or Port 2
    //Each port pin can be programmed to generate an interrupt on a rising edge, a falling edge, or both.
    if(portNumber == 0 || portNumber == 2 )
    {
        const irqflags_t flags = IrqSave();

        ExternalInterruptPins[slot] = pin; // add the pin to the array

        callbacks[slot].func = callback;
        callbacks[slot].param = param;
        
        NVIC_EnableIRQ(EINT3_IRQn); // GPIO interrupts on P0 and P2 trigger EINT3 handler

        switch(mode)
        {
            case InterruptMode::low:
                //LOW level int not implemented in GPIO
                break;
                
            case InterruptMode::high:
                //HIGH level int not implemented in GPIO
                break;
                
            case InterruptMode::falling:
                if(portNumber == 0)
                {
                    util_BitSet(LPC_GPIOINT->IO0.ENF, var_pinNumber_u8); // set Falling Interrupt bit for pin
                    util_BitClear(LPC_GPIOINT->IO0.ENR, var_pinNumber_u8); //ensure Rising disabled
                }
                if(portNumber == 2)
                {
                    util_BitSet(LPC_GPIOINT->IO2.ENF, var_pinNumber_u8);
                    util_BitClear(LPC_GPIOINT->IO2.ENR, var_pinNumber_u8); //ensure Rising disabled
                }

                break;
                
            case InterruptMode::rising:
                if(portNumber == 0) {
                    util_BitSet(LPC_GPIOINT->IO0.ENR, var_pinNumber_u8);
                    util_BitClear(LPC_GPIOINT->IO0.ENF, var_pinNumber_u8); // ensure Falling disabled
                }
                if(portNumber == 2) {
                    util_BitSet(LPC_GPIOINT->IO2.ENR, var_pinNumber_u8);
                    util_BitClear(LPC_GPIOINT->IO2.ENF, var_pinNumber_u8); // ensure Falling disabled
                }

                break;
                
            case InterruptMode::change:
                //Rising and Falling
                if(portNumber == 0)
                {
                    util_BitSet(LPC_GPIOINT->IO0.ENF, var_pinNumber_u8); //Falling
                    util_BitSet(LPC_GPIOINT->IO0.ENR, var_pinNumber_u8); //Rising
                }
                if(portNumber == 2)
                {
                    util_BitSet(LPC_GPIOINT->IO2.ENF, var_pinNumber_u8); //Falling
                    util_BitSet(LPC_GPIOINT->IO2.ENR, var_pinNumber_u8); //Rising
                }

                break;
                
            default:
                break;
                
        }

        IrqRestore(flags);
        
    }
    else
    {
        return false; // no interrupts avail on this pin
    }
    
    return true;
}


void detachInterrupt(Pin pin) noexcept
{
 
    const uint8_t portNumber =  (pin>>5);  //Divide the pin number by 32 go get the PORT number
    const uint8_t var_pinNumber_u8  =   pin & 0x1f;  //lower 5-bits contains the bit number of a 32bit port

    const irqflags_t flags = IrqSave();

    for(size_t i=0; i<MaxExtIntEntries; i++)
    {
        if(ExternalInterruptPins[i] == pin)
        {
            ExternalInterruptPins[i] = NoPin; //remove the pin from the array

            break;
        }
    }
    
    //clear Rise and Fall interrupt for Pin
    if(portNumber == 0)
    {
        util_BitClear(LPC_GPIOINT->IO0.ENF, var_pinNumber_u8); //Falling
        util_BitClear(LPC_GPIOINT->IO0.ENR, var_pinNumber_u8); //Rising
    }
    if(portNumber == 2)
    {
        util_BitClear(LPC_GPIOINT->IO2.ENF, var_pinNumber_u8); //Falling
        util_BitClear(LPC_GPIOINT->IO2.ENR, var_pinNumber_u8); //Rising
    }
    
    IrqRestore(flags);

    
}


extern "C" void EINT3_IRQHandler(void) noexcept
{
    //We assume we arent also using EINT3 (external interrupt function), but only the GPIO interrupts which share the same interrupt
    
    //Look for Rising And Falling interrupt for both ports
    //Since we dont need to do anything different for rise/fall, we treat the same
    uint32_t isr0 = LPC_GPIOINT->IO0.STATR | LPC_GPIOINT->IO0.STATF; // get all pins rise and fall which triggered int
    uint32_t isr2 = LPC_GPIOINT->IO2.STATR | LPC_GPIOINT->IO2.STATF; // get all pins rise and fall which triggered int

    //port 0
    while (isr0 != 0)
    {
        const unsigned int pos0 = LowestSetBitNumber(isr0);        // only one bit should be set
        LPC_GPIOINT->IO0.CLR |= (1 << pos0); // clear the status
        
        //Find the slot for this pin
        const Pin pin= (Pin)(pos0);// Since this is on port 0, this is just the pin number
        size_t slot = MaxExtIntEntries;
        for(size_t i=0; i<MaxExtIntEntries; i++)
        {
            if(ExternalInterruptPins[i] == pin){
                slot = i; //found slot
                break;
            }
        }
        
        if(slot < MaxExtIntEntries && callbacks[slot].func != NULL)
        {
            callbacks[slot].func(callbacks[slot].param);

        }

        isr0 &= ~(1u << pos0);
    }
    //port 2
    while (isr2 != 0)
    {
        const unsigned int pos2 = LowestSetBitNumber(isr2);        // only one bit should be set
        LPC_GPIOINT->IO2.CLR |= (1 << pos2); // clear the status

        //Find the slot for this pin
        const Pin pin = (Pin) ((2 << 5) | (pos2));// pin on port 2
        size_t slot = MaxExtIntEntries;
        for(size_t i=0; i<MaxExtIntEntries; i++)
        {
            if(ExternalInterruptPins[i] == pin){
                slot = i; //found slot
                break;
            }
        }

        
        if(slot < MaxExtIntEntries && callbacks[slot].func != NULL)
        {
            callbacks[slot].func(callbacks[slot].param);
        }


        isr2 &= ~(1u << pos2);
    }

    
    
}

/*************************************************************************************************
                                    END of  ISR's 
**************************************************************************************************/
