#include <libc/memcpy.h>

void* memcpy_raw(void* dest, const void* src, uint32_t size)
{
	uint8_t* p_dest;
	uint8_t* p_src;

	if(!dest && !src)
		return (0);
	p_dest = (uint8_t*)dest;
	p_src = (uint8_t *)src;
	while(size--)
		*p_dest++ = *p_src++;
	return dest;
}

void* memcpy_64(void* dest, const void* src, uint32_t size)
{
	uint64_t* p_dest;
	uint64_t* p_src;

	if(!dest && !src)
		return (0);
	p_dest = (uint64_t *)dest;
	p_src = (uint64_t *)src;
	while(size)
	{
		*p_dest++ = *p_src++;
		size -= sizeof(uint64_t);
	}
	return dest;
}

void* memcpy_32(void* dest, const void* src, uint32_t size)
{
	uint32_t* p_dest;
	uint32_t* p_src;

	if(!dest && !src)
		return (0);
	p_dest = (uint32_t *)dest;
	p_src = (uint32_t *)src;
	while(size)
	{
		*p_dest++ = *p_src++;
		size -= sizeof(uint32_t);
	}
	return dest;
}

void* memcpy_16(void* dest, const void* src, uint32_t size)
{
	uint16_t* p_dest;
	uint16_t* p_src;

	if(!dest && !src)
		return (0);
	p_dest = (uint16_t *)dest;
	p_src = (uint16_t *)src;
	while(size)
	{
		*p_dest++ = *p_src++;
		size -= sizeof(uint16_t);
	}
	return dest;
}

void* memcpy(void* dest, const void* src, uint32_t size)
{
	if(size % sizeof(uint64_t) == 0)
		return (memcpy_64(dest, src, size));
	if(size % sizeof(uint32_t) == 0)
		return (memcpy_32(dest, src, size));
	if(size % sizeof(uint16_t) == 0)
		return (memcpy_16(dest, src, size));
	return (memcpy_raw(dest, src, size));
}
