/*
  Copyright (c) 2014 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <stdlib.h>
#include <FreeRTOS.h>
#include <string.h>

//sdavi: Edited to use FreeRTOS pvPortMalloc and vPortFree as we are using Heap5.c. Needs to be setup before using new

void *operator new(size_t size)
{
    void *mem = pvPortMalloc(size);
    if (mem != nullptr)
        memset(mem, 0, size);
    return mem;
}

void *operator new[](size_t size)
{
    void *mem = pvPortMalloc(size);
    if (mem != nullptr)
        memset(mem, 0, size);
    return mem;
}

void* operator new(size_t size, std::align_val_t align)
{
    void *mem = pvPortMalloc(size);
    if (mem != nullptr)
        memset(mem, 0, size);
    return mem;
}

void *operator new[](size_t size, std::align_val_t align)
{
    void *mem = pvPortMalloc(size);
    if (mem != nullptr)
        memset(mem, 0, size);
    return mem;
}

void operator delete(void * ptr)
{
        vPortFree(ptr);
}

void operator delete(void *ptr , std::size_t)
{
        vPortFree(ptr);
}

void operator delete[](void * ptr)
{
        vPortFree(ptr);
}

void operator delete(void * ptr, std::align_val_t align)
{
        vPortFree(ptr);
}


void operator delete(void *ptr , std::size_t, std::align_val_t align)
{
        vPortFree(ptr);
}

void operator delete[](void * ptr, std::align_val_t align)
{
        vPortFree(ptr);
}




