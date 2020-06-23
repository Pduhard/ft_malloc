/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_hex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pduhard- <pduhard-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:06:07 by pduhard-          #+#    #+#             */
/*   Updated: 2020/06/23 01:19:47 by pduhard-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

void	show_heap_hdr(t_heaphdr *heap)
{
	if (heap->heaptype == HP_TINY)
		ft_putstr("\nHeap : TINY - size : ");
	else if (heap->heaptype == HP_SMALL)
		ft_putstr("\nHeap : SMALL - size : ");
	else
		ft_putstr("\nHeap : LARGE - size : ");
	ft_putnbr(heap->size);
	ft_putstr(" bytes\nHeap range: ");
	write_addr(heap);
	ft_putstr(" - ");
	write_addr((void *)heap + heap->size);
	ft_putstr("\n");
}

void	show_block_hdr(t_blockhdr *block, t_heaphdr *heap,
		unsigned long long sizes[3])
{
	ft_putstr("\n\tBlock ");
	if (block->state == ST_USE)
		ft_putstr("(\x1b[1;31mUSE\x1b[0m) ");
	else if (block->state == ST_FREE)
		ft_putstr("(\x1b[1;32mFREE\x1b[0m)");
	ft_putstr(" addr : ");
	write_addr(block + 1);
	ft_putstr(" size : ");
	ft_putnbr(block->user_size);
	ft_putstr(" bytes - true_size : ");
	ft_putnbr(get_true_block_size(block, heap));
	ft_putstr(" bytes\n");
	if (block->state == ST_USE)
		sizes[0] += block->user_size;
	else
		sizes[1] += block->user_size;
}

void	show_heap(t_heaphdr *heap, unsigned long long sizes[3], int ctrl)
{
	t_blockhdr *block;

	while (heap)
	{
		show_heap_hdr(heap);
		block = (t_blockhdr *)(heap + 1);
		while (block)
		{
			show_block_hdr(block, heap, sizes);
			if (block->state == ST_USE && ctrl == HEX)
				dump_memory(block);
			block = block->next;
		}
		sizes[2] += heap->size;
		heap = heap->next;
	}
}

void	show_alloc_mem_ctrl(int ctrl)
{
	unsigned long long	sizes[3];

	sizes[0] = 0;
	sizes[1] = 0;
	sizes[2] = 0;
	show_heap(g_alloc.tiny, sizes, ctrl);
	show_heap(g_alloc.small, sizes, ctrl);
	show_heap(g_alloc.large, sizes, ctrl);
	ft_putstr("\n\tTotal memory used : ");
	ft_putnbr(sizes[2]);
	ft_putstr(" bytes\n\tTotal allocated memory : ");
	ft_putnbr(sizes[0]);
	ft_putstr(" bytes\n\tTotal available memory : ");
	ft_putnbr(sizes[1]);
	ft_putstr(" bytes\n\tTotal memory used by headers : ");
	ft_putnbr(sizes[2] - sizes[0] - sizes[1]);
	ft_putstr(" bytes\n\n");
}

void	show_alloc_mem_hex(void)
{
	pthread_mutex_lock(&g_mutex);
	show_alloc_mem_ctrl(HEX);
	pthread_mutex_unlock(&g_mutex);
}
