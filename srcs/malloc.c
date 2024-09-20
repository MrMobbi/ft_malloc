
#include "malloc.h"

t_malloc_data	malloc_data;

bool	ft_check_if_tiny_exist(void)
{
	if (malloc_data.tiny != NULL)
		return (true);
	malloc_data.tiny = mmap(NULL, D_TINY_PAGE_SIZE,	\
		PROT_READ | PROT_WRITE, \
		MAP_PRIVATE | MAP_ANONYMOUS, \
		0, 0);
	if (malloc_data.tiny == MAP_FAILED)
		return (false);
	malloc_data.tiny->size = D_TINY_PAGE_SIZE;
	malloc_data.tiny->next = NULL;
	if (D_DEBUG == 1)
		printf("map tiny created\n");
	return (true);
}

bool	ft_check_if_small_exist(void)
{
	if (malloc_data.small != NULL)
		return (true);
	malloc_data.small = mmap(NULL, D_SMALL_PAGE_SIZE,	\
		PROT_READ | PROT_WRITE, \
		MAP_PRIVATE | MAP_ANONYMOUS, \
		0, 0);
	if (D_DEBUG == 1)
		printf("map small created\n");
	if (malloc_data.small == MAP_FAILED)
		return (false);
	return (true);
}

bool	ft_check_next_chunk_freed(void *pos, size_t size)
{
	size_t	meta_data = *((size_t*)pos);
	size_t	chunk_size;
	size_t	total_size;
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
	}
	return (true);
}

size_t	*ft_go_to_next_free_space(void *pos, size_t size)
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
			if (chunk_size <= size)
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

void	*ft_create_new_chunk(size_t size)
{
	void	*head = malloc_data.tiny;
	size_t	*pos = head + E_OFFSET_HEAP;

	pos = ft_go_to_next_free_space(pos, size);
	if (*((size_t*)pos) != 0)
	{
		if (size > *((size_t*)pos) >> E_OFFSET_FLAGS)
			*pos = size  << E_OFFSET_FLAGS;
		*pos += E_IN_USE;
		head = pos;
		return (head + E_OFFSET_META);
	}
	*pos = size << E_OFFSET_FLAGS;
	*pos += E_IN_USE;
	head = pos;
	return (head + E_OFFSET_META);
}

void	*ft_malloc(size_t size)
{
	printf("size asked : [%ld]\n", size);
	if (size <= D_TINY_SIZE)
	{
		printf("tiny detected\n");
		if (!ft_check_if_tiny_exist())
			return (NULL);
		return(ft_create_new_chunk(size));
	}
	else if (size <= D_SMALL_SIZE)
	{
		printf("small detected\n");
		if (!ft_check_if_small_exist())
			return (NULL);
	}
	else if (size > D_SMALL_PAGE_SIZE)
	{
		printf("big detected\n");
		//todo
	}
	return (NULL);
}

//******************//
//		FT_FREE		//
//******************//
static void	*ft_move_size(void *pos)
{
	size_t	meta_data = *((size_t*)pos);
	size_t	chunk_size = meta_data >> E_OFFSET_FLAGS;
	size_t	offset = E_OFFSET_META + chunk_size;
	if (offset % E_OFFSET_ALGIN > 0)
		offset += E_OFFSET_ALGIN - (offset % E_OFFSET_ALGIN);
	return (pos + offset);
}

static bool	ft_check_tiny_heap(void)
{
	void	*head = malloc_data.tiny;
	size_t	*pos = head + E_OFFSET_HEAP;
	size_t	meta_data = *pos;

	while (meta_data != 0)
	{
		if ((meta_data & E_OFFSET_FLAGS) == E_IN_USE)
			return (false);
		pos = ft_move_size(pos);
		meta_data = *pos;
	}
	printf("all heap clear\n");
	return (true);
}

static void ft_clear_heap_tiny(void)
{
	munmap(malloc_data.tiny, D_TINY_SIZE);
	malloc_data.tiny = NULL;
	printf("page tiny destroyed\n");
}

static void	ft_check_if_heap_is_used(size_t size)
{
	if (size <= D_TINY_SIZE)
		if(ft_check_tiny_heap())
			ft_clear_heap_tiny();
}

void	ft_free(void *ptr)
{
	size_t	*pos = ptr - E_OFFSET_META;
	size_t	meta_data = *pos;
	size_t	size = meta_data >> E_OFFSET_FLAGS;
	size_t	flags = meta_data & E_OFFSET_FLAGS;
	if (flags == E_IN_USE)
		flags = E_FREE;
	else if (flags == E_FREE)
		(void) flags; // todo error handling double free
	*pos = size << E_OFFSET_FLAGS;
	*pos += E_FREE;
	ft_check_if_heap_is_used(size);
}
