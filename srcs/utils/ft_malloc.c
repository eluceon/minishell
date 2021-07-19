#include "utils.h"

void	*ft_malloc(size_t size)
{
	size_t	i;
	char	*ret;

	ret = malloc(size);
	if (!ret)
	{
		ft_crash("malloc error");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < size)
	{
		ret[i] = '\0';
		i++;
	}
	return ((void *)ret);
}
