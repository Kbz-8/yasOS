format ELF

end_func:
	ret

smart_setter:
	movq rcx, xmm0
	cmp dl, 8 
	jae setbytes8 ; copy 8 bytes by 8 bytes
	cmp dl, 4
	jae setbytes4 ; copy 4 bytes by 4 bytes
	cmp dl, 1
	ja setbytes1 ; copy bytes by bytes
	jb end_func
	mov byte [rdi], cl
	ret

setbytes8:
	mov qword [rdi + rdx - 8], rcx
	mov qword [rdi], rcx
	ret

setbytes4:
	mov dword [rdi + rdx - 4], ecx
	mov dword [rdi], ecx
	ret

setbytes1:
	mov word [rdi + rdx - 2], cx
	mov word [rdi], cx
	ret

erms_setter:
	mov     rcx, rdx
	movzx   eax, sil
	mov     rdx, rdi
	rep    	stosb
	mov     rax, rdx
	ret

sse2_shared_setter:
	cmp rdx, 0x40 
	ja .L02
	movdqu xword [rdi], xmm0
	movdqu xword [rdi + 0x10], xmm0
	movdqu xword [rdi + rdx - 0x10], xmm0
	movdqu xword [rdi + rdx - 0x20], xmm0
	ret

.L02:
	lea     rcx, [rdi + 0x40]
	movdqu  xword [rdi], xmm0
	and     rcx, 0xffffffffffffffc0
	movdqu  xword [rdi + rdx - 0x10], xmm0
	movdqu  xword [rdi + 0x10], xmm0
	movdqu  xword [rdi + rdx - 0x20], xmm0
	movdqu  xword [rdi + 0x20], xmm0
	movdqu  xword [rdi + rdx - 0x30], xmm0
	movdqu  xword [rdi + 0x30], xmm0
	movdqu  xword [rdi + rdx - 0x40], xmm0
	add     rdx, rdi
	and     rdx, 0xffffffffffffffc0
	cmp     rcx, rdx
	ja end_func
	jmp .L03

.L03:
	movdqa  xword [rcx], xmm0
	movdqa  xword [rcx + 0x10], xmm0
	movdqa  xword [rcx + 0x20], xmm0
	movdqa  xword [rcx + 0x30], xmm0
	add     rcx, 0x40
	cmp     rdx, rcx
	jne     .L03
	ret
