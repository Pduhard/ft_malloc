/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pduhard- <pduhard-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:05:42 by pduhard-          #+#    #+#             */
/*   Updated: 2020/06/23 01:19:38 by pduhard-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

void	ft_putnbr(unsigned long n)
{
	char	nb;

	if (n > 9)
		ft_putnbr(n / 10);
	nb = (n % 10) + '0';
	if (write(2, &nb, 1) == -1)
		return ;
}
