#include <libc/memset.h>
#include <kernel/vga.h>
#include <stdbool.h>

void kernel_main()
{
	vgaInit();
	while(true)
	{
		vgaClear(COLOR(0, 0, 0));
		vgaSwap();
	}
}
