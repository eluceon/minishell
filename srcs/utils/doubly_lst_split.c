#include "utils.h"

void	doubly_lst_split(t_dlst *head, t_dlst **left, t_dlst **right)
{
	t_dlst	*fast;
	t_dlst	*slow;

	if (head == NULL || head->next == NULL)
	{
		*left = head;
		*right = NULL;
		return ;
	}
	slow = head;
	fast = head->next;
	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			fast = fast->next;
			slow = slow->next;
		}
	}
	*left = head;
	*right = slow->next;
	slow->next = NULL;
}
