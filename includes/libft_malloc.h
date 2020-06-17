#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/mman.h>
# define TINY_HEAP_BLOCK_SIZE   128
# define TINY_HEAP_ENTITY_SIZE  16384
# define SMALL_HEAP_BLOCK_SIZE  4096
# define SMALL_HEAP_ENTITY_SIZE 524288

# define MSG_TINY_HDR   "\n\tTINY : "
# define MSG_TINY_HDR_SIZE  9
# define MSG_SMALL_HDR   "\n\tSMALL : "
# define MSG_SMALL_HDR_SIZE  10
# define MSG_LARGE_HDR   "\n\tLARGE : "
# define MSG_LARGE_HDR_SIZE  10

typedef enum {ST_USE, ST_FREE} e_state;
typedef enum {HP_TINY, HP_SMALL, HP_LARGE} e_heaptype;

typedef struct s_heaphdr
{
    struct s_heaphdr    *next;
    struct s_heaphdr    *prev;
    e_heaptype          heaptype;
    size_t              size;
    size_t              free_space; // -sizeof(blockhdr)
    size_t              nb_block;
    // int                 a;
}               t_heaphdr;

typedef struct s_blockhdr
{
    struct s_blockhdr    *next;
    struct s_blockhdr    *prev;
    size_t              size;
    e_state             state;
}               t_blockhdr;

extern t_heaphdr *heap_list[3];
extern void *blockcheck;

void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);
void *calloc(size_t nmemb, size_t size);
void *reallocarray(void *ptr, size_t nmemb, size_t size);
void show_alloc_mem();
void ft_putnbr(unsigned long n);

void    write_addr(unsigned long addr);

#endif