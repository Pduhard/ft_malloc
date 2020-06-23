/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pduhard- <pduhard-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:06:12 by pduhard-          #+#    #+#             */
/*   Updated: 2020/06/23 01:19:50 by pduhard-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

void	write_addr(void *addr)
{
	long		nb;
	char		hex[2];
	size_t		i;

	nb = (unsigned long)addr;
	ft_putstr("0x");
	i = 0;
	while (i++ < 8)
	{
		hex[0] = ((nb >> (56)) & 0xff) / 16;
		hex[1] = ((nb >> (56)) & 0xff) % 16;
		hex[0] += hex[0] < 10 ? '0' : ('a' - 10);
		hex[1] += hex[1] < 10 ? '0' : ('a' - 10);
		nb <<= 8;
		write(1, hex, 2);
	}
}

void	dump_char(char *mem, t_blockhdr *block, size_t i)
{
	size_t j;

	j = 0;
	write(1, " |", 2);
	mem -= 16;
	while (j < 16)
	{
		if (i - 16 + j >= block->user_size)
			break ;
		if (*mem >= 32 && *mem <= 127)
			write(1, mem, 1);
		else
			write(1, ".", 1);
		j++;
		mem++;
	}
	write(1, "|\n", 2);
}

void	write_next_byte(size_t i, size_t size,
		char mem)
{
	char		hex[3];

	hex[2] = ' ';
	if (i < size)
	{
		hex[0] = (mem & 0xf0) >> 4;
		hex[1] = (mem & 0x0f);
		hex[0] += hex[0] < 10 ? '0' : ('a' - 10);
		hex[1] += hex[1] < 10 ? '0' : ('a' - 10);
	}
	else
	{
		hex[0] = ' ';
		hex[1] = ' ';
	}
	write(1, hex, 3);
}

void	dump_memory(t_blockhdr *block)
{
	size_t		i;
	char		*mem;

	mem = (char *)(block + 1);
	i = 0;
	write(1, "\n", 1);
	while (i < block->user_size || (i & 0xf))
	{
		if (!(i & 0xf))
		{
			write_addr((void *)(block + 1) + i);
			write(1, "  ", 2);
		}
		write_next_byte(i, block->user_size, *mem);
		mem++;
		i++;
		if (!(i & 0xf))
			dump_char(mem, block, i);
	}
}
