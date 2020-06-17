#include "libft_malloc.h"

void    *calloc(size_t nmemb, size_t size)
{
    if (!nmemb || !size)
        return (NULL);
    return (malloc(size * nmemb));
}