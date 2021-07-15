/*
 * Alligator Microstepping Settings
 *
 *  Created on: 15 May 2017
 *      Author: Marco Antonini
 */

#include "Microstepping.h"
#include "RepRapFirmware.h"


//***************************************************************************************************
// LPC Microstepping static class


uint8_t microstepping[ NumDirectDrivers ];

void Microstepping::Init() {
    //nothing to do
    
}

bool Microstepping::Set(uint8_t drive, uint8_t value) {

	// Do not exceed the maximum value
	if ( drive >= (NumDirectDrivers) )
	{
		return false;
	}
	if (value !=8 && value != 16 && value != 32 && value != 128 && value != 256)
	{
		return false;
	}

    microstepping[drive] = value;

    return true;
}

uint8_t Microstepping::Read( uint8_t drive ) {

	// Do not exceed the maximum value
	if ( drive < (NumDirectDrivers) )
	{
		return ( microstepping[drive] );
	}
	else
	{
		return 16;
	}
}

// End
