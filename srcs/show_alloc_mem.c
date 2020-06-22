#include "libft_malloc.h"

void	show_alloc_mem(void)
{
	pthread_mutex_lock(&g_mutex);
	show_alloc_mem_ctrl(INFO);
	pthread_mutex_unlock(&g_mutex);
}
