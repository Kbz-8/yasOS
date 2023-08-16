#include <libc/stddef.h>

void* __dumb_memset(void* s, int c, size_t n)
{
	unsigned char* tmp;

	tmp = (unsigned char*)s;
	while (n--)
		*tmp++ = (unsigned char)c;
	return (s);
}
