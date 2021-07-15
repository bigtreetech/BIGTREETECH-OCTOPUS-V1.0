/*
 * IsoDate.h
 *
 * Definitions of year, month and day of compilation, and null-terminated ISO date string
 *
 *  Created on: 6 Nov 2020
 *      Author: David
 */

#ifndef SRC_GENERAL_ISODATE_H_
#define SRC_GENERAL_ISODATE_H_

constexpr unsigned int compileYear = (__DATE__[7] - '0') * 1000 + (__DATE__[8] - '0') * 100 + (__DATE__[9] - '0') * 10 + (__DATE__[10] - '0');
constexpr unsigned int compileMonth =	  (__DATE__[0] == 'J') ? ((__DATE__[1] == 'a') ? 1 : ((__DATE__[2] == 'n') ? 6 : 7))	// Jan, Jun or Jul
										: (__DATE__[0] == 'F') ? 2																// Feb
										: (__DATE__[0] == 'M') ? ((__DATE__[2] == 'r') ? 3 : 5)									// Mar or May
										: (__DATE__[0] == 'A') ? ((__DATE__[1] == 'p') ? 4 : 8)									// Apr or Aug
										: (__DATE__[0] == 'S') ? 9																// Sep
										: (__DATE__[0] == 'O') ? 10																// Oct
										: (__DATE__[0] == 'N') ? 11																// Nov
										: (__DATE__[0] == 'D') ? 12																// Dec
										: 0;
constexpr unsigned int compileDay = (__DATE__[4] == ' ') ? (__DATE__[5] - '0') : (__DATE__[4] - '0') * 10 + (__DATE__[5] - '0');

constexpr char IsoDate[] =
{	compileYear/1000 + '0', (compileYear % 1000)/100 + '0', (compileYear % 100)/10 + '0', compileYear % 10 + '0',
	'-',  compileMonth/10 + '0', compileMonth%10 + '0',
	'-',  compileDay/10 + '0', compileDay%10 + '0',
	0
};

#if 0	// enable this block to test whether IsoDate is correct
#include <cstring>
static_assert(strcmp(IsoDate, "2020-11-06") == 0);		// change to today's date when testing
#endif

#endif /* SRC_GENERAL_ISODATE_H_ */
