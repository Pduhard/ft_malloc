#include "libft_malloc.h"

void ft_memcpy(void *dst, void *src, size_t size)
{
    unsigned char *s;
    unsigned char *d;

    d = (unsigned char *)dst;
    s = (unsigned char *)src;
    while (size--)
        *d++ = *s++;
}

void *realloc(void *ptr, size_t size)
{
    void        *new_alloc;
    // size_t      old_size;
    size_t      true_size;
    t_heaphdr   *heap;
    t_blockhdr  *block;
    
    // ft_putstr("non\n");

    // exit(0);
    // pthread_mutex_lock(&g_mutex);

    if (!size)
    {
        free(ptr);
        
        // pthread_mutex_unlock(&g_mutex);
        return (NULL);
    }
    if (!ptr)
    {
        // pthread_mutex_unlock(&g_mutex);
        return (malloc(size));
    }
    // ft_putstr("realloc\n");
    if (!find_alloc(ptr, &heap, &block))
    {
        // pthread_mutex_unlock(&g_mutex);
        return (NULL);
    }
    true_size = get_true_block_size(block, heap);
    if (true_size >= size)
    {
        block->user_size = size;
        // pthread_mutex_unlock(&g_mutex);
        return (block + 1);
        // init_block(new_block, (t_blockhdr){block, block->next, free_space, ST_FREE});
    }
    new_alloc = malloc(size);
    // old_size = ((t_blockhdr *)(ptr - sizeof(t_blockhdr)))->user_size;
    ft_memcpy(new_alloc, ptr, block->user_size > size ? size : block->user_size);
    free_block(heap, block);
    // ft_putstr("non\n");

    // pthread_mutex_unlock(&g_mutex);
    return (new_alloc);
    // exit(0);
    return (NULL);
    (void)size;
    (void)ptr;
}