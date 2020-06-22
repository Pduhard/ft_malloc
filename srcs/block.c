#include "libft_malloc.h"

size_t	get_true_block_size(t_blockhdr *block, t_heaphdr *heap)
{
	if (block->next)
		return ((void *)block->next - (void *)block - sizeof(t_blockhdr));
	return ((void *)heap + heap->size
		- (void *)block - sizeof(t_blockhdr));
}

void	init_block(t_blockhdr *blockaddr, t_blockhdr data)
{
	*blockaddr = data;
}
