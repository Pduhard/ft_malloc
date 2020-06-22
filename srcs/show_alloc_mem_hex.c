#include "libft_malloc.h"

void	write_addr(void *addr)
{
	unsigned long			nb;
	char			hex[2];
	int				i;

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

void	show_heap_hdr(t_heaphdr *heap)
{
	if (heap->heaptype == HP_TINY)
		ft_putstr("\nHeap : TINY - size : ");
	else if (heap->heaptype == HP_SMALL)
		ft_putstr("\nHeap : SMALL - size : ");
	else
		ft_putstr("\nHeap : LARGE - size : ");
	ft_putnbr(heap->size);
	ft_putstr(" bytes\nHeap range: ");
	write_addr(heap);
	ft_putstr(" - ");
	write_addr((void *)heap + heap->size);
	ft_putstr("\n");
}

void	show_block_hdr(t_blockhdr *block, t_heaphdr *heap,
		unsigned long long sizes[3])
{
	ft_putstr("\n\tBlock ");
	if (block->state == ST_USE)
		ft_putstr("(\x1b[1;31mUSE\x1b[0m) ");
	else if (block->state == ST_FREE)
		ft_putstr("(\x1b[1;32mFREE\x1b[0m)");
	ft_putstr(" addr : ");
	write_addr(block + 1);
	ft_putstr(" size : ");
	ft_putnbr(block->user_size);
	ft_putstr(" bytes - true_size : ");
	ft_putnbr(get_true_block_size(block, heap));
	ft_putstr(" bytes\n");
	if (block->state == ST_USE)
		sizes[0] += block->user_size;
	else
		sizes[1] += block->user_size;
}

void	dump_char(unsigned char *mem, t_blockhdr *block, size_t i)
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

void	dump_memory(t_blockhdr *block)
{
	size_t		i;
	unsigned char	*mem;
	char		hex[3];

	hex[2]= ' ';
	mem = (unsigned char *)(block + 1);
	i = 0;
	write(1, "\n", 1);
	while (i < block->user_size || (i & 0xf))
	{
		if (!(i & 0xf))
		{
			write_addr((void *)(block + 1) + i);
			write(1, "  ", 2);
		}
		if (i < block->user_size)
		{
			hex[0] = (*mem & 0xf0) >> 4;
			hex[1] = (*mem & 0x0f);
			hex[0] += hex[0] < 10 ? '0' : ('a' - 10);
			hex[1] += hex[1] < 10 ? '0' : ('a' - 10);
		}
		else
		{
			hex[0] = ' ';
			hex[1] = ' ';
		}
		write(1, hex, 3);
		mem++;
		i++;
		if (!(i & 0xf))
			dump_char(mem, block, i);
	}
}

void	show_blocks(t_blockhdr *block, t_heaphdr *heap,
		unsigned long long  sizes[3], int ctrl)
{
	while (block)
	{
		show_block_hdr(block, heap, sizes);
		if (block->state == ST_USE && ctrl == HEX)
			dump_memory(block);
		block = block->next;

	}
}

void	show_heap(t_heaphdr *heap, unsigned long long  sizes[3], int ctrl)
{
	while (heap)
	{
		show_heap_hdr(heap);
		show_blocks((t_blockhdr *)(heap + 1), heap, sizes, ctrl);
		sizes[2] += heap->size;
		heap = heap->next;
	}
}

void	show_alloc_mem_ctrl(int ctrl)
{
	unsigned long long  sizes[3];

	sizes[0] = 0;
	sizes[1] = 0;
	sizes[2] = 0;
	show_heap(g_alloc.tiny, sizes, ctrl);
	show_heap(g_alloc.small, sizes, ctrl);
	show_heap(g_alloc.large, sizes, ctrl);
	ft_putstr("\n\tTotal memory used : ");
	ft_putnbr(sizes[2]);
	ft_putstr(" bytes\n\tTotal allocated memory : ");
	ft_putnbr(sizes[0]);
	ft_putstr(" bytes\n\tTotal available memory : ");
	ft_putnbr(sizes[1]);
	ft_putstr(" bytes\n\tTotal memory used by headers : ");
	ft_putnbr(sizes[2] - sizes[0] - sizes[1]);
	ft_putstr(" bytes\n\n");

}

void	show_alloc_mem_hex()
{
	pthread_mutex_lock(&g_mutex);
	show_alloc_mem_ctrl(HEX);
	pthread_mutex_unlock(&g_mutex);
}
