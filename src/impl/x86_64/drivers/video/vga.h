#ifndef VGA
#define VGA

#include <libc/stdint.h>

#define SCREEN_TEXT_WIDTH 80
#define SCREEN_TEXT_HEIGHT 25
#define SCREEN_TEXT_SIZE (SCREEN_TEXT_WIDTH * SCREEN_TEXT_HEIGHT)

enum VGA_DISPLAY_COLOR
{
    VGA_DISPLAY_COLOR_BLACK         = 0,
    VGA_DISPLAY_COLOR_BLUE          = 1,
    VGA_DISPLAY_COLOR_GREEN         = 2,
    VGA_DISPLAY_COLOR_CYAN          = 3,
    VGA_DISPLAY_COLOR_RED           = 4,
    VGA_DISPLAY_COLOR_MAGENTA       = 5,
    VGA_DISPLAY_COLOR_ORANGE        = 6,
    VGA_DISPLAY_COLOR_LGRAY         = 7,
    VGA_DISPLAY_COLOR_DGRAY         = 8,
    VGA_DISPLAY_COLOR_LBLUE         = 9,
    VGA_DISPLAY_COLOR_LGREEN        = 10,
    VGA_DISPLAY_COLOR_LCYAN         = 11,
    VGA_DISPLAY_COLOR_LRED          = 12,
    VGA_DISPLAY_COLOR_PINK          = 13,
    VGA_DISPLAY_COLOR_YELLOW        = 14,
    VGA_DISPLAY_COLOR_WHITE         = 15,
};

void vgaClear(enum VGA_DISPLAY_COLOR color);
void vgaPrint(char* msg);
void vgaPrintAt(char* msg, int x, int y);

#endif
