/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pduhard- <pduhard-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:05:20 by pduhard-          #+#    #+#             */
/*   Updated: 2020/06/23 01:19:32 by pduhard-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

void	*calloc(size_t nmemb, size_t size)
{
	void *alloc;

	if (!nmemb || !size)
		return (NULL);
	alloc = malloc(size * nmemb);
	if (alloc && (size || nmemb))
		ft_bzero(alloc, size * nmemb);
	return (alloc);
}
