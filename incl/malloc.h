
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

# define D_OFFSET_FLAGS 3

enum e_offset
{
	E_OFFSET_FLAGS = 1,
	E_OFFSET_HEAP = 24,
	E_OFFSET_META = 8,
	E_OFFSET_ALGIN = 16,
};

enum e_flag_metadata
{
	E_FREE	= 0,
	E_IN_USE = 1,
};

// this struct is 16 bytes long
typedef struct s_chunk
{
	size_t		size;
	struct s_chunk	*next;
}		t_chunk;

// this struct is 16 bytes long
typedef struct s_heap
{
	size_t	size;
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
void	ft_free(void *ptr);

#endif
