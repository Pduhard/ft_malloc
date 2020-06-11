#include "libft_malloc.h"

t_heaphdr *heap = NULL;

void        add_heap(t_heaphdr *new_heap)
{
    t_heaphdr *lst;
    t_heaphdr *next;

    if (!(lst = heap))
    {
        heap = new_heap;
        return ;
    }
    while (lst->next && lst->next->heaptype < new_heap->heaptype)
        lst = lst->next;
    next = lst->next;
    lst->next = new_heap;
    new_heap->next = next;
}

t_heaphdr   *new_heaphdr(size_t size)
{

    t_heaphdr   new_heap;
    void        *addr;
    // size_t      heapsize;
    // e_heaptype  heaptype;

    if (size < TINY_HEAP_BLOCK_SIZE)
    {
        new_heap.size = TINY_HEAP_ENTITY_SIZE;
        new_heap.heaptype = HP_TINY;
    }
    else if (size < SMALL_HEAP_BLOCK_SIZE)
    {
        new_heap.size = SMALL_HEAP_ENTITY_SIZE;
        new_heap.heaptype = HP_SMALL;
    }
    else
    {
        new_heap.size = (size + sizeof(t_blockhdr) + sizeof(t_heaphdr) + 0xf) & (~0xf);
        new_heap.heaptype = HP_LARGE;
    }
    if ((addr = mmap(NULL, new_heap.size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON , -1, 0)) == MAP_FAILED)
        return (NULL);
    *((t_heaphdr *)addr) = new_heap;
    add_heap((t_heaphdr *)addr);
    return ((t_heaphdr *)addr);
}

void        create_new_block(t_blockhdr *new_block, size_t size, e_state prev_state, e_state state)
{
    new_block->size = size;
    new_block->prev_state = prev_state;
    new_block->state = state;
}

t_blockhdr  *create_free_space(size_t size)
{
    t_heaphdr   *new_heap;
    // t_blockhdr  *new_block;
    // size_t      heapsize;

    if (!(new_heap = new_heaphdr(size)))
        return (NULL);
    // heapsize = new_heaphd->heapsize;
    // new_block = (t_blockhdr *)(new_heap + 1);
    // new_block->size = size;
    // new_block->prev_state = ST_FREE;
    // new_block->state = ST_USE;
    create_new_block((t_blockhdr *)(new_heap + 1),
            size, ST_FREE, ST_USE);
    if (sizeof(t_blockhdr) + size < (size_t)getpagesize())
    {
        create_new_block((t_blockhdr *)(new_heap + 1 + sizeof(t_blockhdr) + size),
            new_heap->size - size - sizeof(t_blockhdr) - sizeof(t_heaphdr),
            ST_USE,
            ST_FREE);
        // new_block = (void *)new_block + sizeof(t_blockhdr) + size;
        // new_block->size = heapsize - size - sizeof(t_blockhdr) - sizeof(t_heaphdr);
        // new_block->prev_state = ST_USE;
        // new_block->state = ST_FREE;
    }
    return ((t_blockhdr *)(new_heap + 1));
}

t_blockhdr  *check_heap_space(size_t size, t_heaphdr *curr)
{
    t_blockhdr  *block;

    block = (t_blockhdr *)(curr + 1);
    while (block)
    {
        if (block->state == ST_FREE && block->size <= size)
            return (block);
            // write(1, "la\n", 3);
        if ((void *)block + block->size + sizeof(t_blockhdr) - (void *)curr > (long)curr->size)
        {
            return (NULL);

            write(1, "nn\n", 3);
        }
        block = (void *)block + block->size + sizeof(t_blockhdr);
    }
            write(1, "nn\n", 3);
        
    return (block);
}

t_blockhdr    *find_free_space(size_t size)
{
    t_blockhdr   *block;
    t_heaphdr    *curr;

    if (!(curr = heap))
        return (create_free_space(size));
    while (curr)
    {
        if (curr->free_space < size && (block = check_heap_space(size, curr)))
            return (block);
        curr = curr->next;
    }
    return (create_free_space(size));
}

void *malloc(size_t size)
{
    t_blockhdr  *block;
    // t_heaphdr   *new_heap;

    if (!(block = find_free_space(size)))
    {
        write(1, "malloc error\n", 13);
        return ((void *)-1);
    }
    write(1, "hallo\n", 6);
    return ((void *)(block + 1));
    (void )size;
}