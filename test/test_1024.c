/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_1024.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pduhard- <pduhard-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:36:40 by pduhard-          #+#    #+#             */
/*   Updated: 2020/06/23 01:41:37 by pduhard-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

int	main(void)
{
	char	*addr;
	int		i;
	int		j;

	i = 0;
	while (i < 1024)
	{
		addr = (char *)malloc(1024);
		j = 0;
		while (j < 1024)
			addr[j++] = 42;
		free(addr);
		i++;
	}
	return (0);
}
