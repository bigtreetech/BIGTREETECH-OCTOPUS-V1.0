/*
 * Misc.h
 *
 *  Created on: 2 Jul 2017
 *      Author: David
 */

#ifndef SRC_MISC_H_
#define SRC_MISC_H_

#include <cstddef>		// for size_t

// Version of strncpy that ensures the result is null terminated
void SafeStrncpy(char *dst, const char *src, size_t length);

// Version of strcat that takes the original buffer size as the limit and ensures the result is null terminated
void SafeStrncat(char *dst, const char *src, size_t length);


#endif /* SRC_MISC_H_ */
