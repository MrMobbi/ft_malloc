
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
	malloc_data.tiny->start = (struct s_chunk*)malloc_data.tiny + 1;
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

void	*ft_create_new_chunk(size_t size)
{
	unsigned int	offset = (size + sizeof(size_t)) / 16;
	if ((size + sizeof(size_t)) % 16 != 0)
		offset += 1;
	printf("offset -> [%d]\n", offset);
	return (NULL);
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
	printf("[%p] malloc_data->tiny\n", malloc_data.tiny);
	return (NULL);
}
