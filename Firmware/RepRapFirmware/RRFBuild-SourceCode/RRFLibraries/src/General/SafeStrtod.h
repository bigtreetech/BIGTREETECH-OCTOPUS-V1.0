/*
 * SafeStrtod.h
 *
 *  Created on: 8 Apr 2018
 *      Author: David
 */

#ifndef SRC_LIBRARIES_GENERAL_SAFESTRTOD_H_
#define SRC_LIBRARIES_GENERAL_SAFESTRTOD_H_

float SafeStrtof(const char *s, const char **endptr = nullptr) noexcept;

uint32_t StrToU32(const char *s, const char **endptr = nullptr) noexcept;

// This overload is used by the 12864 menu code in RepRapFirmware
inline uint32_t StrToU32(char *s, char **endptr = nullptr) noexcept
{
	// Defining it this way saves duplicating the code
	return StrToU32(s, const_cast<const char **>(endptr));
}

int32_t StrToI32(const char *s, const char **endptr = nullptr) noexcept;
uint32_t StrOptHexToU32(const char *s, const char **endptr = nullptr) noexcept;
uint32_t StrHexToU32(const char *s, const char **endptr = nullptr) noexcept;

// This next one was used in places when we may wish to read hex numbers, but we now have alternatives
[[deprecated("use StrToU32, StrHexToU32 or StrOptHexToU32 instead")]] unsigned long SafeStrtoul(const char *s, const char **endptr = nullptr, int base = 10) noexcept;

#define strtod(s, p) Do_not_use_strtod_use_SafeStrtof_instead
#define strtof(s, p) Do_not_use_strtof_use_SafeStrtof_instead
#define strtol(s, ...) Do_not_use_strtol_use_StrToI32_instead
#define strtoul(s, ...) Do_not_use_strtoul_use_StrToU32_instead
#define atof(s) Do_not_use_atof_use_SafeStrtof_instead
#define atoi(s) Do_not_use_atoi_use_StrToI32_instead
#define atol(s) Do_not_use_atol_use_StrToU32_instead

#endif /* SRC_LIBRARIES_GENERAL_SAFESTRTOD_H_ */
