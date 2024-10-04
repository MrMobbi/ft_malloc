
#include "malloc.h"
#include <string.h>

static void	ft_print_flags(size_t flags)
{
	if (flags == E_FREE)
		ft_printf(" | chunk free\n");
	else if (flags == E_IN_USE)
		ft_printf(" | chunk in use\n");
	else if (flags == E_RESIZE)
		ft_printf(" | chunk resized\n");
}

static void	ft_write_color(char *color)
{
	write(STDOUT_FILENO, color, 5);
}

static void	ft_print_color(size_t flags)
{
	if (flags == E_FREE)
		ft_write_color("\033[31m");
	else if (flags == E_IN_USE)
		ft_write_color("\033[32m");
	else if (flags == E_RESIZE)
		ft_write_color("\033[34m");
	else if (flags == 4)
		ft_write_color("\033[33m");
}

static void	ft_print_chunk(void *ptr)
{
	const	char	*reset = "\033[0m";
	ft_print_color(4);
	ft_print_color(*((size_t*)ptr) & E_GET_FLAGS);
	ft_printf("[%p - %p] : %D bytes", ptr + E_OFFSET_META, \
			ptr + E_OFFSET_META + ((*((size_t*)ptr) >> E_OFFSET_FLAGS) - 1), \
			*((size_t*)ptr) >> E_OFFSET_FLAGS);
	ft_print_flags(*((size_t*)ptr) & E_GET_FLAGS);
	write(STDOUT_FILENO, reset, 4);
}

void	ft_show_block(t_heap *heap, char *heap_type)
{
	void	*ptr;
	size_t	offset;
	if (heap == NULL)
	{
		ft_printf("%s heap is empty\n\n", heap_type);
		return ;
	}
	ft_printf("%s heap:\n", heap_type);
	while (heap != NULL)
	{
		ptr = heap;
		ptr += E_OFFSET_HEAP;
		ft_printf("[%p] # START OF THE BLOCK #\n", heap);
		while (*((size_t*)ptr) != 0)
		{
			ft_print_chunk(ptr);
			offset = ft_offset_calculator(ptr);
			ptr += offset;
		}
		heap = heap->next;
	}
	ft_printf("\n");
}

void	ft_show_block_big(t_heap *heap)
{
	void	*ptr;
	char	*reset = "\033[0m";
	if (heap == NULL)
	{
		ft_printf("Big heap is empty\n\n");
		return ;
	}
	ft_printf("Big heap :\n");
	while (heap != NULL)
	{
		ptr = heap;
		ft_write_color("\033[32m");
		ft_printf("[%p - %p] : %D bytes\n", 
				ptr + E_OFFSET_META_BIG,
				ptr + heap->size,
				heap->size - E_OFFSET_META_BIG);
		heap = heap->next;
	}
	write(STDOUT_FILENO, reset, 4);
}
