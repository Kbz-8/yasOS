#ifndef CPU_FEATURES_X86_64
#define CPU_FEATURES_X86_64

extern CPUfeatures* __get_cpu_features_x86_64();

#define __get_cpu_features() __get_cpu_features_x86_64()

#endif
