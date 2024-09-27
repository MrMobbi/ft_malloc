
#include "malloc.h"

void	*ft_handle_realloc(t_heap *heap, void *ptr, size_t size)
{
	(void) heap;
	(void) ptr;
	(void) size;
	return (NULL);
}

void	*ft_realloc_big(t_heap *heap, void *ptr, size_t size)
{
	void	*new;
	ft_free(ptr);
	new = ft_create_new_heap(heap, size);
	return (new + E_OFFSET_META);
}
