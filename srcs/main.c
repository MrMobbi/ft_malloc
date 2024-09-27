
#include "malloc.h"

int main(void)
{
	void	*a = ft_malloc(73);
	void	*b = ft_malloc(73);
	void	*c = ft_malloc(73);

	printf("[%p] address a\n", a);
	printf("[%p] address a\n", b);
	printf("[%p] address a\n", c);
	return (0);
}
