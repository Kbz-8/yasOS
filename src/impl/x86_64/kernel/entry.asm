format ELF64

section '.text' executable
	extrn __kernel_main
	call __kernel_main
	jmp $
