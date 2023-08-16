include 'memset_utils.asm'

public __memset_sse2_unaligned_erms

section '.text' executable

__memset_sse2_unaligned_erms:
	movd xmm0, esi
	mov rax, rdi
	punpcklbw xmm0, xmm0
	punpcklwd xmm0, xmm0
	pshufd  xmm0, xmm0, 0
	cmp rdx, 0x10
	jb smart_setter
	cmp rdx, 0x20
	ja .L01
	movdqu  xword [rdi + rdx - 0x10], xmm0
	movdqu  xword [rdi], xmm0
	ret

.L01:
	cmp rdx, 0x800
	ja erms_setter

