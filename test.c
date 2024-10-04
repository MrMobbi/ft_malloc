
#include "incl/malloc.h"

int	main(void)
{
	char	*str = malloc(8);
	char	*str1 = malloc(10);
	char	*str2 = malloc(10);
	char	*str3 = malloc(72);
	char	*str4 = malloc(10);
	char	*str5 = malloc(10);
	char	*str6 = malloc(10);
	char	*str7 = malloc(10);
	char	*str8 = malloc(10);
	show_alloc_mem();
	for (int i = 0; i < 9; i++)
		str[i] ='a';
	str[9] = '\0';
	(void) str1;
	(void) str2;
	(void) str3;
	(void) str4;
	(void) str5;
	(void) str6;
	(void) str7;
	(void) str8;
	str3 = realloc(str3, 8);
	str1 = realloc(str1,1233);
	str = realloc(str, 56);
	show_alloc_mem();
	return (0);
}
