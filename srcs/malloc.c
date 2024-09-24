
#include "malloc.h"

t_malloc_data	malloc_data;

bool	ft_create_first_tiny(void)
{
	malloc_data.tiny = mmap(NULL, D_TINY_PAGE_SIZE,	\
		PROT_READ | PROT_WRITE, \
		MAP_PRIVATE | MAP_ANONYMOUS, \
		0, 0);
	if (malloc_data.tiny == MAP_FAILED)
		return (false);
	malloc_data.tiny->size = D_TINY_PAGE_SIZE;
	malloc_data.tiny->size_used = E_OFFSET_HEAP;
	malloc_data.tiny->next = NULL;
	if (D_DEBUG == 1)
	{
		printf("[%p] address size\n", &malloc_data.tiny->size);
		printf("[%p] address size_used\n", &malloc_data.tiny->size_used);
		printf("[%p] address next\n", &malloc_data.tiny->next);
		printf("map tiny created\n");
	}
	return (true);
}

void	*ft_create_new_heap_tiny(t_heap *head)
{
	t_heap	*new = mmap(NULL, D_TINY_PAGE_SIZE, \
			PROT_READ | PROT_WRITE, \
		MAP_PRIVATE | MAP_ANONYMOUS, \
		0, 0);
	if (malloc_data.tiny == MAP_FAILED)
		return (false);
	new->size = D_TINY_PAGE_SIZE;
	new->size_used = E_OFFSET_HEAP;
	new->next = NULL;
	while (head != NULL)
	{
		if (head->next == NULL)
		{
			head->next = new;
			break ;
		}
		head = head->next;
	}
	if (D_DEBUG == 1)
	{
		printf("[%p] address size\n", &new->size);
		printf("[%p] address size_used\n", &new->size_used);
		printf("[%p] address next\n", &new->next);
		printf("map tiny created\n");
	}
	return (new);
}

void	*ft_find_heap_tiny(t_heap *heap, size_t size)
{
	if (heap == NULL)
	{
		ft_create_first_tiny();
		return (malloc_data.tiny);
	}
	while (heap != NULL)
	{
		printf("[%d] | [%d]\n", heap->size_used + (int)size, heap->size);
		if (heap->size_used + (int)size < heap->size)
			return (heap);
		if (heap->next == NULL)
			return (ft_create_new_heap_tiny(malloc_data.tiny));
		heap = heap->next;
	}
	return (NULL);
}

void	ft_update_size_heap_tiny(size_t size, t_heap *heap)
{
	size_t	size_used = heap->size_used;
	size_t	total_size_chunk = size + E_OFFSET_META;
	if (total_size_chunk % E_OFFSET_ALGIN > 0)
		total_size_chunk += E_OFFSET_ALGIN - (total_size_chunk % E_OFFSET_ALGIN);
	size_used += total_size_chunk;
	heap->size_used = size_used;
	printf("[%ld] total_size_chunk\n", total_size_chunk);
	printf("[%ld] memory used int tiny\n", size_used);
}

bool	ft_check_if_small_exist(void)
{
	if (malloc_data.small != NULL)
		return (true);
	malloc_data.small = mmap(NULL, D_SMALL_PAGE_SIZE,	\
		PROT_READ | PROT_WRITE, \
		MAP_PRIVATE | MAP_ANONYMOUS, \
		0, 0);
	if (malloc_data.small == MAP_FAILED)
		return (false);
	malloc_data.small->size = D_SMALL_PAGE_SIZE;
	malloc_data.small->next = NULL;
	malloc_data.small->size = E_OFFSET_HEAP << E_OFFSET_SIZE_USED;
	if (D_DEBUG == 1)
		printf("map small created\n");
	return (true);
}

static size_t	*ft_go_to_next_free_space(void *pos, size_t size)
{
	size_t	meta_data = *((size_t*)pos);
	size_t	chunk_size;
	size_t	flags;
	size_t	offset;

	(void) offset;
	while (meta_data != 0)
	{
		chunk_size = meta_data >> E_OFFSET_FLAGS;
		flags = meta_data & E_OFFSET_FLAGS;
		if (flags == E_FREE)
		{
			if (size <= chunk_size)
				return (pos);
		}
	}
	return (NULL);
}

void	*ft_new_chunk_small(size_t size, void *small)
{
	void	*head = small;
	size_t	*pos = head + E_OFFSET_HEAP;

	pos = ft_go_to_next_free_space(pos, size);
	*pos = size << E_OFFSET_FLAGS;
	*pos += E_IN_USE;
	head = pos;
	return (head + E_OFFSET_META);
}

void	*ft_malloc(size_t size)
{
	void	*ptr;
	void	*heap;
	printf("size asked : [%ld]\n", size);
	if (size <= D_TINY_SIZE)
	{
		printf("tiny detected\n");
		heap = ft_find_heap_tiny(malloc_data.tiny, size);
		if (heap == NULL)
			return (NULL);
		ptr = ft_new_chunk_tiny(size, heap);
		ft_update_size_heap_tiny(size, heap);
		return (ptr);
	}
	else if (size <= D_SMALL_SIZE)
	{
		printf("small detected\n");
		if (!ft_check_if_small_exist())
			return (NULL);
		return (ft_new_chunk_small(size, malloc_data.small));
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
	{
		malloc_data.tiny->size_used -= size + E_OFFSET_META;
		if(ft_check_tiny_heap())
			ft_clear_heap_tiny();
	}
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
