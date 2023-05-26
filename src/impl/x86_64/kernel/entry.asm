format ELF
use32

section '.text' executable
	extrn kernel_main
	call kernel_main
	jmp $
