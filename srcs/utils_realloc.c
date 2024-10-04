
#include "malloc.h"

static bool	ft_check_space(void *pos, size_t size)
{
	size_t	total_size = *((size_t*)pos) >> E_OFFSET_FLAGS;
	while (total_size <= size)
	{
		pos += ft_offset_calculator(pos);
		if ((*((size_t*)pos) & E_GET_FLAGS) == E_IN_USE)
			return (false);
		total_size += *((size_t*)pos) >> E_OFFSET_FLAGS;
	}
	return (true);
}

static void	*ft_go_metadata(void *ptr)
{
	ptr += E_OFFSET_META;
	return (ptr);
}

static void	*ft_realloc_new(void *pos, size_t new_size, size_t old_size)
{
	void	*new = malloc(new_size);
	pos = ft_go_metadata(pos);

	if (old_size > new_size)
		for (size_t i = 0; i < new_size; i++)
			((unsigned char*)new)[i] = ((unsigned char*)pos)[i];
	else 
		for (size_t i = 0; i < old_size; i++)
			((unsigned char*)new)[i] = ((unsigned char*)pos)[i];
	free(pos);
	return (new);
}

void	*ft_realloc_same_heap(void *pos, size_t size)
{
	if (size == *((size_t*)pos) >> E_OFFSET_FLAGS)
		return (pos + E_OFFSET_META);
	else if (size < *((size_t*)pos) >> E_OFFSET_FLAGS)
		ft_resize_chunk(pos, size);
	else if (size > *((size_t*)pos) >> E_OFFSET_FLAGS)
	{
		if (ft_check_space(pos, size))
			ft_resize_chunk(pos, size);
		else
			return (ft_realloc_new(pos, size, *((size_t*)pos) >> E_OFFSET_FLAGS));
	}
	*((size_t*)pos) = size << E_OFFSET_FLAGS;
	*((size_t*)pos) += E_IN_USE;
	return (pos + E_OFFSET_META);
}

void	*ft_realloc_big(t_heap *heap, void *pos, size_t size)
{
	heap = ft_find_heap_via_ptr(heap, pos);
	if (size == heap->size)
		return (pos + E_OFFSET_META);
	return (ft_realloc_new(pos, size, heap->size));
}

void	*ft_realloc_all(t_heap *heap, void *pos, size_t size)
{
	size_t	new_size;
	if ((*((size_t*)pos) & E_GET_FLAGS) == E_BIG)
	{
		heap = ft_find_heap_via_ptr(heap, pos);
		new_size = heap->size;
	}
	else
		new_size = *((size_t*)pos) >> E_OFFSET_FLAGS;
	return(ft_realloc_new(pos, size, new_size));
}
