#include "libft_malloc.h"

void	ft_memcpy(void *dst, void *src, size_t size)
{
	unsigned char	*s;
	unsigned char	*d;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	while (size--)
		*d++ = *s++;
}

int	find_realloc(void *ptr, size_t size,
		t_heaphdr **heap_addr, t_blockhdr **block_addr)
{
	*heap_addr = NULL;
	*block_addr = NULL;
	if (!size)
		free(ptr);
	else if (!ptr)
		*block_addr = (void *)-1;
	else if (!find_alloc(ptr, heap_addr, block_addr))
		return (0);
	else
		return (1);
	return (0);
}

void	*realloc(void *ptr, size_t size)
{
	void		*new_alloc;
	size_t		true_size;
	t_heaphdr	*heap;
	t_blockhdr	*block;

	new_alloc = NULL;
	pthread_mutex_lock(&g_mutex);
	if (!find_realloc(ptr, size, &heap, &block))
	{
		pthread_mutex_unlock(&g_mutex);
		return (block ? malloc(size) : NULL);
	}
	true_size = get_true_block_size(block, heap);
	if (true_size >= size)
	{
		block->user_size = size;
		pthread_mutex_unlock(&g_mutex);
		return (block + 1);
	}
	pthread_mutex_unlock(&g_mutex);
	new_alloc = malloc(size);
	ft_memcpy(new_alloc, ptr, block->user_size > size
		? size : block->user_size);
	free_block(heap, block);
	return (new_alloc);
}
