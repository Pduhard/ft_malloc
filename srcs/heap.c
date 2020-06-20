#include "libft_malloc.h"

size_t      get_heap_size(size_t size, e_heaptype heaptype)
{
    size_t      heap_size;
    size_t      page_size;

    if (heaptype == HP_TINY)
        heap_size = (TINY_HEAP_BLOCK_SIZE + sizeof(t_blockhdr)) * NB_BLOCKS;
    if (heaptype == HP_SMALL)
        heap_size = (SMALL_HEAP_BLOCK_SIZE + sizeof(t_blockhdr)) * NB_BLOCKS;
    else
        heap_size = size + sizeof(t_blockhdr);
    page_size = getpagesize();
    heap_size = (heap_size + sizeof(t_heaphdr) + page_size - 1) & (~(page_size - 1)); 
    if ((heap_size % page_size))
    {
        ft_putnbr(heap_size);
        write(1, "\n", 1);
        ft_putnbr(heap_size % page_size);
        write(1, "\n", 1);
        ft_putstr("heap size not q module of page size\n");
        exit(0);
    }
    return (heap_size);
}

void        init_heap_hdr(t_heaphdr *heap, size_t heap_size,
    e_heaptype heaptype, t_heaphdr *prev)
{
    heap->prev = prev;
    heap->next = NULL;
    heap->heaptype = heaptype;
    heap->size = heap_size;
}

t_heaphdr   *new_heap(size_t size, e_heaptype heaptype, t_heaphdr *prev)
{
    t_heaphdr   *heap;
    size_t      heap_size;

    heap_size = get_heap_size(size, heaptype);
    // ft_putstr("new_heap size: ");
    // ft_putnbr(heap_size);
    // write(1, "\n", 1);
    if ((heap = mmap(NULL, heap_size, PROT_READ | PROT_WRITE,
        MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
    {
        ft_putstr("mmap error\n");
        exit(0);
    }
    init_heap_hdr(heap, heap_size, heaptype, prev);
    init_block((t_blockhdr *)(heap + 1), (t_blockhdr){
        NULL, NULL,
        heap_size - sizeof(t_blockhdr) - sizeof(t_heaphdr),
        ST_FREE});
    // exit(0);
    return (heap);
}