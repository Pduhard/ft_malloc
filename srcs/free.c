/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pduhard- <pduhard-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:05:35 by pduhard-          #+#    #+#             */
/*   Updated: 2020/06/23 01:19:35 by pduhard-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

void	reassign_heap_ptr(t_heaphdr *heap)
{
	t_heaptype htype;

	htype = heap->heaptype;
	if (htype == HP_TINY)
		g_alloc.tiny = heap->next;
	if (htype == HP_SMALL)
		g_alloc.small = heap->next;
	if (htype == HP_LARGE)
		g_alloc.large = heap->next;
}

void	free_heap(t_heaphdr *heap)
{
	if (heap->next)
		heap->next->prev = heap->prev;
	if (!heap->prev)
		reassign_heap_ptr(heap);
	else
		heap->prev->next = heap->next;
	if (munmap(heap, heap->size) == -1)
	{
		ft_putstr("munmap error\n");
	}
}

void	free_block(t_heaphdr *heap, t_blockhdr *block)
{
	if (block->state != ST_FREE)
	{
		block->state = ST_FREE;
		block->user_size = get_true_block_size(block, heap);
	}
	if (block->next && block->next->state == ST_FREE)
	{
		block->user_size += block->next->user_size + sizeof(t_blockhdr);
		block->next = block->next->next;
		if (block->next)
			block->next->prev = block;
	}
	if (block->prev && block->prev->state == ST_FREE)
		return (free_block(heap, block->prev));
	if (!block->next && !block->prev)
		return (free_heap(heap));
}

void	free(void *ptr)
{
	t_heaphdr	*heap;
	t_blockhdr	*block;

	pthread_mutex_lock(&g_mutex);
	if (ptr && find_alloc(ptr, &heap, &block))
		free_block(heap, block);
	pthread_mutex_unlock(&g_mutex);
}
