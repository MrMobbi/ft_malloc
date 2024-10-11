
#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdint.h>
# include <sys/mman.h>
# include <stdarg.h>

# define D_DEBUG 1

# define D_TINY_SIZE 72
# define D_TINY_PAGE_SIZE 8192

# define D_SMALL_SIZE 4072
# define D_SMALL_PAGE_SIZE 409600

# define D_MAX_META 10000

enum e_offset
{
	E_OFFSET_FLAGS = 3,
	E_OFFSET_HEAP = 24,
	E_OFFSET_META_BIG = 32,
	E_OFFSET_META = 8,
	E_OFFSET_ALGIN = 16,
	E_OFFSET_SIZE_USED = 16,
};

enum e_flag_metadata
{
	E_FREE	= 0,
	E_IN_USE = 1,
	E_RESIZE = 2,
	E_BIG = 4,
	E_GET_FLAGS = 7,
};

// this struct is 24 bytes long
typedef struct s_heap
{
	size_t	size;
	size_t	size_used;
	struct s_heap	*next;
}		t_heap;

// this struct is 24 bytes long
typedef struct s_malloc_data
{
	t_heap	*tiny;
	t_heap	*small;
	t_heap	*big;
}		t_malloc_data;

//	malloc.c
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	free(void *ptr);
void	show_alloc_mem(void);

//	ft_new_chunk.c
void	ft_resize_chunk(void *pos, size_t size);
void	*ft_new_chunk(size_t size, t_heap *heap);

//	show_mem.c
void	ft_show_block(t_heap *heap, char *msg);
void	ft_show_block_big(t_heap *heap);

//	utils.c
size_t	ft_offset_calculator(void *ptr);
size_t	ft_real_size_calculator(size_t size);
int		ft_putchar(char c);
int		ft_putstr(char *str);
int		ft_putnbr(int n);
size_t	ft_putnbr_size_t(size_t n);
int		ft_put_unsinbr(unsigned int n);

//	utils_malloc.c
void	*ft_get_heap(t_heap *heap, size_t size, size_t size_page);
void	ft_update_size_heap(t_heap *heap);
void	*ft_create_new_heap(t_heap *heap, size_t heap_size);
bool	ft_is_tiny(size_t size);
bool	ft_is_small(size_t size);

//	utils_free.c
void	*ft_delete_heap_if_empty(t_heap *heap);
bool	ft_heap_is_empty(t_heap *heap);
void	*ft_find_heap_via_ptr(t_heap *heap, void *ptr);

//	utils_realloc.c
void	*ft_realloc_same_heap(void *pos, size_t size);
void	*ft_realloc_same_big(void *pos, size_t size);
void	*ft_realloc_big(t_heap *heap, void *pos, size_t size);
void	*ft_realloc_all(t_heap *heap, void *pos, size_t size);

//	ft_printf.c
int		ft_printf(const char *str, ...);

#endif
