
#include "malloc.h"

static bool	ft_check_next_chunk_freed(void *pos, size_t size)
{
	size_t	meta_data = *((size_t*)pos);
	size_t	chunk_size;
	size_t	total_size = 0;
	size_t	flags;
	size_t	offset;

	while (meta_data != 0)
	{
		chunk_size = meta_data >> E_OFFSET_FLAGS;
		flags = meta_data & E_OFFSET_FLAGS;
		if (flags == E_IN_USE)
			return (false);
		total_size += chunk_size;
		if (size <= total_size)
			return (true);
		offset = chunk_size + E_OFFSET_META;
		if (offset % E_OFFSET_ALGIN > 0)
			offset += E_OFFSET_ALGIN - (offset % E_OFFSET_ALGIN);
		pos += offset;
		meta_data = *((size_t*)pos);
		total_size += E_OFFSET_META;
	}
	return (true);
}

static size_t	*ft_go_to_next_free_space(void *pos, size_t size)
{
	size_t	meta_data = *((size_t*)pos);
	size_t	chunk_size;
	size_t	flags;
	size_t	offset;

	while (meta_data != 0)
	{
		chunk_size = meta_data >> E_OFFSET_FLAGS;
		flags = meta_data & E_OFFSET_FLAGS;
		if (flags == E_FREE)
		{
			if (size <= chunk_size)
				return (pos);
			if (ft_check_next_chunk_freed(pos, size))
				return (pos);
		}
		offset = chunk_size + E_OFFSET_META;
		if (offset % E_OFFSET_ALGIN > 0)
			offset += E_OFFSET_ALGIN - (offset % E_OFFSET_ALGIN);
		pos += offset;
		meta_data = *((size_t*)pos);
	}
	return (pos);
}

void	*ft_new_chunk_tiny(size_t size, void *tiny, bool *reuse)
{
	void	*head = tiny;
	size_t	*pos = head + E_OFFSET_HEAP;

	pos = ft_go_to_next_free_space(pos, size);
	if (*((size_t*)pos) != 0)
	{
		if (size > *((size_t*)pos) >> E_OFFSET_FLAGS)
			*pos = size  << E_OFFSET_FLAGS;
		*pos += E_IN_USE;
		head = pos;
		*reuse = true;
		return (head + E_OFFSET_META);
	}
	*pos = size << E_OFFSET_FLAGS;
	*pos += E_IN_USE;
	head = pos;
	*reuse = false;
	return (head + E_OFFSET_META);
}
