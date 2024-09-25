
#include "malloc.h"

t_malloc_data	malloc_data;

//******************//
//		MALLOC		//
//******************//

static void	*ft_find_heap(t_heap *heap, size_t size)
{
	if (size <= D_TINY_SIZE)
	{
		if (heap == NULL)
		{
			malloc_data.tiny = ft_create_new_heap(NULL, D_TINY_PAGE_SIZE);
			return (malloc_data.tiny);
		}
		heap = ft_get_heap(heap, size, D_TINY_PAGE_SIZE);
	}
	else if (size <= D_SMALL_SIZE)
	{
		if (heap == NULL)
		{
			malloc_data.small = ft_create_new_heap(NULL, D_SMALL_PAGE_SIZE);
			return (malloc_data.small);
		}
		heap = ft_get_heap(heap, size, D_SMALL_PAGE_SIZE);
	}
	else if (size > D_SMALL_SIZE)
	{
		if (heap == NULL)
		{
			malloc_data.big = ft_create_new_heap(NULL, size + E_OFFSET_HEAP);
			return (malloc_data.big);
		}
		heap = ft_create_new_heap(malloc_data.big, size + E_OFFSET_HEAP);
		return (heap);
	}
	return (heap);
}

void	*ft_malloc(size_t size)
{
	void	*ptr;
	void	*heap;
	printf("size asked : [%ld]\n", size);
	if (size <= D_TINY_SIZE)
		heap = ft_find_heap(malloc_data.tiny, size);
	else if (size <= D_SMALL_SIZE)
		heap = ft_find_heap(malloc_data.small, size);
	else if (size > D_SMALL_SIZE)
	{
		heap = ft_find_heap(malloc_data.big, size);
		return (heap + E_OFFSET_HEAP);
	}
	if (heap == NULL)
		return (NULL);
	ptr = ft_new_chunk(size, heap);
	ft_update_size_heap(size, heap);
	return (ptr);
}

//******************//
//		FREE		//
//******************//

static void ft_delete_heap_big(void *ptr)
{
	t_heap *current = malloc_data.big;
	t_heap *previous = NULL;
	t_heap *target = (t_heap *)((char *)ptr - E_OFFSET_HEAP);

	while (current)
	{
		if (current == target)
		{
			if (previous) 
				previous->next = current->next;
			else 
				malloc_data.big = current->next;
			munmap(current, current->size);
			return;
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

static void	ft_update_heap(size_t size, void *ptr)
{
	t_heap	*heap;

	if (size <= D_TINY_SIZE)
		heap = ft_find_heap_via_ptr(malloc_data.tiny, ptr);
	else if (size <= D_SMALL_SIZE)
		heap = ft_find_heap_via_ptr(malloc_data.small, ptr);
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
	size_t	flags = meta_data & E_OFFSET_FLAGS;
	if (meta_data == 0 || meta_data > 8129)
		ft_delete_heap_big(ptr);
	else
	{
		if (flags == E_IN_USE)
			flags = E_FREE;
		else if (flags == E_FREE)
			(void) flags; // todo error handling double free
		*pos = size << E_OFFSET_FLAGS;
		*pos += E_FREE;
		ft_update_heap(size, ptr);
		ft_check_heap_empty(size);
	}
}

//******************//
//	  SHOW_MEM  	//
//******************//

void	show_alloc_mem(void)
{
	ft_show_block(malloc_data.tiny, "TNY");
	ft_show_block(malloc_data.small, "SMALL");
	ft_show_block_big(malloc_data.big);
}
