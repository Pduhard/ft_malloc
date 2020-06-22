#include "libft_malloc.h"

void	ft_putnbr(unsigned long n)
{
	char	nb;

	if (n > 9)
		ft_putnbr(n / 10);
	nb = (n % 10) + '0';
	if (write(2, &nb, 1) == -1)
		return ;
}
