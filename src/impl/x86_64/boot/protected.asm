use16
use_32bpm:
    cli

    lgdt [gdt_descriptor]

    mov eax , cr0 
    or eax , 0x1
    mov cr0 , eax

    jmp CODE_SEG:init_32bpm

use32
init_32bpm:
    mov ax, DATA_SEG

    mov ds, ax
    mov ss, ax 
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000
    mov esp, ebp

    call main_32b

use16
