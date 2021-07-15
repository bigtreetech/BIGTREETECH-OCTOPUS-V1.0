#include "Misc.h"
#include <cstring>

// Version of strncpy that ensures the result is null terminated
void SafeStrncpy(char *dst, const char *src, size_t length)
{
	strncpy(dst, src, length);
	dst[length - 1] = 0;
}

// Version of strcat that takes the original buffer size as the limit and ensures the result is null terminated
void SafeStrncat(char *dst, const char *src, size_t length)
{
	dst[length - 1] = 0;
	const size_t index = strlen(dst);
	strncat(dst + index, src, length - index);
	dst[length - 1] = 0;
}

// End
