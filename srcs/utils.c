
#include "malloc.h"


size_t	ft_offset_calculator(void *ptr)
{
	size_t	offset = *((size_t*)ptr) >> E_OFFSET_FLAGS;
	offset += E_OFFSET_META;
	if (offset % E_OFFSET_ALGIN > 0)
		offset += E_OFFSET_ALGIN - (offset % E_OFFSET_ALGIN);
	return (offset);
}
