#include "libft_malloc.h"

size_t	ft_strlen(char *str)
{
	char	*str2;

	str2 = str;
	while (*str2)
		++str2;
	return ((size_t)(str2 - str));
}
