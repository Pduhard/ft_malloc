#include "includes/libft_malloc.h"
int main()
{
	char *addr;
	int i;
	
	i = 0;
	while (i < 100)
	{
		addr = (char *)malloc(100);
		for (int j = 0; j < 100; ++j)
		{
			addr[j] = 42;
		}
		i++;
	}
	show_alloc_mem_hex();

	return (0);
}
