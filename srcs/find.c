#include "libft_malloc.h"

int	check_in_heap_list(void *ptr, t_heaphdr *heap_lst,
		t_heaphdr **heap_addr, t_blockhdr **block_addr)
{
	t_blockhdr *block_lst;

	while (heap_lst)
	{
		if (ptr > (void *)heap_lst && ptr < (void *)heap_lst + heap_lst->size)
		{
			block_lst = (t_blockhdr *)(heap_lst + 1);
			while (block_lst)
			{
				if ((void *)(block_lst + 1) == ptr)
				{
					*heap_addr = heap_lst;
					*block_addr = block_lst;
					return (1);
				}
				block_lst = block_lst->next;
			}
		}
		heap_lst = heap_lst->next;
	}
	return (0);
}

int	find_alloc(void *ptr, t_heaphdr **heap_addr, t_blockhdr **block_addr)
{
	if (check_in_heap_list(ptr, g_alloc.tiny, heap_addr, block_addr) ||
			check_in_heap_list(ptr, g_alloc.small, heap_addr, block_addr) ||
			check_in_heap_list(ptr, g_alloc.large, heap_addr, block_addr))
		return (1);
	return (0);
}
