#include "libft_malloc.h"

int main(void)
{
    void *mem;
    void *mem1;
    void *mem2;
    void *mem3;
    void *mem4;
    void *mem5;

    mem = malloc(128);
    mem1 = malloc(128);   
    mem2 = malloc(128);
    mem3 = malloc(128);
    mem4 = malloc(128);   
    mem5 = malloc(128);

    ft_putstr("=================================\n");
    show_alloc_mem();
    free(mem1);
    ft_putstr("=================================\n");
    show_alloc_mem();
    ft_putstr("=================================\n");
    free(mem);
    show_alloc_mem();
    ft_putstr("=================================\n");
    free(mem2);
    show_alloc_mem();
    ft_putstr("=================================\n");
    free(mem4);
    show_alloc_mem();
    ft_putstr("=================================\n");
    free(mem3);
    show_alloc_mem();
    ft_putstr("=================================\n");
    free(mem5);
    show_alloc_mem();
}