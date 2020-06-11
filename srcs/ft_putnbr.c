#include "libft_malloc.h"

void	ft_putnbr(long n)
{
	char	nb;
	int		neg;

	neg = 0;
	if (n < 0)
	{
		neg = 1;
		if (write(2, "-", 1) == -1)
			return ;
		ft_putnbr(-n);
	}
	if (n > 9)
		ft_putnbr(n / 10);
	nb = (n % 10) + '0';
	if (neg != 1 && write(2, &nb, 1) == -1)
		return ;
}
