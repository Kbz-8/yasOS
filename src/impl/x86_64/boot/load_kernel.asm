disk_load:
	pusha
	push dx 

	mov ah, 0x02
	mov al, dh

	mov ch, 0x00
	mov dh, 0x00
	mov cl, 0x02

	int 0x13

	jc .disk_error

	pop dx
	cmp dh, al
	jne .disk_error

	popa
	ret

	.disk_error:
		jmp $

boot_drive:
	db 0

load_kernel:
	mov bx, KERNEL_OFFSET 
	mov dh, 15
	mov dl, [boot_drive]
	call disk_load
