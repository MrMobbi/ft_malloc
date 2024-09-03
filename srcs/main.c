
#include "malloc.h"

int main(int ac, char **av)
{
	(void) ac;
	(void) av;

	char *test = ft_malloc(sizeof(char) * 6);

	test[0] = 'a';
	test[1] = 'b';
	test[2] = 'c';
	test[3] = 'd';
	test[4] = 'e';
	test[6] = '\0';

	printf("[%s]\n", test);
	return (0);
}
