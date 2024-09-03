
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

typedef struct s_malloc_data
{
		struct s_heap_tiny	*tiny;
		struct s_heap_small	*small;
		struct s_heap_big	*big;

}		t_malloc_data;

typedef struct s_heap_tiny {
	bool	is_init;
	void	*start;
}		t_heap_tiny;

typedef struct s_heap_small {
	bool	is_init;
	void	*start;
}		t_heap_small;

typedef struct s_heap_big {
	void	*start;
	struct s_heap_big	*next;
}		t_heap_big;

void	print_debug(char *msg);
void	*ft_malloc(size_t size);

#endif
