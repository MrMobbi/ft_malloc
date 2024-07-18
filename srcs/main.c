
#include "malloc.h"

int main(int ac, char **av)
{
	(void) ac;

	printf("Hello World\n");
	char *test, *test2;
	test = malloc(sizeof(char) * atoi(av[1]));
	test2 = malloc(sizeof(char) * atoi(av[2]));
	printf("[%ld]\n", sizeof(char) * atoi(av[2]));
	printf("add test [%p]\n", test);
	printf("add test2 [%p]\n", test2);
	free(test);
	free(test2);
	return (0);
}
