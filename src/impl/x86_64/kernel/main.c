#include <drivers/video/vga.h>
#include <libc/stdbool.h>

#ifndef x86_64
	#error "yasOS is only supported on x86_64 CPU architectures for now"
#endif

void __kernel_main()
{
	vgaClear(VGA_DISPLAY_COLOR_BLACK);
	//vgaPrint("yasOS\n");
}
