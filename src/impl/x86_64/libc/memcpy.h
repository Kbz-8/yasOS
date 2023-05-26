#ifndef LIBC_MEMCPY
#define LIBC_MEMCPY

#include <stdint.h>

void* memcpy(void* dst, const void* src, uint32_t len);

#endif
