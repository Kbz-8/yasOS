use16

org 0x7c00

KERNEL_OFFSET equ 0x1000

mov [boot_drive], dl

mov bp, 0x9000
mov sp, bp

call load_kernel
call use_32bpm

jmp $

include "gdt.asm"
include "load_kernel.asm"
include "protected.asm"

use32
main_32b:
    call KERNEL_OFFSET

    jmp $

times 510-($-$$) db 0
dw 0xaa55 
