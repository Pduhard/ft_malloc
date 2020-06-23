/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defragment_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pduhard- <pduhard-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:21:23 by pduhard-          #+#    #+#             */
/*   Updated: 2020/06/23 01:37:12 by pduhard-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

static void	show_allc(void *mem)
{
	ft_putstr("=================================\n");
	show_alloc_mem();
	if (mem)
		free(mem);
}

int			main(void)
{
	void	*mem[6];
	int		i;

	i = 0;
	while (i < 6)
		mem[i++] = malloc(128);
	show_allc(mem[1]);
	show_allc(mem[0]);
	show_allc(mem[2]);
	show_allc(mem[4]);
	show_allc(mem[3]);
	show_allc(mem[5]);
	show_allc(NULL);
	return (0);
}
