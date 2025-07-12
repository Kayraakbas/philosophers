#include "philo.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t			i;
	unsigned char	*res;

	i = 0;
	res = malloc(count * size);
	if (!res)
		return (NULL);
	while (i < count * size)
	{
		res[i] = 0;
		i++;
	}
	return (res);
}
