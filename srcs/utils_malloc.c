

#include "malloc.h"

void	*ft_create_new_heap(t_heap *head, size_t heap_size)
{
	t_heap	*new = mmap(NULL, heap_size, \
		PROT_READ | PROT_WRITE, \
		MAP_PRIVATE | MAP_ANONYMOUS, \
		0, 0);
	if (new == MAP_FAILED)
		return (false);
	new->size = heap_size;
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
	return (new);
}

void	ft_update_size_heap(t_heap *heap)
{
	void	*pos = heap;
	size_t	total_size = E_OFFSET_HEAP;
	size_t	flags;

	pos += E_OFFSET_HEAP;
	while (*((size_t*)pos) != 0)
	{
		flags = *((size_t*)pos) & E_GET_FLAGS;
		if (flags != E_FREE)
			total_size += ft_offset_calculator(pos);
		pos += ft_offset_calculator(pos);
	}
	heap->size_used = total_size;
}

void	*ft_get_heap(t_heap *heap, size_t size, size_t size_page)
{
	while (heap != NULL)
	{
		if (heap->size_used + ft_real_size_calculator(size) + E_OFFSET_META < heap->size)
			return (heap);
		if (heap->next == NULL)
			return (ft_create_new_heap(heap, size_page));
		heap = heap->next;
	}
	return (NULL);
}
