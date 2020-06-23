/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_multithread.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pduhard- <pduhard-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:42:52 by pduhard-          #+#    #+#             */
/*   Updated: 2020/06/23 01:44:13 by pduhard-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "libft_malloc.h"

void	*alloc_and_free(void *param)
{
	char	*mem;
	int		i;

	i = 0;
	while (i < 1024)
	{
		mem = malloc(1024);
		i++;
		free(mem);
	}
	show_alloc_mem();
	show_alloc_mem_hex();
	pthread_exit(NULL);
	(void)param;
}

int		main(int argc, char **argv)
{
	pthread_t	threads[4];
	int			i;

	i = 0;
	while (i < 4)
		if (pthread_create(&(threads[i++]), NULL, alloc_and_free,
			(void *)argv))
			return (0);
	i = 0;
	while (i < 4)
		pthread_join(threads[i++], NULL);
}
