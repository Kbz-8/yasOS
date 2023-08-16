#ifndef CPU_FEATURES
#define CPU_FEATURES

#include <libc/stdbool.h>

typedef struct
{
	bool sse;
	bool sse2;
	bool avx;
	bool avx2;
	bool erms;
} CPUfeatures;

#ifdef x86_64
	#include <libc/arch/x86_64/cpu_features_x86_64.h>
#endif

#endif
