#include <pthread.h>
# include "libft_malloc.h"

#define NB_THREADS  4

void *alloc_and_free(void *param)
{
    char **argv;

    argv = (char **)param;
    for (int i = 0; i < 1024; i++)
    {
        char *mem = malloc(1024);
        free(mem);
    }
    show_alloc_mem();
    show_alloc_mem_hex();
    pthread_exit(NULL);
    (void )argv;
}

int main(int argc, char **argv)
{
    pthread_t threads[NB_THREADS];
    int         i;

    i = 0;
    while (i < NB_THREADS)
        if (pthread_create(&(threads[i++]), NULL, alloc_and_free,
            (void *)argv))
                return (0);
    i = 0;
    while (i < NB_THREADS)
        pthread_join(threads[i++], NULL);
}