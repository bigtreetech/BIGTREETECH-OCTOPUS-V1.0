#ifndef STATICNETWORKMEMORYALLOCATOR_H
#define STATICNETWORKMEMORYALLOCATOR_H

#include <stdlib.h>

void *staticMallocLarge( size_t xWantedSize );
void staticFreeLarge( void *blkPtr );

void *staticMallocSocket( size_t xWantedSize );
void staticFreeSocket( void *blkPtr );



#endif
