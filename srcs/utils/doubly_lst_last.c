#include "utils.h"

t_dlst	*doubly_lstlast(t_dlst *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
