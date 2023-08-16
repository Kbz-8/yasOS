#ifndef KERNEL_UTILS
#define KERNEL_UTILS

#include <libc/stdint.h>

static inline void outportb(uint16_t port, uint8_t data)
{
	__asm__("outb %1, %0" : : "dN" (port), "a" (data));
}

#endif
