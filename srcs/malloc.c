#include "libft_malloc.h"

t_alloc		g_alloc = (t_alloc){NULL, NULL, NULL};
pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;

t_heaphdr	**get_heap_list(size_t size, e_heaptype *heaptype)
{
	if (size <= TINY_HEAP_BLOCK_SIZE)
	{
		*heaptype = HP_TINY;
		return (&(g_alloc.tiny));
	}
	if (size <= SMALL_HEAP_BLOCK_SIZE)
	{
		*heaptype = HP_SMALL;
		return (&(g_alloc.small));
	}
	*heaptype = HP_LARGE;
	return (&(g_alloc.large));
}

void		update_block(t_blockhdr *block, t_heaphdr *heap, size_t size)
{
	t_blockhdr	*new_block;
	size_t		true_size;
	size_t		free_space;
	size_t		size_align;

	true_size = get_true_block_size(block, heap);
	block->user_size = size;
	block->state = ST_USE;
	size_align = size;
	size_align = (size + 15) & (~15);
	free_space = true_size - sizeof(t_blockhdr) - size_align;
	if ((int)free_space < 16)
		return ;
	new_block = (t_blockhdr *)((void *)block + sizeof(t_blockhdr) + size_align);
	init_block(new_block, (t_blockhdr){block,
			block->next, free_space, ST_FREE});
	if (new_block->next)
		new_block->next->prev = new_block;
	block->next = new_block;
}

t_blockhdr	*find_space_in_heap(t_heaphdr *heap, size_t size)
{
	t_blockhdr	*block;

	block = (t_blockhdr *)(heap + 1);
	while (block)
	{
		if (block->state == ST_FREE && block->user_size >= size)
		{
			update_block(block, heap, size);
			return (block);
		}
		block = block->next;
	}
	return (NULL);
}

t_blockhdr	*find_heap(t_heaphdr *heap_lst, size_t size, e_heaptype heaptype)
{
	t_blockhdr	*block;
	int			check_inf;

	check_inf = 0;
	while (heap_lst)
	{
		if ((block = find_space_in_heap(heap_lst, size)))
			return (block);
		if (!heap_lst->next && !check_inf)
		{
			heap_lst->next = new_heap(size, heaptype, heap_lst);
			check_inf = 1;
		}
		heap_lst = heap_lst->next;
	}
	return (NULL);
}

void		*malloc(size_t size)
{
	t_heaphdr	**heap_lst_addr;
	t_blockhdr	*block;
	e_heaptype	heaptype;

	pthread_mutex_lock(&g_mutex);
	if (!(heap_lst_addr = get_heap_list(size, &heaptype)))
	{
		pthread_mutex_unlock(&g_mutex);
		return (NULL);
	}
	if (!*heap_lst_addr)
		*heap_lst_addr = new_heap(size, heaptype, NULL);
	block = find_heap(*heap_lst_addr, size, heaptype);
	pthread_mutex_unlock(&g_mutex);
	return (block ? block + 1 : NULL);
}
