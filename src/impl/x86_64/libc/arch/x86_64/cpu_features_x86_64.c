#include <libc/arch/cpu_features.h>
#include <libc/stddef.h>

#define SSE  0x02000000
#define SSE2 0x04000000
#define AVX  0x10000000
#define AVX2 0x00000020
#define ERMS 0x00000100

CPUfeatures __cpu_features_x86_64;
_Atomic bool __cpu_features_init = false;

void __inline_asm_cpuid(int fid, int sfid, unsigned int* eax, unsigned int* ebx, unsigned int* ecx, unsigned int* edx)
{
	#if defined(__clang__) || defined(__GNUC__) || defined(__MINGW32__) || defined(__MINGW34__)
		__asm__ volatile
		(
			"cpuid" 
			:   "=a" (*eax), 
				"=b" (*ebx), 
				"=c" (*ecx), 
				"=d" (*edx)

			:   "a" (fid),
				"c" (sfid)
		);
	#else
		#error "inline assembly not supported"
	#endif
}

CPUfeatures* __get_cpu_features_x86_64()
{
	unsigned int eax, ebx, ecx, edx;

	if(__cpu_features_init == false)
	{
		__inline_asm_cpuid(1, 0, &eax, &ebx, &ecx, &edx);
		__cpu_features_x86_64.sse = edx & SSE;
		__cpu_features_x86_64.sse2 = edx & SSE2;
		__cpu_features_x86_64.avx = ecx & AVX;
		__inline_asm_cpuid(7, 0, &eax, &ebx, &ecx, &edx);
		__cpu_features_x86_64.avx2 = ebx & AVX2;
		__cpu_features_x86_64.erms = ebx & ERMS;
		__cpu_features_init = true;
	}
	return &__cpu_features_x86_64;
}
