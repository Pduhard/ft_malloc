/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pduhard- <pduhard-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:06:10 by pduhard-          #+#    #+#             */
/*   Updated: 2020/06/23 01:19:49 by pduhard-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

void	show_alloc_mem(void)
{
	pthread_mutex_lock(&g_mutex);
	show_alloc_mem_ctrl(INFO);
	pthread_mutex_unlock(&g_mutex);
}
