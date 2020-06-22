#include "libft_malloc.h"

void	*calloc(size_t nmemb, size_t size)
{
	void *alloc;

	if (!nmemb || !size)
		return (NULL);
	alloc = malloc(size * nmemb);
	if (alloc && (size || nmemb))
		bzero(alloc, size * nmemb);
	return (alloc);
}
