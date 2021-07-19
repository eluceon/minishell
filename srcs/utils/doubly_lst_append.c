#include "utils.h"

t_dlst	*doubly_lst_append(t_dlst **lst, t_dlst *new)
{
	t_dlst	*tmp;

	if (!new)
		return (NULL);
	tmp = *lst;
	if (!*lst)
		(*lst) = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	return (*lst);
}
