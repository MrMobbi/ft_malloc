
#include "malloc.h"

static bool	ft_check_next_chunk_freed(void *pos, size_t size)
{
	size_t	meta_data = *((size_t*)pos);
	size_t	chunk_size, flags, offset;
	size_t	total_size = 0;

	while (meta_data != 0)
	{
		chunk_size = meta_data >> E_OFFSET_FLAGS;
		flags = meta_data & E_GET_FLAGS;
		if (flags == E_IN_USE)
			return (false);
		total_size += chunk_size;
		if (size <= total_size)
			return (true);
		offset = ft_offset_calculator(pos);
		pos += offset;
		meta_data = *((size_t*)pos);
		total_size += E_OFFSET_META;
	}
	return (true);
}

static bool	ft_new_size_feat(size_t new_size, size_t old_size)
{
	new_size = ft_real_size_calculator(new_size);
	old_size = ft_real_size_calculator(old_size);

	if (new_size <= old_size)
		return (true);
	return (false);
}

static void	*ft_go_next_free_space(void *pos, size_t size)
{
	size_t	meta_data = *((size_t*)pos);
	size_t	chunk_size, flags, offset;

	while (meta_data != 0)
	{
		chunk_size = meta_data >> E_OFFSET_FLAGS;
		flags = meta_data & E_GET_FLAGS;
		if (flags == E_FREE)
		{
			if (ft_new_size_feat(size, chunk_size))
				return (pos);
			if (ft_check_next_chunk_freed(pos, size))
				return (pos);
		}
		offset = ft_offset_calculator(pos);
		pos += offset;
		meta_data = *((size_t*)pos);
	}
	return (pos);
}

static void	ft_free_inbetween(void *pos, size_t new_size, size_t old_size)
{
	pos += new_size + E_OFFSET_META;
	*((size_t*)pos) = (old_size - new_size - E_OFFSET_META) << E_OFFSET_FLAGS;
	*((size_t*)pos) += E_RESIZE;
}

static void	ft_resize_inbetween(void *pos, size_t new_size, size_t old_size)
{
	void	*start = pos;
	size_t	total_jump = old_size;

	while (total_jump < new_size)
	{
		pos += ft_offset_calculator(pos);
		total_jump += ft_real_size_calculator(*((size_t*)pos) >> E_OFFSET_FLAGS);
	}
	pos = start;
	if (total_jump != new_size)
	{
		pos += new_size + E_OFFSET_META;
		*((size_t*)pos) = (total_jump - new_size) << E_OFFSET_FLAGS;
		*((size_t*)pos) += E_RESIZE;
	}
}

void	ft_resize_chunk(void *pos, size_t size)
{
	size_t	old_size, new_size;
	
	new_size = ft_real_size_calculator(size);
	old_size = ft_offset_calculator(pos) - E_OFFSET_META;
	if (old_size == new_size)
		return ;
	else if (old_size > new_size)
		ft_free_inbetween(pos, new_size, old_size);
	else if (new_size > old_size)
		ft_resize_inbetween(pos, new_size, old_size);
}

void	*ft_new_chunk(size_t size, t_heap *heap)
{
	void	*head = heap;
	size_t	*pos = head + E_OFFSET_HEAP;

	pos = ft_go_next_free_space(pos, size);
	if (*pos != 0)
		ft_resize_chunk(pos, size);
	*pos = size << E_OFFSET_FLAGS;
	*pos += E_IN_USE;
	head = pos;
	return (head + E_OFFSET_META);
}
