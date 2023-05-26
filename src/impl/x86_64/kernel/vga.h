#ifndef VGA
#define VGA

#include <stdint.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define SCREEN_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT)

#define COLOR(_r, _g, _b)((uint8_t)( \
    (((_r) & 0x7) << 5) |       \
    (((_g) & 0x7) << 2) |       \
    (((_b) & 0x3) << 0)))

#define COLOR_R(_index) (((_index) >> 5) & 0x7)
#define COLOR_G(_index) (((_index) >> 2) & 0x7)
#define COLOR_B(_index) (((_index) >> 0) & 0x3)

enum VGA_DISPLAY_COLOR
{
    VGA_DISPLAY_COLOR_BLACK         = 0,
    VGA_DISPLAY_COLOR_BLUE          = 1,
    VGA_DISPLAY_COLOR_GREEN         = 2,
    VGA_DISPLAY_COLOR_CYAN          = 3,
    VGA_DISPLAY_COLOR_RED           = 4,
    VGA_DISPLAY_COLOR_MAGENTA       = 5,
    VGA_DISPLAY_COLOR_BROWN         = 6,
    VGA_DISPLAY_COLOR_LIGHTGRAY     = 7,
    VGA_DISPLAY_COLOR_DARKGRAY      = 8,
    VGA_DISPLAY_COLOR_LIGHTBLUE     = 9,
    VGA_DISPLAY_COLOR_LIGHTGREEN    = 10,
    VGA_DISPLAY_COLOR_LIGHTCYAN     = 11,
    VGA_DISPLAY_COLOR_LIGHTRED      = 12,
    VGA_DISPLAY_COLOR_PINK          = 13,
    VGA_DISPLAY_COLOR_YELLOW        = 14,
    VGA_DISPLAY_COLOR_WHITE         = 15
};

extern uint8_t __vga_swap_buffer[2][SCREEN_SIZE];
extern uint8_t __vga_swap_buffer_index;

#define screen_buffer() (__vga_swap_buffer[__vga_swap_buffer_index])
#define screen_set(_p, _x, _y) (__vga_swap_buffer[__vga_swap_buffer_index][((_y) * SCREEN_WIDTH + (_x))] = (_p))

#define screen_fill(_c, _x, _y, _w, _h) do \
	{\
		__typeof__(_x) __x = (_x);\
		__typeof__(_y) __y = (_y);\
		__typeof__(_w) __w = (_w);\
		__typeof__(_y) __ymax = __y + (_h);\
		__typeof__(_c) __c = (_c);\
		for(; __y < __ymax; __y++)\
			memset(&screen_buffer()[__y * SCREEN_WIDTH + __x], __c, __w);\
	} while (0)

void vgaInit();
void vgaClear(uint8_t color);
void vgaSwap();

#endif
