
#include "malloc.h"

void	*ft_find_heap_via_ptr(t_heap *heap, void *ptr)
{
	void	*search = heap;
	size_t	total_size = E_OFFSET_HEAP;

	search += E_OFFSET_HEAP;
	while (ptr != search)
	{
		if (total_size + ft_offset_calculator(search) > heap->size \
				|| *((size_t*)search) == 0) {
			heap = heap->next;
			if (heap == NULL)
				return (NULL);
			search = heap;
			search += E_OFFSET_HEAP;
			total_size = E_OFFSET_HEAP;
		}
		else
		{
			total_size += ft_offset_calculator(search);
			search += ft_offset_calculator(search);
		}
	}
	return (heap);
}
