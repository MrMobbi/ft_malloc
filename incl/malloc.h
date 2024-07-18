
#ifndef MALLOC_H
# define MALLOC_H

# include <stdio.h>
# include <stdlib.h>

void	*tab_nmap[4096];

typedef struct s_list {
	size_t	size;
	bool	localted;
	void	*data;
}	t_list

void	*ft_malloc(size_t size);

#endif
