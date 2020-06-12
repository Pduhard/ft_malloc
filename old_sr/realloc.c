#include "libft_malloc.h"

void *realloc(void *ptr, size_t size)
{
    t_heaphdr   *curr;
    t_blockhdr  *block;

    write(2, "realloc=>newmalloc\n", sizeof("realloc=>newmalloc\n"));
    curr = heap[0];
    void *new_ptr = malloc(size);
    if (!ptr)
        return (new_ptr);
    // return (new_ptr);
    if (size == 0)
        return (NULL);
        return (NULL);
    if (ptr && !size)
        free(ptr);
        int turn = 0;
    while (curr)
    {
        turn++;

        block = (t_blockhdr *)(curr + 1);
        while ((void *)block < (void *)curr + curr->size
            && (void *)(block + 1) != ptr)
        {
            // ft_putnbr((long)block + 1);
        write_addr((unsigned long)(block + 1));
            write(2, " - ", 3);
        write_addr((unsigned long)(ptr));
            // ft_putnbr((long)ptr);
            write(2, "\n", 1);

            block = (void *)block + block->size + sizeof(t_blockhdr);
        }
        write_addr((unsigned long)(block + 1));
        write(1, " == ", 4);
        write_addr((unsigned long)(ptr));
        write(1, "\n", 1);

        if ((void *)block < (void *)curr + curr->size
            && (void *)(block + 1) == ptr)
    //    if ((void *)(curr + 1) + sizeof(t_blockhdr) == ptr)
        {
            write(2, "finded\n", 7);

            // exit(0);
            for (size_t i = 0; i < block->size && i < size; ++i)
            {
                *((unsigned char *)new_ptr + i) = *((unsigned char *)(block + 1) + i);
                // exit(0);
            }
            return (new_ptr);
        }
        curr = curr->next;

    }

    // exit(0);

    write(2, "noo?\n", 5);
    show_alloc_mem();
        if (turn == 2)
        exit(0);
    return (NULL);
    (void)size;
    (void)ptr;
}