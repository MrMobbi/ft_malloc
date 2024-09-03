
#include "malloc.h"

t_malloc_data	malloc_data;
t_heap_tiny		tiny;
t_heap_small	small;
t_heap_big		big;

bool	ft_check_if_heap_exist(t_heap_tiny *heap_tiny)
{
	if (heap_tiny)
		return (true);
	else
	{
		tiny.start = mmap(NULL, D_TINY_PAGE_SIZE,	\
			PROT_READ | PROT_WRITE, \
			MAP_PRIVATE | MAP_ANONYMOUS, \
			0, 0);
		if (D_DEBUG == 1)
			printf("map tiny created\n");
		if (tiny.start == MAP_FAILED)
			return (false);
		malloc_data.tiny = &tiny;
	}
	return (true);
}

void	*ft_malloc(size_t size)
{
	if (size <= D_TINY_SIZE)
	{
		if (!ft_check_if_heap_exist(malloc_data.tiny))
			return (NULL);
	}
	else if (size <= D_SMALL_SIZE)
	{
		//todo
	}
	else if (size > D_SMALL_PAGE_SIZE)
	{
		//todo
	}
	printf("[%p] malloc_data\n", &malloc_data);
	printf("[%p] malloc_data->tiny\n", malloc_data.tiny);
	printf("[%p] malloc_data->small\n", malloc_data.small);
	printf("[%p] malloc_data->big\n", malloc_data.big);
	return (NULL);
}
