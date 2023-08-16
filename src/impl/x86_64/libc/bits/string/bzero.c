#include <libc/stddef.h>
#include <libc/string.h>

__attribute__((always_inline)) inline void	bzero(void *s, size_t n)
{
	memset(s, 0, n);
}
