#include "libft_malloc.h"

t_alloc         g_alloc = (t_alloc){NULL, NULL, NULL};
pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

t_heaphdr   **get_heap_list(size_t size, e_heaptype *heaptype)
{

    if (size <= TINY_HEAP_BLOCK_SIZE)
    {
        *heaptype = HP_TINY;
        return (&(g_alloc.tiny));
    }
    if (size <= SMALL_HEAP_BLOCK_SIZE)
    {
        *heaptype = HP_SMALL;
        return (&(g_alloc.small));
    }
    *heaptype = HP_LARGE;
    return (&(g_alloc.large));
}

void        update_block(t_blockhdr *block, t_heaphdr *heap, size_t size)
{
    size_t true_size;
    t_blockhdr  *new_block;
    size_t  free_space;
    size_t  size_align;

    true_size = get_true_block_size(block, heap);
    block->user_size = size;
    block->state = ST_USE;
    size_align = size;
    size_align = (size + 15) & (~15);
    free_space = true_size - sizeof(t_blockhdr) - size_align;
    // write()
    if ((int)free_space < 16)
        return ;
    new_block = (t_blockhdr *)((void *)block + sizeof(t_blockhdr) + size_align);
    init_block(new_block, (t_blockhdr){block, block->next, free_space, ST_FREE});
    if (new_block->next)
        new_block->next->prev = new_block;
    block->next = new_block;
    // return (block);
}

t_blockhdr  *find_space_in_heap(t_heaphdr *heap, size_t size)
{
    t_blockhdr *block;

    block = (t_blockhdr *)(heap + 1);
        // pthread_mutex_lock(&g_mutex);
    while (block)
    {

        if (block->state == ST_FREE && block->user_size >= size)
        {
            // pthread_mutex_unlock(&g_mutex);

            update_block(block, heap, size);
            return (block);
        }

        block = block->next;
    }
        // pthread_mutex_unlock(&g_mutex);

    return (NULL);
}

void *malloc(size_t size)
{
    t_heaphdr   **heap_lst_addr;
    t_heaphdr   *heap_lst;
    t_blockhdr  *block;
    e_heaptype  heaptype;
    int         check_inf;

        // return (NULL);
    // if (pthread_mutex_lock(&g_mutex))
        // return (NULL);
    check_inf = 0;
    // ft_putstr("malloc\n");
    // exit(0);
    // pthread_mutex_lock(&g_mutex);

    if (!(heap_lst_addr = get_heap_list(size, &heaptype)))
    {
        return (NULL);
    }
    // pthread_mutex_lock(&g_mutex);
    if (!*heap_lst_addr)
        *heap_lst_addr = new_heap(size, heaptype, NULL);
    heap_lst = *heap_lst_addr;
    // pthread_mutex_unlock(&g_mutex);
    while (heap_lst)
    {

        if ((block = find_space_in_heap(heap_lst, size)))
        {
            // ft_putstr("new allocation\n");
    // show_alloc_mem();

            // write(1, "hall1\n", 6);
            // write(1, "hallo\n", 6);
            // pthread_mutex_unlock(&g_mutex);
            return (block + 1);
        }
        // pthread_mutex_lock(&g_mutex);

        if (!heap_lst->next && !check_inf)
        {
            heap_lst->next = new_heap(size, heaptype, heap_lst);
            check_inf = 1;
        }
        // pthread_mutex_unlock(&g_mutex);

        heap_lst = heap_lst->next;
    }
            // write(1, "hall7\n", 6);
    // pthread_mutex_unlock(&g_mutex);
    // ft_putstr("error\n");
    return (NULL);
    (void)size;
}