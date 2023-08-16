#include <libc/arch/cpu_features.h>

//extern void* __memset_erms(void* str, int c, unsigned int n);
//extern void* __memset_avx512_unaligned(void* str, int c, unsigned int n);
//extern void* __memset_avx_no_vzeroupper(void* str, int c, unsigned int n);
//extern void* __memset_avx2_unaligned(void* str, int c, unsigned int n);
//extern void* __memset_sse2_unaligned(void* str, int c, unsigned int n);
//extern void* __memset_sse2_unaligned_erms(void* str, int c, unsigned int n);

void* __dumb_memset(void* s, int c, unsigned int n);

typedef void* (*func_ptr)(void*, int, unsigned int);

static inline func_ptr __memset_ifunc(void)
{
/*
	register unsigned int edx asm("%edx");
	if(__get_cpu_features()->erms)
		if((edx & 0x1000) != 0)
			return __memset_erms;
	if(has_avx512)
	{
		if((edx & 0x800) == 0)
			return __memset_avx512_unaligned;
		return __memset_avx_no_vzeroupper;
	}
	if(__get_cpu_features()->avx2)
		return __memset_avx2_unaligned;
	if(__get_cpu_features()->sse2)
	{
		if(__get_cpu_features()->erms)
			return __memset_sse2_unaligned_erms;
		return __memset_sse2_unaligned;
	}
*/
	return __dumb_memset;
}

void* memset(void* str, int c, unsigned int n) __attribute__((ifunc("__memset_ifunc")));
