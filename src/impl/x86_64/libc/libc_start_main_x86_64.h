#ifndef __LIBC_START_MAIN_X86_64
#define __LIBC_START_MAIN_X86_64

extern void __libc_start_main_x86_64_impl();

#define libc_start_main() __libc_start_main_x86_64_impl()

#endif
