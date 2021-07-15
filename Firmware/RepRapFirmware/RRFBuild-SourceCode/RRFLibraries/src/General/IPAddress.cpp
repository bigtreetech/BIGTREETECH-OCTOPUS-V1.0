/*
 * IPAddress.cpp
 *
 *  Created on: 16 Oct 2018
 *      Author: David
 */

#include "IPAddress.h"

void IPAddress::SetV4(const uint8_t ip[4]) noexcept
{
	v4Address = ((uint32_t)ip[3] << 24) | ((uint32_t)ip[2] << 16) | ((uint32_t)ip[1] << 8) | (uint32_t)ip[0];
}

void IPAddress::UnpackV4(uint8_t rslt[4]) const noexcept
{
	rslt[3] = (uint8_t)(v4Address >> 24);
	rslt[2] = (uint8_t)(v4Address >> 16);
	rslt[1] = (uint8_t)(v4Address >> 8);
	rslt[0] = (uint8_t)v4Address;
}

// End
