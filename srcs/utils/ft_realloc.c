#include "utils.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (ptr && size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = (char *)malloc(size * sizeof(char));
	if (!new_ptr)
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (new_ptr);
	new_ptr = ft_memmove(new_ptr, ptr, size);
	free(ptr);
	ptr = NULL;
	return (new_ptr);
}
