format ELF

public sqrt

section '.text' executable

sqrt:
	sqrtss xmm0, xmm0 ; calc the sqrt of the given number using single precision float numbers
	ret
