#include "utils.h"

t_dlst	*doubly_lst_dup(t_dlst *head)
{
	t_dlst	*new_head;
	char	*str_dup;

	if (!head)
		return (NULL);
	new_head = NULL;
	while (head)
	{
		str_dup = ft_strdup(head->str);
		if (!str_dup)
			return (NULL);
		new_head = doubly_lst_append(&new_head, doubly_lst_new(str_dup, NONE));
		if (!new_head)
			return (NULL);
		head = head->next;
	}
	return (new_head);
}
