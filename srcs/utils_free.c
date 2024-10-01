
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

bool	ft_heap_is_empty(t_heap *heap)
{
	void	*ptr = heap;
	size_t	meta_data, flags, offset;

	ptr += E_OFFSET_HEAP;
	meta_data = *((size_t*)ptr);
	flags = meta_data & E_GET_FLAGS;
	while (flags == E_FREE)
	{
		offset = ft_offset_calculator(ptr);
		ptr += offset;
		meta_data = *((size_t*)ptr);
		flags = meta_data & E_GET_FLAGS;
		if (meta_data == 0)
			return (true);
	}
	return (false);
}

void *ft_delete_heap_if_empty(t_heap *heap)
{
    t_heap *current = heap;
    t_heap *previous = NULL;

    while (current != NULL)
    {
        t_heap *next = current->next;
        if (ft_heap_is_empty(current))
        {
            if (previous == NULL)
                heap = next;
			else
                previous->next = next;
            munmap(current, current->size);
        }
        else
            previous = current;
        current = next;
    }
    return (heap);
}
