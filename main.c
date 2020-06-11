#include "libft_malloc/includes/libft_malloc.h"
#include <stdio.h>

int main(void)
{
    void *tst = ft_malloc(12);
    // ((char *)tst)[4096] = 2;
    printf("malloc %p \n", tst);
    return (0);
}