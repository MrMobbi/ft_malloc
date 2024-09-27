
#include "malloc.h"

// ## Hexa ##
static int	ft_put_address_hexa(unsigned long long nbr)
{
	static int	count;

	count = 0;
	if (nbr > 15)
	{
		ft_put_address_hexa(nbr / 16);
		nbr = nbr % 16;
	}
	if (nbr <= 9)
		count += ft_putchar(nbr + '0');
	if (nbr >= 10 && nbr <= 15)
		count += ft_putchar(nbr + 87);
	return (count);
}

static int	ft_put_hexa(unsigned int nbr)
{
	static int	count;

	count = 0;
	if (nbr > 15)
	{
		ft_put_hexa(nbr / 16);
		nbr = nbr % 16;
	}
	if (nbr <= 9)
		count += ft_putchar(nbr + '0');
	if (nbr >= 10 && nbr <= 15)
		count += ft_putchar(nbr + 87);
	return (count);
}

static int	ft_put_uphexa(unsigned int nbr)
{
	static int	count1;

	count1 = 0;
	if (nbr > 15)
	{
		ft_put_uphexa(nbr / 16);
		nbr = nbr % 16;
	}
	if (nbr <= 9)
		count1 += ft_putchar(nbr + '0');
	if (nbr >= 10 && nbr <= 15)
		count1 += ft_putchar(nbr + 55);
	return (count1);
}

// ## sort ##
static int	ft_sort(va_list args, char c)
{
	int	count;

	count = 0;
	if (c == 'd' || c == 'i')
		count = ft_putnbr(va_arg(args, int));
	if (c == '%')
		count = write(1, "%", 1);
	if (c == 's')
		count = ft_putstr(va_arg(args, char *));
	if (c == 'c')
		count = ft_putchar(va_arg(args, int));
	if (c == 'u')
		count = ft_put_unsinbr(va_arg(args, unsigned int));
	if (c == 'x')
		count = ft_put_hexa(va_arg(args, unsigned int));
	if (c == 'X')
		count = ft_put_uphexa(va_arg(args, unsigned int));
	if (c == 'p')
	{
		count = write(1, "0x", 2);
		count += ft_put_address_hexa(va_arg(args, unsigned long long));
	}
	return (count);
}

int	ft_printf(const char *str, ...)
{
	int		count;
	va_list	args;
	size_t	i;

	i = 0;
	va_start(args, str);
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			count += ft_sort(args, str[i + 1]);
			i += 2;
		}
		else
			count += ft_putchar(str[i++]);
	}
	va_end(args);
	return (count);
}
