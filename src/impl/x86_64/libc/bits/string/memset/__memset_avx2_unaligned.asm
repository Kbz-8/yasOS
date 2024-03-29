include '__memset_avx_utils.asm'

public __memset_avx2_unaligned

section '.text' executable

__memset_avx2_unaligned:
	vmovd xmm0, esi
	mov rax, rdi
	vpbroadcastb ymm0, xmm0
	cmp rdx, 0x20
	jb avx_20
	cmp rdx, 0x40
	ja avx_size_checker
	vmovdqu yword [rdi + rdx - 0x20], ymm0
	vmovdqu yword [rdi], ymm0
	vzeroupper
	ret
