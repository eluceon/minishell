#include "utils.h"

int	doubly_lst_size(t_dlst *lst)
{
	int		size;
	t_dlst	*tmp;

	size = 0;
	tmp = lst;
	while (tmp)
	{
		tmp = tmp->next;
		size++;
	}
	return (size);
}
