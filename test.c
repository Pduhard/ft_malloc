#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "./includes/libft_malloc.h"
#include <stdlib.h>

// void show_mem();
int main(void)
{
	// struct rlimit rlimit;
	// void *data;

	// if (getrlimit(RLIMIT_CPU, &rlimit) == -1)
	// 	printf("error errno\n");
	// else
	// {
	//	printf("%ld\n", getpagesize() * 4);
	// }
	// data = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON , -1, 0);
	// ((char *)data)[getpagesize() - 1] = 5;
	// printf("%s\n", strerror(errno));
	// void *data2 = mmap(NULL, getpagesize() * getpagesize(), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	// printf("%s\n", strerror(errno));
	// 	void *data3 = mmap(NULL, getpagesize() * getpagesize() * 0x100, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	// printf("%s %d\n", strerror(errno), 0xA0000);
	// printf("%lx\n%lx\n%lx\n", data, data2, data3);
	int rd;

	printf("sizeof heaphdr %zu sizeof blockhdr %zu\n", sizeof(t_heaphdr), sizeof(t_blockhdr));
	rd = 0xfff12340;
	for (int i = 0; i < 20000; ++i)
	{
		//printf("")
		// ft_putnbr(rd >> 16);
		if (!rd)
			rd = 0x12356;
		char *e = malloc((rd >> 16) % 4096);
		for (int j = 0; j < (rd >> 16) % 4096; j++)
			*(e + j - 1) = 'f';
		rd ^= rd >> 2;
		rd ^= rd << 4;
		rd ^= rd >> 6;
		// show_alloc_mem();
	}
	// e[0] = 'a';
	// e[1] = 'a';
	// e[2] = '\n';
	// e[3] = '\0';
	//memcpy(e, "salut\0", 6);
	// write(1, e, 3);
	// printf("%zu %s\n", sizeof(t_heaphdr), e);
	// printf()
/*	char *t = malloc(4);
	char *b;

	b = t + 1;
	free(0x0);
	free (b);
*/	return (0);
}
