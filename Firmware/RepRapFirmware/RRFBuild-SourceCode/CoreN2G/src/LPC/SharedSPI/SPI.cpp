//Implement the SharedSpi as in RRF

#include "Core.h"
#include "SPI.h"

#include "SoftwareSPI.h"
#include "HardwareSPI.h"

SPI *SPI::getSSPDevice(SSPChannel channel)
{
    switch(channel)
    {
        case SSP0: return &HardwareSPI::SSP0; break;
        case SSP1: return &HardwareSPI::SSP1; break;
        case SWSPI0: return &SoftwareSPI::SWSSP0; break;
        default: return nullptr;
    }
}

