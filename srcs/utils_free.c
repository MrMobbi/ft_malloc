
#include "malloc.h"

void	*ft_find_heap_via_ptr(t_heap *heap, void *ptr)
{
	void	*search = heap;
	size_t	chunk_size, offset;
	size_t	total_size = 0;
	search += E_OFFSET_HEAP;

	while (ptr != search + E_OFFSET_META)
	{
		chunk_size = *((size_t*)search) >> E_OFFSET_FLAGS;
		if (total_size + chunk_size > heap->size)
		{
			heap = heap->next;
			search = heap + E_OFFSET_HEAP;
		}
		if (heap == NULL)
			return (NULL);
		total_size += chunk_size;
		offset = ft_offset_calculator(search);
		search += offset;
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

