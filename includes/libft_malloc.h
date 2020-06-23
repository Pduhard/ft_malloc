/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_malloc.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pduhard- <pduhard-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:21:12 by pduhard-          #+#    #+#             */
/*   Updated: 2020/06/23 01:21:16 by pduhard-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

# include <unistd.h>
# include <sys/mman.h>
# include <pthread.h>

# define NB_BLOCKS		100
# define TINY_HEAP_BLOCK_SIZE	128
# define SMALL_HEAP_BLOCK_SIZE	1024

# define INFO	0
# define HEX	1

typedef enum
{
	ST_USE,
	ST_FREE,
}	t_state;

typedef enum
{
	HP_TINY,
	HP_SMALL,
	HP_LARGE,
}	t_heaptype;

typedef struct	s_heaphdr
{
	struct s_heaphdr	*prev;
	struct s_heaphdr	*next;
	t_heaptype			heaptype;
	size_t				size;
}				t_heaphdr;

typedef struct	s_blockhdr
{
	struct s_blockhdr	*prev;
	struct s_blockhdr	*next;
	size_t				user_size;
	t_state				state;
}				t_blockhdr;

typedef	struct	s_alloc
{
	t_heaphdr	*tiny;
	t_heaphdr	*small;
	t_heaphdr	*large;
}				t_alloc;

extern t_alloc			g_alloc;

extern pthread_mutex_t		g_mutex;

void			*malloc(size_t size);
void			free(void *ptr);
void			*realloc(void *ptr, size_t size);
void			*calloc(size_t nmemb, size_t size);
void			*reallocarray(void *ptr, size_t nmemb, size_t size);
void			show_alloc_mem();
void			show_alloc_mem_hex();

/*
**  Intern function
*/

void			show_alloc_mem_ctrl(int ctrl);
t_heaphdr		*new_heap(size_t size, t_heaptype heaptype, t_heaphdr *prev);
void			init_block(t_blockhdr *blockaddr, t_blockhdr data);
size_t			get_true_block_size(t_blockhdr *block, t_heaphdr *heap);
int				find_alloc(void *ptr, t_heaphdr **heap_addr,
					t_blockhdr **block_addr);
void			free_block(t_heaphdr *heap, t_blockhdr *block);
void			write_addr(void *addr);
void			dump_memory(t_blockhdr *block);
void			ft_putnbr(unsigned long n);
size_t			ft_strlen(char *str);
void			ft_putstr(char *str);
void			ft_bzero(void *s, size_t n);

#endif
