
#include "malloc.h"

int main(void)
{

	char	*big = ft_malloc(1092830);
	void	*big2 = ft_malloc(1092830);
	void	*big3 = ft_malloc(1092830);
	void	*big4 = ft_malloc(9999999);
	printf("[%p] big\n", big);
	printf("[%p] big2\n", big2);
	printf("[%p] big3\n", big3);
	printf("[%p] big4\n", big4);
	for (int i = 0; i < 26; i++)
		big[i] = 'a' + i;

	ft_realloc(big, 5000);
	big[26] = '\0';
	printf("%s\n", big);

	char	*test = malloc(8);
	for (int i = 0; i < 7; i++)
		test[i] = 'a' + i;
	test[7] = '\0';
	printf("%s\n", test);

	show_alloc_mem();
	free(test);

	return (0);
}
