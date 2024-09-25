
#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdint.h>
# include <sys/mman.h>

# define D_DEBUG 1

# define D_TINY_SIZE 72
# define D_TINY_PAGE_SIZE 8192

# define D_SMALL_SIZE 4064
# define D_SMALL_PAGE_SIZE 409600

# define D_MAX_META 10000

enum e_offset
{
	E_OFFSET_FLAGS = 1,
	E_OFFSET_HEAP = 24,
	E_OFFSET_META = 8,
	E_OFFSET_ALGIN = 16,
	E_OFFSET_SIZE_USED = 16,
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
	size_t	size_used;
	struct s_heap	*next;
}		t_heap;

typedef struct s_malloc_data
{
	t_heap	*tiny;
	t_heap	*small;
	t_heap	*big;
}		t_malloc_data;

//	malloc.c
void	*ft_malloc(size_t size);
void	ft_free(void *ptr);
void	show_alloc_mem(void);

// ft_new_chunk.c
void	*ft_new_chunk(size_t size, void *tiny);

//	SHOW_MEM
void	ft_show_block(t_heap *heap, char *msg);

//	utils.c
size_t	ft_offset_calculator(void *ptr);

//	utils_malloc.c
void	*ft_get_heap(t_heap *heap, size_t size, size_t size_page);
void	ft_update_size_heap(size_t size, t_heap *heap);
void	*ft_create_new_heap(t_heap *heap, size_t heap_size);

//	utils_free.c
void	*ft_delete_heap_if_empty(t_heap *heap);
bool	ft_heap_is_empty(t_heap *heap);
void	*ft_find_heap_via_ptr(t_heap *heap, void *ptr);

#endif
