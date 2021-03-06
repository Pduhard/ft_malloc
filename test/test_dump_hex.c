/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_dump_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pduhard- <pduhard-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:38:26 by pduhard-          #+#    #+#             */
/*   Updated: 2020/06/23 01:39:16 by pduhard-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

int	main(void)
{
	char	*addr;
	int		i;
	int		j;

	i = 0;
	while (i < 100)
	{
		addr = (char *)malloc(256);
		j = 0;
		while (j < 256)
		{
			addr[j] = j;
			++j;
		}
		++i;
	}
	show_alloc_mem_hex();
	return (0);
}
