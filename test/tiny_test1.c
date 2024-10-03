
#include "malloc.h"

int main(void)
{
	char	*a = malloc(8);	// 0x1020 16 bytes used
	char	*b = malloc(24);	// 0x1030 32 bytes used
	char	*c = malloc(40);	// 0x1050 48 bytes used
	char	*d = malloc(56);	// 0x1080 64 bytes used
	char	*e = malloc(72);	// 0x10c0 80 bytes used


	printf("[%p] a\n",a);
	printf("[%p] b\n",b);
	printf("[%p] c\n",c);
	printf("[%p] d\n",d);
	printf("[%p] e\n",e);

	free(a);
	free(b);

	a = malloc(32);	// 0x1020 48 bytes
	b = malloc(8);	// 0x1110 16 bytes
	char *f = malloc(1);	// 0x1120 16 bytes

	printf("[%p] a\n",a);
	printf("[%p] b\n",b);
	printf("[%p] f\n",f);

	printf("free a\n");
	free(a);
	printf("free b\n");
	free(b);
	printf("free c\n");
	free(c);
	printf("free d\n");
	free(d);
	printf("free e\n");
	free(e);
	printf("free f\n");
	free(f);

	return (0);
}
