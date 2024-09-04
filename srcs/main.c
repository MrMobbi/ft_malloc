
#include "malloc.h"

int main(int ac, char **av)
{
	(void) ac;
	(void) av;

	char *test = ft_malloc(sizeof(char) * 9);


	(void) test;
	return (0);
}
