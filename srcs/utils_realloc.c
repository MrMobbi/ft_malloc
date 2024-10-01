
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

static void	*ft_realloc_new(void *pos, size_t size)
{
	void	*new = ft_malloc(size);

	for (size_t i = 0; i < *((size_t*)pos) >> E_OFFSET_FLAGS; i++)
		((unsigned char*)new)[i + E_OFFSET_META] = ((unsigned char*)pos)[i + E_OFFSET_META];
	ft_free(pos + E_OFFSET_META);
	return (new);
}

void	*ft_reallocate_same_heap(t_heap *heap, void *pos, size_t size)
{
	(void) heap;
	if (size == *((size_t*)pos) >> E_OFFSET_FLAGS)
		return (pos);
	else if (size < *((size_t*)pos) >> E_OFFSET_FLAGS)
		ft_resize_chunk(pos, size);
	else if (size > *((size_t*)pos) >> E_OFFSET_FLAGS)
	{
		if (ft_check_space(pos, size))
			ft_resize_chunk(pos, size);
		return (ft_realloc_new(pos, size));
	}
	*((size_t*)pos) = size << E_OFFSET_FLAGS;
	*((size_t*)pos) += E_IN_USE;
	return (pos);
}
