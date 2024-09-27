
#include "malloc.h"

int main(void)
{

	void	*big = ft_malloc(1092830);
	void	*big2 = ft_malloc(1092830);
	void	*big3 = ft_malloc(1092830);
	void	*big4 = ft_malloc(9999999);
	printf("[%p] big\n", big);
	printf("[%p] big2\n", big2);
	printf("[%p] big3\n", big3);
	printf("[%p] big4\n", big4);

	show_alloc_mem();

	return (0);
}
