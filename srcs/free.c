#include "libft_malloc.h"

void    *blockcheck = NULL;

void           merge_next_block(t_blockhdr *block, t_heaphdr *heap)
{
    write(1, "merge in\n", 9);
    block->size += block->next->size + sizeof(t_blockhdr);
    block->next = block->next->next;
    heap->free_space += sizeof(t_blockhdr);
    if (block->next)
        block->next->prev = block;
    heap->nb_block--;
    write(1, "merge out\n", 11);
}

void     free_heap(t_heaphdr *heap, e_heaptype heaptype)
{
    if (!heap->prev)
        heap_list[heaptype] = heap->next;
    if (heap->prev)
        heap->prev->next = heap->next;
    if (heap->next)
        heap->next->prev = heap->prev;
    if ((munmap(heap, heap->size) == -1))
    {
        // write(2, "munmap error\n", 13);
    }
    write(1, "unmapok\n", 8);
}

static void    free_block(t_heaphdr *heap, t_blockhdr *block, e_heaptype heaptype)
{
    // return ;
    // heap->free_space += block->size;
    // write(1, "freeblock\n", 10);
    // if (heap->nb_block <= 1)
    //     return (free_heap(heap, heaptype));
    // write_addr((unsigned long)block);
    // write(1, "\n", 1);
    // if (block->next && block->next->state == ST_FREE)
    // {
    //     merge_next_block(block, heap);
    // }
    // if (block->prev && block->prev->state == ST_FREE)
    // {
    //     block = block->prev;
    //     merge_next_block(block, heap);
    // }

    write_addr((unsigned long)block);
    write(1, " : prev: ", 9);
    write_addr((unsigned long)block->prev);

    write(1, " : next: ", 9);
    write_addr((unsigned long)block->next);

    write(1, " size: ", 7);
    ft_putnbr(block->size);

    write(1, " state: ", 8);
    ft_putnbr(block->state);
    write(1, "\n", 1);
    // write_addr((unsigned long)block->prev);
    // if (block)
    block->size = 0;
    block->state = ST_FREE;
    blockcheck = block;

    heap->free_space += block->size;
    write(1, "state\n", 6);
    (void)heaptype;
    (void)heap;
    // if (heap->nb_block <= 1)
    //     return (free_heap(heap, heaptype));
    // write(1, "freeblockout\n", 13);
}

static void    find_alloc(t_heaphdr *heap, void *ptr, e_heaptype heaptype)
{
    t_blockhdr  *block;

    block = (t_blockhdr *)(heap + 1);
    // write(1, "freefind\n", 9);
    while (block)
    {
        if ((void *)(block + 1) == ptr)
        {
            // check for space etc..
            // write(1, "ok\n", 3);
            // exit(0);
            write(1, "\nhallo\n", 7);
            // write_addr((unsigned long)block);
            free_block(heap, block, heaptype);
            break ;
        }
        block = block->next;
    }
//  show_alloc_mem();

    // write_addr((unsigned long)ptr);
    // write(1, "\nwrong ptr in find alloc\n", 25);
    // ft_putnbr(size);
    // show_alloc_mem();
// 0x00007fdc7ab7ffb8
    // return (NULL);
}

void free(void *ptr)
{
    // write(2, "free\n", 5);
    t_heaphdr *heaps;

    // return ;
    if (!ptr)
        return ;
    // show_alloc_mem();
    write_addr((unsigned long)ptr);
    // ((t_blockhdr *)ptr - 1)->state = ST_FREE;
    // return ;
    write(1, "\n", 1);
    // show_alloc_mem();
    // return;
    int i = 0;
    while (i < 3)
    {
        heaps = heap_list[i];
        while (heaps)
        {
            // write(1, "rea check heap\n", 15);
            if (ptr > (void *)heaps && ptr < (void *)heaps + heaps->size)
                return (find_alloc(heaps, ptr, i));
            heaps = heaps->next;
        }
        // write(1, "rea next heap\n", 14);

        i++;
    }
    // write(1, "ha\n", 3);
    (void)ptr;
}