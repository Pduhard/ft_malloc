/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pduhard- <pduhard-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:05:52 by pduhard-          #+#    #+#             */
/*   Updated: 2020/06/23 01:19:42 by pduhard-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

size_t		get_heap_size(size_t size, t_heaptype heaptype)
{
	size_t	heap_size;
	size_t	page_size;

	if (heaptype == HP_TINY)
		heap_size = (TINY_HEAP_BLOCK_SIZE + sizeof(t_blockhdr)) * NB_BLOCKS;
	if (heaptype == HP_SMALL)
		heap_size = (SMALL_HEAP_BLOCK_SIZE + sizeof(t_blockhdr)) * NB_BLOCKS;
	else
		heap_size = size + sizeof(t_blockhdr);
	page_size = getpagesize() - 1;
	heap_size = (heap_size + sizeof(t_heaphdr) + page_size) & (~page_size);
	return (heap_size);
}

void		init_heap_hdr(t_heaphdr *heap, size_t heap_size,
		t_heaptype heaptype, t_heaphdr *prev)
{
	heap->prev = prev;
	heap->next = NULL;
	heap->heaptype = heaptype;
	heap->size = heap_size;
}

t_heaphdr	*new_heap(size_t size, t_heaptype heaptype, t_heaphdr *prev)
{
	t_heaphdr	*heap;
	size_t		heap_size;

	heap_size = get_heap_size(size, heaptype);
	if ((heap = mmap(NULL, heap_size, PROT_READ | PROT_WRITE,
					MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
	init_heap_hdr(heap, heap_size, heaptype, prev);
	init_block((t_blockhdr *)(heap + 1), (t_blockhdr){
			NULL, NULL,
			heap_size - sizeof(t_blockhdr) - sizeof(t_heaphdr),
			ST_FREE});
	return (heap);
}
