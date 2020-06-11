#include "libft_malloc.h"

t_heaphdr *heap = NULL;
// #include "libft.h"

void        add_heap(t_heaphdr *new_heap)
{
    t_heaphdr *lst;
    t_heaphdr *next;

    if (!(lst = heap))
    {
        heap = new_heap;
        heap->next = NULL;
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
        new_heap.free_space = TINY_HEAP_ENTITY_SIZE - sizeof(t_blockhdr) - sizeof(t_heaphdr) - size;
    }
    else if (size < SMALL_HEAP_BLOCK_SIZE)
    {
        new_heap.size = SMALL_HEAP_ENTITY_SIZE;
        new_heap.heaptype = HP_SMALL;
        new_heap.free_space = SMALL_HEAP_ENTITY_SIZE - sizeof(t_blockhdr) - sizeof(t_heaphdr) - size;
    }
    else
    {
        new_heap.size = size + sizeof(t_blockhdr) + sizeof(t_heaphdr);
        new_heap.heaptype = HP_LARGE;
        new_heap.free_space = 0;


    }
    write(2, "size:", 5);
    ft_putnbr(new_heap.size);
    write(2, " neededsize:", 11);
    ft_putnbr(size);
    write(2, "\ntype:", 6);
    ft_putnbr(new_heap.heaptype);
    write(2, "\n", 1);
    // new_heap.next = NULL;
    if ((addr = mmap(NULL, new_heap.size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS , -1, 0)) == MAP_FAILED)
    {
        write(2, "malloc error\n", 13);

        return (NULL);
    }
    *((t_heaphdr *)addr) = new_heap;
    add_heap((t_heaphdr *)addr);
    return ((t_heaphdr *)addr);
}

void        create_new_block(t_blockhdr *new_block, size_t size, e_state prev_state, e_state state)
{
    write(2, "in new blck\n", sizeof("in new blck\n"));
    new_block->size = size;
    new_block->prev_state = prev_state;
    new_block->state = state;
    write(2, "out new blck\n", sizeof("out new blck\n"));

}

t_blockhdr  *create_free_space(size_t size)
{
    t_heaphdr   *new_heap;
    // t_blockhdr  *new_block;
    // size_t      heapsize;

    write(2, "create free space\n", sizeof("create free space\n"));

    if (!(new_heap = new_heaphdr(size)))
        return (NULL);
    // heapsize = new_heaphd->heapsize;
    // new_block = (t_blockhdr *)(new_heap + 1);
    // new_block->size = size;
    // new_block->prev_state = ST_FREE;
    // new_block->state = ST_USE;
    create_new_block((t_blockhdr *)(new_heap + 1),
            size, ST_FREE, ST_USE);
    write(2, "new used blockhdr\n", sizeof("new used blockhdr\n"));

    if (new_heap->heaptype != HP_LARGE)
    {
        create_new_block((t_blockhdr *)((void *)(new_heap + 1) + sizeof(t_blockhdr) + size),
            new_heap->size - size - sizeof(t_blockhdr) - sizeof(t_heaphdr),
            ST_USE,
            ST_FREE);
        write(2, "new free blockhdr\n", sizeof("new free blockhdr\n"));

        // new_block = (void *)new_block + sizeof(t_blockhdr) + size;
        // new_block->size = heapsize - size - sizeof(t_blockhdr) - sizeof(t_heaphdr);
        // new_block->prev_state = ST_USE;
        // new_block->state = ST_FREE;
    }
    else
        write(2, "no blockhdr after large\n", sizeof("no blockhdr after large\n"));
    return ((t_blockhdr *)(new_heap + 1));
}

t_blockhdr  *check_heap_space(size_t size, t_heaphdr *curr)
{
    t_blockhdr  *block;
    e_state     prev_state;

    write(2, "check_heap_space in\n", sizeof("check_heap_space in\n"));

    if (curr->heaptype == HP_LARGE)
        return (NULL);
    if (curr->heaptype == HP_TINY && size > TINY_HEAP_BLOCK_SIZE)
        return (NULL);
    if (curr->heaptype == HP_SMALL && (size > SMALL_HEAP_BLOCK_SIZE || size < TINY_HEAP_BLOCK_SIZE))
        return (NULL);
    block = (t_blockhdr *)(curr + 1);

    // write(2, "check_heap_space in\n", sizeof("check_heap_space in\n"));
    write(2, "block space:", 12);
    ft_putnbr(curr->size);
    write(2, "\n", 1);
    prev_state = ST_FREE;
    while (block)
    {
        // write(2, "loop check heap\n", sizeof("loop check heap\n"));
        if (block->state == ST_FREE && size <= block->size)
        {
            write(2, "check_heap_space out finded\n", sizeof("check_heap_space out finded\n"));
            create_new_block(block, size, prev_state, ST_USE);
            // size_t size_left;
            curr->free_space -= (size + sizeof(t_blockhdr));
            // size_left = ((void *)curr + curr->size) - ((void *)block + sizeof(t_blockhdr) + size);
            if (curr->free_space > sizeof(t_blockhdr))
                create_new_block((void *)block + size + sizeof(t_blockhdr),
                    curr->free_space, ST_USE, ST_FREE);
            return (block);
        }    // write(2, "la\n", 3);
        if ((void *)block + block->size + sizeof(t_blockhdr) - (void *)curr > (long)curr->size)
        {
    write(2, "check_heap_space out\n", sizeof("check_heap_space out\n"));
            return (NULL);

//            write(2, "nn\n", 3);
        }
        prev_state = block->prev_state;
        block = (void *)block + block->size + sizeof(t_blockhdr);
    }
    write(2, "check_heap_space out\n", sizeof("check_heap_space out\n"));
            //write(2, "nn\n", 3);
        
    return (block);
}

t_blockhdr    *find_free_space(size_t size)
{
    t_blockhdr   *block;
    t_heaphdr    *curr;

    write(2, "find free space\n", sizeof("find free space\n"));

    if (!(curr = heap))
    {
        // write(1, "chelou\n", 7);
        return (create_free_space(size));
    }
    while (curr)
    {
       write(2, "compare free space: " , sizeof("compare free space: "));
        ft_putnbr(curr->free_space);
       write(2, "\n", 1);
        if (curr->free_space >= size && (block = check_heap_space(size, curr)))
            return (block);
        curr = curr->next;
    }
    // write(2, "end of find free space\n", sizeof("find free space \n"));
    return (create_free_space(size));
}

void *malloc(size_t size)
{
    t_blockhdr  *block;
    // t_heaphdr   *new_heap;

    size = (size + 15) & (~15);
    write(1, "malloc in\n", 10);
    if (!(block = find_free_space(size)))
    {
        write(2, "malloc error\n", 13);
        return ((void *)-1);
    }
    //write(2, "return\n", 7);
    show_alloc_mem();
    write_addr((unsigned long)(block + 1));
    write(1, "\n", 1);
    return ((void *)(block + 1));
    (void )size;
}