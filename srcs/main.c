
#include "malloc.h"

int main(int ac, char **av)
{
	(void) ac;
	(void) av;

	char	*a = ft_malloc(8); // 0x1020
	char	*b = ft_malloc(9); // 0x1030
	char	*c = ft_malloc(32); // 0x1050
	char	*d = ft_malloc(8); // 0x1080
	char	*e = ft_malloc(8); // 0x1090
	
	printf("[%p] a\n",a);
	printf("[%p] b\n",b);
	printf("[%p] c\n",c);
	printf("[%p] d\n",d);
	printf("[%p] e\n",e);

	ft_free(a);
	ft_free(b);

	a = ft_malloc(32); // 0x1020
	b = ft_malloc(8); // 0x10a0
					  
	printf("[%p] a\n",a);
	printf("[%p] b\n",b);

	ft_free(a);
	ft_free(b);
	ft_free(c);
	ft_free(d);
	ft_free(e);

	return (0);
}
