#include "libft_malloc.h"

void    *copy_block(t_blockhdr *new_block, t_blockhdr *old_block, size_t size, int unk_addr)
{
    size_t  i;
    unsigned char   *src;
    unsigned char   *dst;
    size_t  old_size;


    i = 0;
    old_size = unk_addr ? size : old_block->size;
    // exit(0);
    // write(1, "nroaml\n", 7);
    dst = (unsigned char *)(new_block + 1);
    src = (unsigned char *)(old_block + 1);
    // write(1, "size: ", 6);
    // ft_putnbr(size);

    // write(1, "olb_blocksize: ", 15);
    // ft_putnbr(old_block->size);
    // write(1, ":: i = ", 7);
    while (i < size && i < old_size)
    {
        // write(1, "copy\n", 5);
        *dst = *src;
        dst++;
        src++;
        i++;
    }
    // ft_putnbr(i);
    // write(1, "\n", 1);
    // write(1, "new_alloc: ", 11);
    // write_addr((long)new_block + sizeof(t_blockhdr));
    // write(1, "\n", 1);
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
            // write(1, "ok\n", 3);
            // exit(0);
            // write()
            return (copy_block(malloc(size) - sizeof(t_blockhdr), block, size, 0));
        }
        block = block->next;
    }
    // write_addr((unsigned long)ptr);
    // write(1, "\nwrong ptr in find alloc\n", 25);
    // ft_putnbr(size);
    // show_alloc_mem();
// 0x00007fdc7ab7ffb8
    return (NULL);
}

void *realloc(void *ptr, size_t size)
{
    t_heaphdr   *heaps;

    size = (size + 15) & (~15);
    if (!ptr)
        return (malloc(size));
    if (ptr && !size)
    {
        free(ptr);
        return (NULL);
    }
    // return (NULL);
    // htype = get_heap_type(size);
    // write(1, "realloc ptr: ", 12);
    // write_addr((unsigned long)ptr);

    // write(1, "\nheap loop start\n", 17);
    int i = 0;
    while (i < 3)
    {
        heaps = heap_list[i];
        while (heaps)
        {
            // write(1, "rea check heap\n", 15);
            if (ptr > (void *)heaps && ptr < (void *)heaps + heaps->size)
                return (find_alloc(heaps, size, ptr) + sizeof(t_blockhdr));
            heaps = heaps->next;
        }
        // write(1, "rea next heap\n", 14);

        i++;
    }
    // return ((void *)-1);
    return (copy_block(malloc(size) - sizeof(t_blockhdr), ptr - sizeof(t_blockhdr), size, 1) + sizeof(t_blockhdr));
    write(1, (char *)ptr, 156);
    write(1, "ajh\n", 4);
    write_addr((unsigned long)ptr);
    write(1, "\nwrong ptr\n", 11);
    ft_putnbr(size);
    show_alloc_mem();
    exit(0);
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