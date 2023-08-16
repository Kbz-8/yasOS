#include <drivers/video/vga.h>
#include <drivers/video/ports.h>
#include <libc/string.h>
#include <kernel/utils.h>

#define VGA_ADDRESS 0xB8000
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

static inline int _getOffset(int col, int row)
{
	return 2 * (row * SCREEN_TEXT_WIDTH + col);
}

static inline int _getOffsetRow(int offset)
{
	return offset / (2 * SCREEN_TEXT_WIDTH);
}

static inline int _getOffsetCol(int offset)
{
	return (offset - (_getOffsetRow(offset) * 2 * SCREEN_TEXT_WIDTH)) / 2;
}

int _getCursorOffset()
{
	portByteOut(REG_SCREEN_CTRL, 14);
	int offset = portByteIn(REG_SCREEN_DATA) << 8;
	portByteOut(REG_SCREEN_CTRL, 15);
	offset += portByteIn(REG_SCREEN_DATA);
	return offset * 2;
}

void _setCursorOffset(int offset)
{
	offset /= 2;
	portByteOut(REG_SCREEN_CTRL, 14);
	portByteOut(REG_SCREEN_DATA, (uint8_t)(offset >> 8));
	portByteOut(REG_SCREEN_CTRL, 15);
	portByteOut(REG_SCREEN_DATA, (uint8_t)(offset & 0xff));
}

void vgaClear(enum VGA_DISPLAY_COLOR color)
{
	uint8_t* screen = (uint8_t*)VGA_ADDRESS;
	for(int i = 0; i < SCREEN_TEXT_SIZE; i++)
	{
		screen[i * 2] = ' ';
		screen[i * 2 + 1] = (uint8_t)color << 4 | (uint8_t)VGA_DISPLAY_COLOR_WHITE;
	}
	_setCursorOffset(_getOffset(0, 0));
}

int _putChar(char c, int col, int row, enum VGA_DISPLAY_COLOR color)
{
	uint8_t* screen = (uint8_t*)VGA_ADDRESS;

	if(col >= SCREEN_TEXT_WIDTH || row >= SCREEN_TEXT_HEIGHT)
	{
		screen[2 * SCREEN_TEXT_HEIGHT * SCREEN_TEXT_WIDTH - 2] = 'E';
		screen[2 * SCREEN_TEXT_HEIGHT * SCREEN_TEXT_WIDTH - 1] = ((uint8_t)VGA_DISPLAY_COLOR_WHITE << 4)  | (uint8_t)VGA_DISPLAY_COLOR_RED;
		return _getOffset(col, row);
	}

	int offset = (col >= 0 && row >= 0) ? _getOffset(col, row) : _getCursorOffset();
	if(c == '\n')
	{
		row = _getOffsetRow(offset);
		offset = _getOffset(0, row + 1);
	}
	else if(c == 0x08)
	{
		screen[offset] = ' ';
		screen[offset + 1] = (uint8_t)VGA_DISPLAY_COLOR_BLACK << 4 | (uint8_t)color;
	}
	else
	{
		screen[offset] = c;
		screen[offset + 1] = (uint8_t)VGA_DISPLAY_COLOR_BLACK << 4 | (uint8_t)color;
		offset += 2;
	}

	if(offset >= SCREEN_TEXT_HEIGHT * SCREEN_TEXT_WIDTH * 2)
	{
		for (int i = 1; i < SCREEN_TEXT_HEIGHT; i++)
			memcpy((uint8_t*)(_getOffset(0, i) + VGA_ADDRESS), (uint8_t*)(_getOffset(0, i - 1) + VGA_ADDRESS), SCREEN_TEXT_WIDTH * 2);

		char* last_line = (char*)(_getOffset(0, SCREEN_TEXT_HEIGHT - 1) + (uint8_t*)VGA_ADDRESS);
		for(int i = 0; i < SCREEN_TEXT_WIDTH * 2; i++)
			last_line[i] = 0;

		offset -= 2 * SCREEN_TEXT_WIDTH;
	}

	_setCursorOffset(offset);
	return offset;
}

void vgaPrint(char* msg)
{
	vgaPrintAt(msg, -1, -1);
}

void vgaPrintAt(char* msg, int x, int y)
{
	int offset;
	if(x >= 0 && y >= 0)
		offset = _getOffset(x, y);
	else
	{
		offset = _getCursorOffset();
		y = _getOffsetRow(offset);
		x = _getOffsetCol(offset);
	}

	for(int i = 0; msg[i]; i++)
	{
		offset = _putChar(msg[i], x, y, VGA_DISPLAY_COLOR_WHITE);
		x = _getOffsetRow(offset);
		y = _getOffsetCol(offset);
	}
}
