format ELF

public __memset_erms
public _setter

section '.text' executable

__memset_erms:
	test rdx, rdx
	jne _setter
	mov rax, rdi
	ret

_setter:
	mov     rcx, rdx
	movzx   eax, sil
	mov     rdx, rdi
	rep    	stosb
	mov     rax, rdx
	ret
