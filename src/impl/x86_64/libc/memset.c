#include <libc/memset.h>

void* memset(void* ptr, uint8_t value, uint32_t len)
{
	if(ptr == 0)
		return 0;
	uint8_t* byte_ptr = (uint8_t*)ptr;
	while(len > 0)
	{
		*byte_ptr = value;
		byte_ptr++;
		len--;
	}
	return ptr;
}
