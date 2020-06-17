#include "libft_malloc.h"

t_heaphdr *heap_list[3] = {NULL, NULL, NULL};

e_heaptype  get_heap_type(size_t size)
{
    if (size < TINY_HEAP_BLOCK_SIZE)
        return (HP_TINY);
    else if (size < SMALL_HEAP_BLOCK_SIZE)
        return (HP_SMALL);
    return (HP_LARGE);
}

void        init_heap_first_block(t_heaphdr *heap)
{
    t_blockhdr *block;

    block = (t_blockhdr *)(heap + 1);
    block->prev = NULL;
    block->next = NULL;
    block->size = heap->free_space;
    block->state = ST_FREE;
}

t_heaphdr   *new_heap(size_t size, e_heaptype heaptype, t_heaphdr *prev)
{
    t_heaphdr   *heap;
    size_t      heap_size;
    // size_t      i;

    if (heaptype == HP_LARGE)
        heap_size = size + sizeof(t_heaphdr) + sizeof(t_blockhdr);
    else if (heaptype == HP_TINY)
        heap_size = TINY_HEAP_ENTITY_SIZE;
    else
        heap_size = SMALL_HEAP_ENTITY_SIZE;
    if ((heap = mmap(NULL, heap_size, PROT_READ | PROT_WRITE,
        MAP_PRIVATE | MAP_ANON, -1, 0)) == MAP_FAILED)
    {
        write(2, "Mmap error\n", 11);
        return (NULL);
    }
    heap->next = NULL;
    heap->prev = prev;
    heap->heaptype = heaptype;
    heap->size = heap_size;
    heap->free_space = heap_size - sizeof(t_heaphdr) - sizeof(t_blockhdr);
    heap->nb_block = 1;
    init_heap_first_block(heap);
    return (heap);
}

// int   check_next_block_on_heap(t_heaphdr *heap, t_blockhdr *block)
// {
//     if ((void *)block - (void *)heap + block->size + sizeof(t_blockhdr) <= heap->size)
//         return (1);
//     return (0);
// }

// t_blockhdr  *new_free_end_block(t_heaphdr *heap, t_blockhdr *block)
// {
//     t_blockhdr *free_block;

//     free_block = (void *)block + sizeof(t_blockhdr) + block->size;
//     free_block->next = NULL;
//     free_block->prev = block;
//     free_block->size = (void *)heap + heap->size - (void *)free_block - sizeof(t_blockhdr);
//     free_block->state = ST_FREE;
//     heap->nb_block++;

//     return (free_block);
// }

// void  *new_block_insertion(t_heaphdr *heap, t_blockhdr *blockhdr, size_t size, size_t block_index, t_blockhdr *prev)
// {
//     if (block_index >= heap->nb_block)
//     {
//         blockhdr->next = NULL;
//         blockhdr->prev = prev;
//         blockhdr->size = size;
//         blockhdr->state = ST_USE;
//         heap->free_space -= (sizeof(t_blockhdr) + size);
//         heap->nb_block++;
//         if (check_next_block_on_heap(heap, blockhdr))
//             blockhdr->next = new_free_end_block(heap, blockhdr);
//         return (blockhdr);
//     }
//     // else
//     // {
//     //     blockhdr->next = NULL;
//     //     blockhdr->prev = prev;
//     //     blockhdr->size = size;
//     //     blockhdr->state = ST_USE;
//     //     heap->free_space -= (sizeof(t_blockhdr) + size);
//     //     heap->nb_block++;
//     //     if (check_next_block_on_heap(heap, blockhdr))
//     //         blockhdr->next = new_free_end_block(heap, blockhdr);
//     //     return (blockhdr);
//     // }
//     return (blockhdr);
// }

void        add_free_block(t_blockhdr *block, size_t size,
    t_blockhdr *prev, t_blockhdr *next)
{
    block->prev = prev;
    block->next = next;
    if (next)
        next->prev = block;
    block->size = size;
    block->state = ST_FREE;
}

t_blockhdr  *update_block(t_heaphdr *heap, t_blockhdr *block, size_t size)
{
    t_blockhdr  *next;
    size_t      old_size;

    if (block->size <= size + sizeof(t_blockhdr) + 16)
    {
    // write(1, "insertion fill\n", 15);
        block->size = size;
        block->state = ST_USE;
        heap->free_space -= (block->size);
        return (block);
    }
    // if (block == blockcheck)
        // exit(0);
        write(1, "in bcheck\n", 10);
    next = block->next;
    old_size = block->size;
    heap->free_space -= (size + sizeof(t_blockhdr));
    heap->nb_block++;
    block->size = size;
    block->state = ST_USE;
    block->next = (void *)block + sizeof(t_blockhdr) + size;
    // if ((int)(old_size - size - sizeof(t_blockhdr)) < 0)
    //     exit(0);
    add_free_block(block->next, old_size - size - sizeof(t_blockhdr), block, next);
    // exit(0);
    // write(1, "insertion nblock\n", 17);
    return (block);
}

t_blockhdr  *check_for_insertion(t_heaphdr *heap, size_t size)
{
    t_blockhdr  *block;
    size_t      i;

    // while
    // if (heap->nb_block == 0)
    //     return (new_block_insertion(heap, (t_blockhdr *)(heap + 1), size, 0, NULL));
    
    block = (t_blockhdr *)(heap + 1);
    i = 0;
    while (i < heap->nb_block)
    {
        if (block->state == ST_FREE && block->size >= size)
            return (update_block(heap, block, size));
        block = block->next;
        i++;
    }
    // block = (t_blockhdr *)(heap + 1);
    return (NULL);
}

void *malloc(size_t size)
{
    t_heaphdr   *heaps;
    e_heaptype  htype;
    t_blockhdr  *block;

    // show_alloc_mem();
    // write(1, "malloc in\n", 10);
    size = (size + 15) & (~15);
    htype = get_heap_type(size);
    if (!heap_list[htype] &&!(heap_list[htype] = new_heap(size, htype, NULL)))
            return (NULL);
    heaps = heap_list[htype];
    while (heaps)
    {
        if (heaps->free_space >= size)
        {
            if ((block = check_for_insertion(heaps, size)))
            {

                // write(1, "malloc out\n", 11);
                return (block + 1);
            }
        }
        if (!heaps->next && !(heaps->next = new_heap(size, htype, heaps)))
            return (NULL);
        heaps = heaps->next;
    }
    return (NULL);
}