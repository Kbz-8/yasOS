#include <libc/stddef.h>

size_t	__dumb_strlen(char* str)
{
	if(str == NULL)
		return 0;
	size_t size;
	for(size = 0; str[size]; size++);
	return (size);
}
