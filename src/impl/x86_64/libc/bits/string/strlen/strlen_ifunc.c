#include <libc/arch/cpu_features.h>

//extern unsigned int __strlen_avx2(char* str);
//extern unsigned int __strlen_sse2(char* str);

unsigned int __dumb_strlen(char* s);

typedef unsigned int (*func_ptr)(char*);

static inline func_ptr __strlen_ifunc(void)
{
//	if(__get_cpu_features()->avx2)
//		return __strlen_avx2;
//	if(__get_cpu_features()->sse2)
//		return __strlen_sse2;
	return __dumb_strlen;
}

unsigned int strlen(char* str) __attribute__((ifunc("__strlen_ifunc")));
