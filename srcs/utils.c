
#include "malloc.h"

void	print_debug(char *msg)
{
	while (msg++)
		write(1, msg, 1);
}
