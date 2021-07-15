    /***************************************************************************************************
                                   ExploreEmbedded    
 ****************************************************************************************************
 * File:   gpio.h
 * Version: 15.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: File contains the the accessing the GPIO pins of a controller.
                First the GPIO pins needs to configured(Input/Output) and later used accordingly.

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
 **************************************************************************************************/


#include "chip.h"
#include "stdutils.h"
#include "gpio.h"

#include "BitBanding.h"

inline void GPIO_PinFunction(gpioPins_et enm_pinNumber, uint8_t var_pinFunction_u8)
{
    uint8_t var_portNumber_u8 =  (enm_pinNumber >> 5);  //Divide the pin number by 32 go get the PORT number
    uint8_t var_pinNumber_u8  =  (enm_pinNumber & 0x1f);  //lower 5-bits contains the bit number of a 32bit port
    
    var_portNumber_u8 = var_portNumber_u8 * 2;
    if(var_pinNumber_u8 >= 16)
    {
       var_portNumber_u8++; 
       var_pinNumber_u8 = var_pinNumber_u8 - 16;
    }
    
    var_pinNumber_u8 = var_pinNumber_u8 * 2;
        
    //Each pin in PINSEL has 2 bits to configure
    //Get the bitband alias address of both bits (IOCON is in peripheral region)
    volatile uint32_t* bb_pin_b1 = bb_alias_periph_dword(&LPC_IOCON->PINSEL[var_portNumber_u8], var_pinNumber_u8);
    volatile uint32_t* bb_pin_b2 = bb_alias_periph_dword(&LPC_IOCON->PINSEL[var_portNumber_u8], var_pinNumber_u8+1);
    
    *bb_pin_b1 = (var_pinFunction_u8 & 0x01);        //1st bit of pinFunction
    *bb_pin_b2 = (var_pinFunction_u8 >> 1) & 0x01;   //2nd bit of pinFunction
}



/***************************************************************************************************
                  void GPIO_PinDirection(gpioPins_et enm_pinNumber, uint8_t var_pinDirn_u8)
 ***************************************************************************************************
 * I/P Arguments: 
                gpioPins_et: pin number which needs to be updated.
                             Refer the gpio.h for pin numbering.
                gpioDirection_et: Direction to be configured ie. INPUT/OUTPUT.
                              

 * Return value    : none

 * description :This function sets the specified direction as INPUT/OUTPUT.  
 ***************************************************************************************************/

inline volatile uint32_t *GPIO_BB_PinDirectionPtr(gpioPins_et enm_pinNumber)
{
    const uint8_t var_portNumber_u8 =  (enm_pinNumber >> 5);          //Divide the pin number by 32 go get the PORT number
    const uint8_t var_pinNumber_u8  =  (enm_pinNumber & 0x1f);        //lower 5-bits contains the bit number of a 32bit port
    LPC_GPIO_T *LPC_GPIO_PORT = (LPC_GPIO_T*)(LPC_GPIO0_BASE + ((var_portNumber_u8) << 5));

    //Get the bitband alias address
    return bb_alias_sram_dword(&LPC_GPIO_PORT->DIR, var_pinNumber_u8);
}


inline void GPIO_PinDirection(gpioPins_et enm_pinNumber, uint8_t var_pinDirn_u8)
{
    const uint8_t var_portNumber_u8 =  (enm_pinNumber >> 5);      //Divide the pin number by 32 go get the PORT number
    const uint8_t var_pinNumber_u8  =  (enm_pinNumber & 0x1f);    //lower 5-bits contains the bit number of a 32bit port

    /* Go to particular port after decoding from the pin number and  set the direction as specified*/
    LPC_GPIO_T *LPC_GPIO_PORT = (LPC_GPIO_T*)(LPC_GPIO0_BASE + ((var_portNumber_u8) << 5));

    //Get the bitband alias address
    volatile uint32_t* bb_pin = bb_alias_sram_dword(&LPC_GPIO_PORT->DIR, var_pinNumber_u8);
    *bb_pin = var_pinDirn_u8 & 0x01; //set the BB alias word which sets the bit in LPC_GPIO_PORT->DIR

}








/***************************************************************************************************
            void GPIO_PinWrite(gpioPins_et enm_pinNumber, uint8_t var_pinValue_u8)
 ***************************************************************************************************
 * I/P Arguments: 
                gpioPins_et: pin number which needs to be updated.
                             Refer the gpio.h for pin numbering.
                gpioValue_et: Value to be updated(LOW/HIGH) on the selected pin.
                              

 * Return value    : none

 * description :This function updates the specified value on the selected pin.  
                Before updating the pins status, the pin function should be selected and then
                the pin should be configured as OUTPUT 
***************************************************************************************************/
inline void GPIO_PinWrite(gpioPins_et enm_pinNumber, uint8_t var_pinValue_u8)
{
    const uint8_t var_portNumber_u8 = (enm_pinNumber >> 5);       //Divide the pin number by 32 go get the PORT number
    const uint8_t var_pinNumber_u8  = (enm_pinNumber & 0x1f);     //lower 5-bits contains the bit number of a 32bit port
    LPC_GPIO_T *LPC_GPIO_PORT = (LPC_GPIO_T*)(LPC_GPIO0_BASE + ((var_portNumber_u8) << 5));
    
    if (var_pinValue_u8 & 0x1)
    {
        LPC_GPIO_PORT->SET = 1 << var_pinNumber_u8;
    }
    else
    {
        LPC_GPIO_PORT->CLR = 1 << var_pinNumber_u8;
    }
}



inline volatile uint32_t *GPIO_BB_PinValuePtr(gpioPins_et enm_pinNumber)
{
    const uint8_t var_portNumber_u8 =  (enm_pinNumber >> 5);       //Divide the pin number by 32 go get the PORT number
    const uint8_t var_pinNumber_u8  =  (enm_pinNumber & 0x1f);     //lower 5-bits contains the bit number of a 32bit port
    LPC_GPIO_T * LPC_GPIO_PORT = (LPC_GPIO_T*)(LPC_GPIO0_BASE + ((var_portNumber_u8) << 5));
        
    //Get the bitband alias address
    return bb_alias_sram_dword(&LPC_GPIO_PORT->PIN, var_pinNumber_u8);
}





/***************************************************************************************************
                    uint8_t GPIO_PinRead(gpioPins_et enm_pinNumber)
 ***************************************************************************************************
 * I/P Arguments: 
                gpioPins_et: pin number which needs to be read.
                             Refer the gpio.h for pin numbering.

 * Return value    : 
                 uint8_t:    Status of the specified pin.

 * description :This function returns the status of the selected pin.
                Before reading the pins status, the pin function should be selected and accordingly
                the pin should be configured as INPUT 
 ***************************************************************************************************/
inline uint8_t GPIO_PinRead(gpioPins_et enm_pinNumber)
{
    uint8_t returnStatus = 0;
    const uint8_t var_portNumber_u8 =  (enm_pinNumber >> 5);      //Divide the pin number by 32 go get the PORT number
    const uint8_t var_pinNumber_u8  =  (enm_pinNumber & 0x1f);    //lower 5-bits contains the bit number of a 32bit port

    /* Go to particular port after decoding from the pin number and read the pins status */
    LPC_GPIO_T * LPC_GPIO_PORT = (LPC_GPIO_T*)(LPC_GPIO0_BASE + ((var_portNumber_u8) << 5));
    
    returnStatus = util_IsBitSet(LPC_GPIO_PORT->PIN,var_pinNumber_u8);
                  
    return returnStatus;
}

//SD: Added function to handle pin modes, based on mbed
inline void GPIO_PinInputMode(gpioPins_et enm_pinNumber, uint8_t var_pinFunction_u8) noexcept
{
    uint8_t port_number;
    uint8_t pin_number = enm_pinNumber;

    port_number =  (enm_pinNumber>>5);  //Divide the pin number by 32 go get the PORT number
    pin_number  =   pin_number & 0x1f;  //lower 5-bits contains the bit number of a 32bit port

    switch (var_pinFunction_u8){
        case LPC_INPUT_PULLUP:
            // Set the two bits for this pin as 00
            if( port_number == 0 && pin_number < 16  ){ LPC_IOCON->PINMODE[0] &= ~(3<<( pin_number    *2)); }
            if( port_number == 0 && pin_number >= 16 ){ LPC_IOCON->PINMODE[1] &= ~(3<<((pin_number-16)*2)); }
            if( port_number == 1 && pin_number < 16  ){ LPC_IOCON->PINMODE[2] &= ~(3<<( pin_number    *2)); }
            if( port_number == 1 && pin_number >= 16 ){ LPC_IOCON->PINMODE[3] &= ~(3<<((pin_number-16)*2)); }
            if( port_number == 2 && pin_number < 16  ){ LPC_IOCON->PINMODE[4] &= ~(3<<( pin_number    *2)); }
            if( port_number == 3 && pin_number >= 16 ){ LPC_IOCON->PINMODE[7] &= ~(3<<((pin_number-16)*2)); }
            if( port_number == 4 && pin_number >= 16 ){ LPC_IOCON->PINMODE[9] &= ~(3<<((pin_number-16)*2)); }

             break;
        case LPC_INPUT_REPEATER:
            // Set the two bits for this pin as 01
            if( port_number == 0 && pin_number < 16  ){ LPC_IOCON->PINMODE[0] |= (1<<( pin_number*2)); LPC_IOCON->PINMODE[0] &= ~(2<<( pin_number    *2)); }
            if( port_number == 0 && pin_number >= 16 ){ LPC_IOCON->PINMODE[1] |= (1<<( pin_number*2)); LPC_IOCON->PINMODE[1] &= ~(2<<((pin_number-16)*2)); }
            if( port_number == 1 && pin_number < 16  ){ LPC_IOCON->PINMODE[2] |= (1<<( pin_number*2)); LPC_IOCON->PINMODE[2] &= ~(2<<( pin_number    *2)); }
            if( port_number == 1 && pin_number >= 16 ){ LPC_IOCON->PINMODE[3] |= (1<<( pin_number*2)); LPC_IOCON->PINMODE[3] &= ~(2<<((pin_number-16)*2)); }
            if( port_number == 2 && pin_number < 16  ){ LPC_IOCON->PINMODE[4] |= (1<<( pin_number*2)); LPC_IOCON->PINMODE[4] &= ~(2<<( pin_number    *2)); }
            if( port_number == 3 && pin_number >= 16 ){ LPC_IOCON->PINMODE[7] |= (1<<( pin_number*2)); LPC_IOCON->PINMODE[7] &= ~(2<<((pin_number-16)*2)); }
            if( port_number == 4 && pin_number >= 16 ){ LPC_IOCON->PINMODE[9] |= (1<<( pin_number*2)); LPC_IOCON->PINMODE[9] &= ~(2<<((pin_number-16)*2)); }
             break;
        case LPC_INPUT_NOPULLUP_NOPULLDOWN:
            // Set the two bits for this pin as 10
            if( port_number == 0 && pin_number < 16  ){ LPC_IOCON->PINMODE[0] |= (2<<( pin_number*2)); LPC_IOCON->PINMODE[0] &= ~(1<<( pin_number    *2)); }
            if( port_number == 0 && pin_number >= 16 ){ LPC_IOCON->PINMODE[1] |= (2<<( pin_number*2)); LPC_IOCON->PINMODE[1] &= ~(1<<((pin_number-16)*2)); }
            if( port_number == 1 && pin_number < 16  ){ LPC_IOCON->PINMODE[2] |= (2<<( pin_number*2)); LPC_IOCON->PINMODE[2] &= ~(1<<( pin_number    *2)); }
            if( port_number == 1 && pin_number >= 16 ){ LPC_IOCON->PINMODE[3] |= (2<<( pin_number*2)); LPC_IOCON->PINMODE[3] &= ~(1<<((pin_number-16)*2)); }
            if( port_number == 2 && pin_number < 16  ){ LPC_IOCON->PINMODE[4] |= (2<<( pin_number*2)); LPC_IOCON->PINMODE[4] &= ~(1<<( pin_number    *2)); }
            if( port_number == 3 && pin_number >= 16 ){ LPC_IOCON->PINMODE[7] |= (2<<( pin_number*2)); LPC_IOCON->PINMODE[7] &= ~(1<<((pin_number-16)*2)); }
            if( port_number == 4 && pin_number >= 16 ){ LPC_IOCON->PINMODE[9] |= (2<<( pin_number*2)); LPC_IOCON->PINMODE[9] &= ~(1<<((pin_number-16)*2)); }
             break;
        case LPC_INPUT_PULLDOWN:
            // Set the two bits for this pin as 11
            if( port_number == 0 && pin_number < 16  ){ LPC_IOCON->PINMODE[0] |= (3<<( pin_number    *2)); }
            if( port_number == 0 && pin_number >= 16 ){ LPC_IOCON->PINMODE[1] |= (3<<((pin_number-16)*2)); }
            if( port_number == 1 && pin_number < 16  ){ LPC_IOCON->PINMODE[2] |= (3<<( pin_number    *2)); }
            if( port_number == 1 && pin_number >= 16 ){ LPC_IOCON->PINMODE[3] |= (3<<((pin_number-16)*2)); }
            if( port_number == 2 && pin_number < 16  ){ LPC_IOCON->PINMODE[4] |= (3<<( pin_number    *2)); }
            if( port_number == 3 && pin_number >= 16 ){ LPC_IOCON->PINMODE[7] |= (3<<((pin_number-16)*2)); }
            if( port_number == 4 && pin_number >= 16 ){ LPC_IOCON->PINMODE[9] |= (3<<((pin_number-16)*2)); }

             break;
        case LPC_OPEN_DRAIN_MODE:
            if( port_number == 0 ){ LPC_IOCON->PINMODE_OD[0] |= (1<<pin_number); }
            if( port_number == 1 ){ LPC_IOCON->PINMODE_OD[1] |= (1<<pin_number); }
            if( port_number == 2 ){ LPC_IOCON->PINMODE_OD[2] |= (1<<pin_number); }
            if( port_number == 3 ){ LPC_IOCON->PINMODE_OD[3] |= (1<<pin_number); }
            if( port_number == 4 ){ LPC_IOCON->PINMODE_OD[4] |= (1<<pin_number); }
            //pull_none(); // no pull up by default

             break;
        default:
             return; // invalid mode
        }
 }

