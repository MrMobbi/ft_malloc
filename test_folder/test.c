

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "incl/malloc.h"

int	main(void)
{
	char	*tiny = malloc(8);
	if (!tiny)
		return (1);
	char	*tiny1 = malloc(24);
	if (!tiny1)
		return (1);
	char	*tiny2 = malloc(40);
	if (!tiny2)
		return (1);
	char	*tiny3 = malloc(56);
	if (!tiny3)
		return (1);
	char	*tiny4 = malloc(72);
	if (!tiny4)
		return (1);
	char	*tiny5 = malloc(68);
	if (!tiny5)
		return (1);
	char	*tiny6 = malloc(6);
	if (!tiny6)
		return (1);

	free(tiny2);
	free(tiny3);

	char	*small1 = malloc(73);
	if (!small1)
		return (1);
	char	*small2 = malloc(1024);
	if (!small2)
		return (1);
	char	*small3 = malloc(2048);
	if (!small3)
		return (1);
	char	*small4 = malloc(4072);
	if (!small4)
		return (1);
	show_alloc_mem();

	return (0);
}
