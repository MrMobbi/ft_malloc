
#include "malloc.h"

int main(void)
{
	char	*big = ft_malloc(4073);
	void	*big2 = ft_malloc(12830);
	void	*big3 = ft_malloc(1092830);
	void	*big4 = ft_malloc(9999999);
	void	*small1 = ft_malloc(123);
	void	*small2 = ft_malloc(523);
	void	*small3 = ft_malloc(1123);
	void	*small4 = ft_malloc(3123);
	void	*small5 = ft_malloc(4072);
	void	*tiny1 = ft_malloc(8);
	void	*tiny2 = ft_malloc(24);
	void	*tiny3 = ft_malloc(40);
	void	*tiny4 = ft_malloc(56);
	void	*tiny5 = ft_malloc(72);

	show_alloc_mem();
	big2 = ft_realloc(big2 ,10000);
	tiny1 = ft_realloc(tiny1, 24);
	printf("%p\n", tiny1);
	small1 = ft_realloc(small1,250);
	tiny2 = ft_realloc(tiny2, 250);
	show_alloc_mem();
	(void) tiny1;
	(void) tiny2;
	(void) tiny3;
	(void) tiny4;
	(void) tiny5;
	(void) small1;
	(void) small2;
	(void) small3;
	(void) small4;
	(void) small5;
	(void) big;
	(void) big2;
	(void) big3;
	(void) big4;

	return (0);
}
