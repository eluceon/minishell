#include "utils.h"

void	doubly_lst_delete_element(t_dlst **lst)
{
	if (*lst)
	{
		if ((*lst)->prev)
			(*lst)->prev->next = (*lst)->next;
		if ((*lst)->next)
			(*lst)->next->prev = (*lst)->prev;
		free((*lst)->str);
		(*lst)->str = NULL;
		free(*lst);
		(*lst) = NULL;
	}
}
