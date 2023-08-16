#include <libc/stdint.h>

uint8_t portByteIn(uint16_t port)
{
	uint8_t result;
	__asm__ volatile("in %%dx, %%al" : "=a" (result) : "d" (port));
	return result;
}

void portByteOut(uint16_t port, uint8_t data)
{
	__asm__ volatile("out %%al, %%dx" : : "a" (data), "d" (port));
}

uint16_t portWordIn(uint16_t port)
{
	uint16_t result;
	__asm__ volatile("in %%dx, %%ax" : "=a" (result) : "d" (port));
	return result;
}

void portWordOut(uint16_t port, uint16_t data)
{
	__asm__ volatile("out %%ax, %%dx" : : "a" (data), "d" (port));
}
