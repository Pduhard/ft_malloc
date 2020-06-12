#include "libft_malloc.h"

void	ft_putnbr(unsigned long n)
{
	char	nb;

	if (n > 9)
		ft_putnbr(n / 10);
	else
		write(1, "\n", 1);
	nb = (n % 10) + '0';
	if (write(2, &nb, 1) == -1)
		return ;
}
