#include "includes/libft_malloc.h"
int main()
{
	char *addr;
	char *addr1;
	int i;
	
	i = 0;
	while (i < 1024)
	{
		addr = (char *)malloc(1024);
		addr1 = (char *)malloc(1024);
		for (int j = 0; j < 1024; ++j)
		{
			addr[j] = 42;
			addr1[j] = 42;
		}
		free(addr);
		i++;
	}

	return (0);
}
