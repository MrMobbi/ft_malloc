
#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdint.h>
# include <sys/mman.h>

# define D_DEBUG 1

# define D_TINY_SIZE 32
# define D_TINY_PAGE_SIZE 4096

# define D_SMALL_SIZE 512
# define D_SMALL_PAGE_SIZE 53248

typedef struct s_chunk
{
	size_t		size;
	struct s_chunk	*next;
}		t_chunk;

typedef struct s_heap
{
	size_t	size;
	struct s_chunk	*start;
	struct s_heap	*next;
}		t_heap;

typedef struct s_malloc_data
{
	t_heap	*tiny;
	t_heap	*small;
	t_heap	*big;
}		t_malloc_data;

void	print_debug(char *msg);
void	*ft_malloc(size_t size);

#endif
