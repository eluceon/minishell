#include "utils.h"

void	doubly_lst_clear(t_dlst **lst)
{
	t_dlst	*tmp1;
	t_dlst	*tmp2;

	if (*lst)
	{
		tmp1 = *lst;
		while (tmp1)
		{
			tmp2 = tmp1->next;
			free(tmp1->str);
			free(tmp1);
			tmp1 = tmp2;
		}
		*lst = NULL;
	}
}
