
#include "malloc.h"

t_malloc_data	malloc_data;

//******************//
//		MALLOC		//
//******************//

static void	*ft_find_heap(t_heap *heap, size_t size)
{
	size_t	page_size;
	t_heap	*new;

	if (size <= D_TINY_SIZE)
		page_size = D_TINY_PAGE_SIZE;
	else if (size <= D_SMALL_SIZE)
		page_size = D_SMALL_PAGE_SIZE;
	else
		page_size = size + E_OFFSET_META_BIG;

	if (heap == NULL)
	{
		if (size <= D_TINY_SIZE)
			new = malloc_data.tiny = ft_create_new_heap(NULL, D_TINY_PAGE_SIZE);
		else if (size <= D_SMALL_SIZE)
			new = malloc_data.small = ft_create_new_heap(NULL, D_SMALL_PAGE_SIZE);
		else
			new = malloc_data.big = ft_create_new_heap(NULL, page_size);
		return (new);
	}

	if (size > D_SMALL_SIZE)
		return (ft_create_new_heap(malloc_data.big, page_size));
	else
		return (ft_get_heap(heap, size, page_size));
}

void	*ft_malloc(size_t size)
{
	void	*pos;
	void	*heap;
	if (size <= D_TINY_SIZE)
		heap = ft_find_heap(malloc_data.tiny, size);
	else if (size <= D_SMALL_SIZE)
		heap = ft_find_heap(malloc_data.small, size);
	else if (size > D_SMALL_SIZE)
	{
		heap = ft_find_heap(malloc_data.big, size);
		if (heap == NULL)
			return (NULL);
		heap += E_OFFSET_HEAP;
		*((size_t*)heap) = E_BIG;
		return (heap + E_OFFSET_META);
	}
	if (heap == NULL)
		return (NULL);
	pos = ft_new_chunk(size, heap);
	ft_update_size_heap(heap);
	return (pos);
}

//******************//
//		REALLOC		//
//******************//

void	*ft_reallocate(t_heap *heap, void *pos, size_t size)
{
	(void) heap;
	(void) pos;
	(void) size;
	return (NULL);
}

void	*ft_realloc(void *pos, size_t size)
{
	if (pos == NULL)
		return (ft_malloc(size));
	pos -= E_OFFSET_META;
	if ((*((size_t*)pos) & E_GET_FLAGS) == E_FREE \
			|| (*((size_t*)pos) & E_GET_FLAGS) == E_RESIZE)
		return (NULL);
	else if ((*((size_t*)pos) & E_GET_FLAGS) == E_BIG)
		return (ft_reallocate_big(malloc_data.big, pos, size));
	if ((size <= D_TINY_SIZE &&  \
			*((size_t*)pos) >> E_OFFSET_FLAGS <= D_TINY_SIZE)
		|| 
			(size <= D_SMALL_SIZE &&  \
			*((size_t*)pos) >> E_OFFSET_FLAGS <= D_SMALL_SIZE))
		pos = ft_realloc_same_heap(pos, size);
	else
		pos = ft_realloc_all(malloc_data.big, pos, size);
	return (pos);
}

//******************//
//		FREE		//
//******************//

static void ft_delete_heap_big(void *pos)
{
	t_heap *current = malloc_data.big;
	t_heap *previous = NULL;
	t_heap *target = (t_heap *)((char *)pos - E_OFFSET_META_BIG);

	while (current)
	{
		if (current == target)
		{
			if (previous) 
				previous->next = current->next;
			else 
				malloc_data.big = current->next;
			munmap(current, current->size);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

static void	ft_check_heap_empty(size_t size)
{
	if (size <= D_TINY_SIZE)
		malloc_data.tiny = ft_delete_heap_if_empty(malloc_data.tiny);
	else if (size <= D_SMALL_SIZE)
		malloc_data.small = ft_delete_heap_if_empty(malloc_data.small);
}

static void	ft_update_heap(size_t size, void *pos)
{
	t_heap	*heap;

	if (size <= D_TINY_SIZE)
		heap = ft_find_heap_via_ptr(malloc_data.tiny, pos);
	else if (size <= D_SMALL_SIZE)
		heap = ft_find_heap_via_ptr(malloc_data.small, pos);
	size += E_OFFSET_META;
	if (size % E_OFFSET_ALGIN > 0)
		size += E_OFFSET_ALGIN - (size % E_OFFSET_ALGIN);
	heap->size_used -= size;
}


void	ft_free(void *ptr)
{
	size_t	*pos = ptr - E_OFFSET_META;
	size_t	meta_data = *pos;
	size_t	size = meta_data >> E_OFFSET_FLAGS;
	size_t	flags = meta_data & E_GET_FLAGS;
	if (flags == E_BIG)
		ft_delete_heap_big(ptr);
	else
	{
		if (flags == E_IN_USE)
			flags = E_FREE;
		else if (flags == E_FREE)
			(void) flags; // todo error handling double free
		*pos = size << E_OFFSET_FLAGS;
		*pos += E_FREE;
		ft_update_heap(size, pos);
		ft_check_heap_empty(size);
	}
}

//******************//
//	  SHOW_MEM  	//
//******************//

void	show_alloc_mem(void)
{
	ft_show_block(malloc_data.tiny, "TINY");
	ft_show_block(malloc_data.small, "SMALL");
	ft_show_block_big(malloc_data.big);
}
