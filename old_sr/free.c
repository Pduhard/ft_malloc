#include "libft_malloc.h"

void free(void *ptr)
{
    write(2, "free\n", 5);
    (void)ptr;
}