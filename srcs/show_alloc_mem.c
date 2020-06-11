#include "libft_malloc.h"
#include <stdio.h>
void    write_addr(unsigned long addr)
{
    // unsigned long   addr;
    unsigned char   hex[16];
    unsigned long   i;

    i = 0;
    // addr = (unsigned long)curr;
    while (i < sizeof(unsigned long))
    {
        hex[i * 2] = (unsigned char)((addr >> ((sizeof(unsigned long) - i - 1) * 8)) & 0xff) / 16;
        hex[i * 2 + 1] = (unsigned char)((addr >> ((sizeof(unsigned long) - i - 1) * 8)) & 0xff) % 16;
        hex[i * 2] += hex[i * 2] > 9 ? ('a' - 10) : '0';
        hex[i * 2 + 1] += hex[i * 2 + 1] > 9 ? ('a' - 10) : '0';
        i++;
    }
    write(1, "0x", 2);
    write(1, hex, 16);
    // write(1, (char *)&addr, sizeof(unsigned long))
}

void    write_heap_header(t_heaphdr *curr)
{
    if (curr->heaptype == HP_TINY)
        write(1, MSG_TINY_HDR, MSG_TINY_HDR_SIZE);
    else if (curr->heaptype == HP_SMALL)
        write(1, MSG_SMALL_HDR, MSG_SMALL_HDR_SIZE);
    else if (curr->heaptype == HP_LARGE)
        write(1, MSG_LARGE_HDR, MSG_LARGE_HDR_SIZE);
    write_addr((unsigned long)curr);
    write(1, " - ", 3);
    //printf("\n%p\n", curr);
    write_addr((unsigned long)curr + curr->size);
    write(1, " heap size :", 11);
    ft_putnbr(curr->size);
    write(1, " free space :", 13);
    ft_putnbr(curr->free_space);
    write(1, "\n", 1);
}

void    write_heap_block(t_blockhdr  *block)
{
    
    unsigned long   block_addr;

    // block = (t_blockhdr *)(curr + 1);
    block_addr = (unsigned long)block;
    block_addr += sizeof(t_blockhdr);
    write_addr(block_addr);
    write(1, " - ", 3);
    write_addr(block_addr + block->size);
    write(1, " : ", 3);
    ft_putnbr(block->size);
    // nb octets;
    write(1, " octets ", 8);
    if (block->state == ST_USE)
        write(1, " octets USE\n", 12);
    else
        write(1, " octets FREE\n", 13);
    //printf("\n%p\n", curr);
    // write(1, "\n", 1);
}

void    write_heap_blocks(t_heaphdr *curr)
{
    t_blockhdr  *block;
    // unsigned long   block_addr;

    block = (t_blockhdr *)(curr + 1);
    while ((void *)block < (void *)curr + curr->size)
    {
        write_heap_block(block);
        block = (void *)block + sizeof(t_blockhdr) + block->size;
    }
    // block_addr = (unsigned long)block;
    // block_addr += sizeof(t_blockhdr);
    // write_addr(block_addr);
    // write(1, " - ", 3);
    // write_addr(block_addr + block->size);
    // write(1, " : ", 3);
    // ft_putnbr(block->size);
    // // nb octets;
    // write(1, " octets\n", 8);
    //printf("\n%p\n", curr);
    // write(1, "\n", 1);
}

void    show_alloc_mem(void)
{
    t_heaphdr   *curr;

// curr = (void *)-1;
    // write_addr(0xff12f33);
    // return ;
    curr = heap;
    while (curr)
    {
        write_heap_header(curr);
        write_heap_blocks(curr);
        curr = curr->next;
    }
    write(1, "end of show\n", 12);
    // exit(0);
}