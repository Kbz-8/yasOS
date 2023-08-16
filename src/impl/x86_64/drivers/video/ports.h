#ifndef VGA_PORTS
#define VGA_PORTS

#include <libc/stdint.h>

uint8_t portByteIn(uint16_t port);
void portByteOut(uint16_t port, uint8_t data);
uint16_t portWordIn(uint16_t port);
void portWordOut(uint16_t port, uint16_t data);

#endif
