#ifndef GENERIC_H
#define GENERIC_H

#include "../Pins_LPC.h"


// List of assignable pins and their mapping from names to MPU ports. This is indexed by logical pin number.
// The names must match user input that has been concerted to lowercase and had _ and - characters stripped out.
// Aliases are separate by the , character.
// If a pin name is prefixed by ! then this means the pin is hardware inverted. The same pin may have names for both the inverted and non-inverted cases,
// for example the inverted heater pins on the expansion connector are available as non-inverted servo pins on a DFueX.

// All pins can be accessed using the pin notation PX.Y, so no names needed
constexpr PinEntry PinTable_Generic[] =
{

};

//NoPin for Generic, Actual pins must be specified in /sys/Board.txt 
constexpr BoardDefaults genericDefaults = {
    0,
    {NoPin, NoPin, NoPin, NoPin, NoPin},    //enablePins
    {NoPin, NoPin, NoPin, NoPin, NoPin},    //stepPins
    {NoPin, NoPin, NoPin, NoPin, NoPin},    //dirPins
#if HAS_SMART_DRIVERS
    {NoPin, NoPin, NoPin, NoPin, NoPin},    //uartPins
    0,                                      // Smart drivers
#endif
    0,                                      //digiPot Factor    
};

#endif