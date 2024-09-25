
#include "malloc.h"

int main(void)
{
	show_alloc_mem();
	char	*a = ft_malloc(72);
	char	*b = ft_malloc(72);
	char	*c = ft_malloc(4064);
	char	*d = ft_malloc(4064);
	char	*e = ft_malloc(73);
	char	*f = ft_malloc(5000);
	char	*g = ft_malloc(5000);

	printf("[%p] address a\n", a);
	printf("[%p] address b\n", b);
	printf("[%p] address c\n", c);
	printf("[%p] address d\n", d);
	printf("[%p] address e\n", e);
	printf("[%p] address f\n", f);
	printf("[%p] address g\n", g);

	printf("\n\n");
	show_alloc_mem();

	printf("\n\n### FREE ###\n\n");
	printf("free a\n");
	ft_free(a);
	printf("free b\n");
	ft_free(b);
	printf("free c\n");
	ft_free(c);
	printf("free d\n");
	ft_free(d);
	printf("free e\n");
	ft_free(e);
	printf("free f\n");
	ft_free(f);
	return (0);
}
