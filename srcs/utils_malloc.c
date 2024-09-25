

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
	printf("[%p] address size\n", &new->size);
	printf("[%p] address size_used\n", &new->size_used);
	printf("[%p] address next\n", &new->next);
	return (new);
}

void	ft_update_size_heap(size_t size, t_heap *heap)
{
	size_t	size_used = heap->size_used;
	size_t	total_size_chunk = size + E_OFFSET_META;
	if (total_size_chunk % E_OFFSET_ALGIN > 0)
		total_size_chunk += E_OFFSET_ALGIN - (total_size_chunk % E_OFFSET_ALGIN);
	size_used += total_size_chunk;
	heap->size_used = size_used;
}

void	*ft_get_heap(t_heap *heap, size_t size, size_t size_page)
{
	while (heap != NULL)
	{
		if (heap->size_used + size < heap->size)
			return (heap);
		if (heap->next == NULL)
			return (ft_create_new_heap(heap, size_page));
		heap = heap->next;
	}
	return (NULL);
}
