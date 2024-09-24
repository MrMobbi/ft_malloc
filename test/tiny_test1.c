
#include "malloc.h"

int main(void)
{
	char	*a = ft_malloc(8);	// 0x1020 16 bytes used
	char	*b = ft_malloc(24);	// 0x1030 32 bytes used
	char	*c = ft_malloc(40);	// 0x1050 48 bytes used
	char	*d = ft_malloc(56);	// 0x1080 64 bytes used
	char	*e = ft_malloc(72);	// 0x10c0 80 bytes used


	printf("[%p] a\n",a);
	printf("[%p] b\n",b);
	printf("[%p] c\n",c);
	printf("[%p] d\n",d);
	printf("[%p] e\n",e);

	ft_free(a);
	ft_free(b);

	a = ft_malloc(32);	// 0x1020 48 bytes
	b = ft_malloc(8);	// 0x1110 16 bytes
	char *f = ft_malloc(1);	// 0x1120 16 bytes

	printf("[%p] a\n",a);
	printf("[%p] b\n",b);
	printf("[%p] f\n",f);

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

	printf("[%ld]\n", sizeof(t_heap));

	return (0);
}
