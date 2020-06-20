#include "libft_malloc.h"

void    *calloc(size_t nmemb, size_t size)
{
    void *alloc;

    pthread_mutex_lock(&g_mutex);
    if (!nmemb || !size)
    {
        pthread_mutex_unlock(&g_mutex);
        return (NULL);
    }
    alloc = malloc(size * nmemb);
    if (alloc && (size || nmemb))
        bzero(alloc, size * nmemb);
    pthread_mutex_unlock(&g_mutex);
    return( alloc);
}