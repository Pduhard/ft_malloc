/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pduhard- <pduhard-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:05:04 by pduhard-          #+#    #+#             */
/*   Updated: 2020/06/23 01:19:31 by pduhard-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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
