
#include "malloc.h"

void	ft_show_block(t_heap *heap, char *heap_type)
{
	void	*ptr;
	size_t	offset;
	if (heap == NULL)
	{
		printf("%s heap is empty\n", heap_type);
		return ;
	}

	printf("%s heap:\n", heap_type);
	while (heap != NULL)
	{
		ptr = heap;
		ptr += E_OFFSET_HEAP;
		printf("[%p] start of the block\n", heap);
		while (*((size_t*)ptr) != 0)
		{
			printf("[%p - %p] : %ld bytes\n", ptr + E_OFFSET_META, \
					ptr + E_OFFSET_META + (*((size_t*)ptr) >> E_OFFSET_FLAGS), \
					*((size_t*)ptr) >> E_OFFSET_FLAGS);
			offset = ft_offset_calculator(ptr);
			ptr += offset;
		}
		heap = heap->next;
	}
	printf("\n");
}

void	ft_show_block_big(t_heap *heap)
{
	void	*ptr;
	if (heap == NULL)
	{
		printf("Big heap is empty\n\n");
		return ;
	}
	printf("Big heap :\n");
	while (heap != NULL)
	{
		ptr = heap;
		printf("[%p - %p] : %ld bytes\n", ptr + E_OFFSET_HEAP, \
				ptr + E_OFFSET_HEAP + heap->size,
				heap->size);
		heap = heap->next;
	}
}
