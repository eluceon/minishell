#include "utils.h"

void	merge_last_element(t_dlst *left, t_dlst *right, t_dlst **merged)
{
	if (left == NULL)
	{
		*merged = right;
		return ;
	}
	if (right == NULL)
	{
		*merged = left;
		return ;
	}
}

void	merge_first_elemenet(t_dlst **left, t_dlst **right, t_dlst **merged)
{
	if (ft_strcmp((*left)->str, (*right)->str) < 0)
	{
		*merged = *left;
		*left = (*left)->next;
	}
	else
	{
		*merged = *right;
		*right = (*right)->next;
	}
	(*merged)->prev = NULL;
}

void	merge_remainder(t_dlst **left, t_dlst **right, t_dlst **merged)
{
	while (*left)
	{
		(*merged)->next = *left;
		(*merged)->next->prev = (*merged);
		*merged = (*merged)->next;
		*left = (*left)->next;
	}
	while (*right)
	{
		(*merged)->next = *right;
		(*merged)->next->prev = (*merged);
		*merged = (*merged)->next;
		*right = (*right)->next;
	}
}

void	doubly_lst_merge(t_dlst *left, t_dlst *right, t_dlst **merged)
{
	t_dlst	*tmp;	

	*merged = NULL;
	if (left == NULL || right == NULL)
		return (merge_last_element(left, right, merged));
	merge_first_elemenet(&left, &right, merged);
	tmp = *merged;
	while (left && right)
	{
		if (ft_strcmp(left->str, right->str) < 0)
		{
			(*merged)->next = left;
			left = left->next;
		}
		else
		{
			(*merged)->next = right;
			right = right->next;
		}
		(*merged)->next->prev = (*merged);
		*merged = (*merged)->next;
	}
	merge_remainder(&left, &right, merged);
	*merged = tmp;
}

void	doubly_lst_merge_sort(t_dlst **head)
{
	t_dlst	*left;
	t_dlst	*right;

	left = NULL;
	right = NULL;
	if ((*head == NULL) || ((*head)->next == NULL))
		return ;
	doubly_lst_split(*head, &left, &right);
	doubly_lst_merge_sort(&left);
	doubly_lst_merge_sort(&right);
	doubly_lst_merge(left, right, head);
}
