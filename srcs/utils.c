
#include "malloc.h"


size_t	ft_offset_calculator(void *ptr)
{
	size_t	offset = *((size_t*)ptr) >> E_OFFSET_FLAGS;
	offset += E_OFFSET_META;
	if (offset % E_OFFSET_ALGIN > 0)
		offset += E_OFFSET_ALGIN - (offset % E_OFFSET_ALGIN);
	return (offset);
}

size_t	ft_real_size_calculator(size_t size)
{
	size += E_OFFSET_META;
	if (size % E_OFFSET_ALGIN > 0)
		size += E_OFFSET_ALGIN - (size % E_OFFSET_ALGIN);
	size -= E_OFFSET_META;
	return (size);
}

size_t	ft_putnbr_size_t(size_t n)
{
	static int	count;

	count = 0;
	if (n > 9)
	{
		ft_putnbr(n / 10);
		n = n % 10;
	}
	if (n < 10)
		count += ft_putchar(n + '0');
	return (count);
}
int	ft_putnbr(int n)
{
	static int	count;
	int			neg;

	count = 0;
	neg = 0;
	if (n == -2147483648)
		return (write(1, "-2147483648", 11));
	if (n < 0)
	{
		write(1, "-", 1);
		n *= -1;
		neg = 1;
	}
	if (n > 9)
	{
		ft_putnbr(n / 10);
		n = n % 10;
	}
	if (n < 10)
		count += ft_putchar(n + '0');
	if (neg == 1)
		count += 1;
	return (count);
}

int	ft_put_unsinbr(unsigned int n)
{
	static int	count;

	count = 0;
	if (n > 9)
	{
		ft_put_unsinbr(n / 10);
		n = n % 10;
	}
	if (n < 10)
		count += ft_putchar(n + '0');
	return (count);
}

int	ft_putstr(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	if (!str)
		return (write(1, "(null)", 6));
	while (str[i] != '\0')
	{
		count += ft_putchar(str[i]);
		i++;
	}
	return (count);
}

int	ft_putchar(char c)
{
	write (1, &c, 1);
	return (1);
}
