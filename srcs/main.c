
#include "malloc.h"

int main(void)
{
	char	*a;

	for (int i = 0; i < 110; i++)
	{
		a = ft_malloc(72);
		printf("[%p] ##### [%d]\n", a, i);
	}
	return (0);
}
