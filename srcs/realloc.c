#include "libft_malloc.h"

void    *copy_block(t_blockhdr *new_block, t_blockhdr *old_block, size_t size)
{
    size_t  i;
    unsigned char   *src;
    unsigned char   *dst;

    i = 0;
    dst = (unsigned char *)(new_block + 1);
    src = (unsigned char *)(old_block + 1);
    while (i < size && i < old_block->size)
    {
        *dst = *src;
        dst++;
        src++;
        i++;
    }
    return new_block;
}

void    *find_alloc(t_heaphdr *heap, size_t size, void *ptr)
{
    t_blockhdr  *block;

    block = (t_blockhdr *)(heap + 1);
    while (block)
    {
        if ((void *)(block + 1) == ptr)
        {
            // check for space etc..
            return (copy_block(malloc(size) - sizeof(block), block, size));
        }
        block = block->next;
    }
    write(1, "ajh\n", 4);

    return (NULL);
}

void *realloc(void *ptr, size_t size)
{
    t_heaphdr   *heaps;

    if (!ptr)
        return (malloc(size));
    if (ptr && !size)
    {
        free(ptr);
        return (NULL);
    }
    // htype = get_heap_type(size);
    int i = 0;
    while (i < 3)
    {
        heaps = heap_list[i];
        while (heaps)
        {
            if (ptr > (void *)heaps && ptr < (void *)heaps + heaps->size)
                return (find_alloc(heaps, size, ptr));
            heaps = heaps->next;
        }
        i++;
    }
    write(1, "ajh\n", 4);
    // t_heaphdr   *curr;
    // t_blockhdr  *block;

    // write(2, "realloc=>newmalloc\n", sizeof("realloc=>newmalloc\n"));
    // curr = heap;
    // void *new_ptr = malloc(size);
    // if (!ptr)
    //     return (new_ptr);
    // // return (new_ptr);
    // if (size == 0)
    //     return (NULL);
    // if (ptr && !size)
    //     free(ptr);
    //     int turn = 0;
    // while (curr)
    // {
    //     turn++;

    //     block = (t_blockhdr *)(curr + 1);
    //     while ((void *)block < (void *)curr + curr->size
    //         && (void *)(block + 1) != ptr)
    //     {
    //         // ft_putnbr((long)block + 1);
    //     // write_addr((unsigned long)(block + 1));
    //     //     write(2, " - ", 3);
    //     // write_addr((unsigned long)(ptr));
    //         // ft_putnbr((long)ptr);
    //         // write(2, "\n", 1);

    //         block = (void *)block + block->size + sizeof(t_blockhdr);
    //     }
    //     // write_addr((unsigned long)(block + 1));
    //     // write(1, " == ", 4);
    //     // write_addr((unsigned long)(ptr));
    //     // write(1, "\n", 1);

    //     if ((void *)block < (void *)curr + curr->size
    //         && (void *)(block + 1) == ptr)
    // //    if ((void *)(curr + 1) + sizeof(t_blockhdr) == ptr)
    //     {
    //         write(2, "finded\n", 7);

    //         // exit(0);
    //         for (size_t i = 0; i < block->size && i < size; ++i)
    //         {
    //             *((unsigned char *)new_ptr + i) = *((unsigned char *)(block + 1) + i);
    //             // exit(0);
    //         }
    //         return (new_ptr);
    //     }
    //     curr = curr->next;

    // }

    // // exit(0);

    // write(2, "noo?\n", 5);
    // write_addr((unsigned long)ptr);
    // exit(0);
    // show_alloc_mem();
    //     if (turn == 2)
        // exit(0);
    return (NULL);
    (void)size;
    (void)ptr;
}