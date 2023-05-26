#include <kernel/vga.h>
#include <libc/memset.h>
#include <kernel/utils.h>

#define VGA_ADDRESS 0xA0000

uint8_t __vga_swap_buffer[2][SCREEN_SIZE];
uint8_t __vga_swap_buffer_index = 0;

#define CURRENT_BUFFER (__vga_swap_buffer[__vga_swap_buffer_index])
#define SWAP() (__vga_swap_buffer_index = 1 - __vga_swap_buffer_index)

#define PALETTE_MASK 0x3C6
#define PALETTE_READ 0x3C7
#define PALETTE_WRITE 0x3C8
#define PALETTE_DATA 0x3C9

void vgaSwap()
{
	memcpy(VGA_ADDRESS, &CURRENT_BUFFER, SCREEN_SIZE);
	SWAP();
}

void vgaClear(uint8_t color)
{
	memset(&CURRENT_BUFFER, color, SCREEN_SIZE);
}

void vgaInit()
{
	// configure palette with 8-bit RRRGGGBB color
	outportb(PALETTE_MASK, 0xFF);
	outportb(PALETTE_WRITE, 0);
	for(uint8_t i = 0; i < 255; i++)
	{
		outportb(PALETTE_DATA, (((i >> 5) & 0x7) * (256 / 8)) / 4);
		outportb(PALETTE_DATA, (((i >> 2) & 0x7) * (256 / 8)) / 4);
		outportb(PALETTE_DATA, (((i >> 0) & 0x3) * (256 / 4)) / 4);
	}

	// set color 255 = white
	outportb(PALETTE_DATA, 0x3F);
	outportb(PALETTE_DATA, 0x3F);
	outportb(PALETTE_DATA, 0x3F);
}
