#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/mman.h>
# include <pthread.h>
# include <strings.h>

# define NB_BLOCKS  100
# define TINY_HEAP_BLOCK_SIZE   1024
# define INFO   0
# define HEX    1

//# define TINY_HEAP_ENTITY_SIZE  16384

# define SMALL_HEAP_BLOCK_SIZE  8092

//# define SMALL_HEAP_ENTITY_SIZE 524288

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
    struct s_heaphdr    *prev;
    struct s_heaphdr    *next;
    e_heaptype          heaptype;
    size_t              size;
}               t_heaphdr;

typedef struct s_blockhdr
{
    struct s_blockhdr   *prev;
    struct s_blockhdr   *next;
    size_t              user_size;
    e_state             state;
}               t_blockhdr;

typedef struct  s_alloc
{
    t_heaphdr   *tiny;
    t_heaphdr   *small;
    t_heaphdr   *large;
}               t_alloc;

extern t_alloc   g_alloc;

extern t_heaphdr *heap_list[2]; // SMALL/TINY and LARGE
// extern void *blockcheck;
extern pthread_mutex_t	g_mutex;

void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);
void *calloc(size_t nmemb, size_t size);
void *reallocarray(void *ptr, size_t nmemb, size_t size);


void show_alloc_mem();
void show_alloc_mem_hex();
void show_alloc_mem_ctrl(int ctrl);
void ft_putnbr(unsigned long n);
// e_heaptype  get_heap_type(size_t size);

t_heaphdr   *new_heap(size_t size, e_heaptype heaptype, t_heaphdr *prev);
void init_block(t_blockhdr *blockaddr, t_blockhdr data);
size_t get_true_block_size(t_blockhdr *block, t_heaphdr *heap);
int     find_alloc(void *ptr, t_heaphdr **heap_addr, t_blockhdr **block_addr);
void free_block(t_heaphdr *heap, t_blockhdr *block);


size_t ft_strlen(char *str);
void ft_putstr(char *str);


// void    write_addr(unsigned long addr);
void    write_block_info(t_blockhdr *block);

#endif