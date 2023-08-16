format ELF

public __abs

section '.text' executable

__abs:
	mov ebx, eax
	neg eax
	cmovl eax, ebx ; if eax is now negative, restore its saved value
	ret
