#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/mman.h>
# define TINY_HEAP_BLOCK_SIZE   128
# define TINY_HEAP_ENTITY_SIZE  16384
# define SMALL_HEAP_BLOCK_SIZE  4096
# define SMALL_HEAP_ENTITY_SIZE 524288

typedef enum {ST_USE, ST_FREE} e_state;
typedef enum {HP_TINY, HP_SMALL, HP_LARGE} e_heaptype;

typedef struct s_heaphdr
{
    struct s_heaphdr    *next;
    e_heaptype              heaptype;
    size_t              size;
    size_t              free_space;
    int                 a;
}               t_heaphdr;

typedef struct s_blockhdr
{
    size_t              size;
    e_state             prev_state;
    e_state             state;
}               t_blockhdr;

void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);

#endif