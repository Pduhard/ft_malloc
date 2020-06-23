/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pduhard- <pduhard-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:05:49 by pduhard-          #+#    #+#             */
/*   Updated: 2020/06/23 01:20:46 by pduhard-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

size_t	ft_strlen(char *str)
{
	char	*str2;

	str2 = str;
	while (*str2)
		++str2;
	return ((size_t)(str2 - str));
}
