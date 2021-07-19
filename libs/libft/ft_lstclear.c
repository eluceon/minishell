/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 18:14:52 by eluceon           #+#    #+#             */
/*   Updated: 2020/11/09 20:04:39 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp1;
	t_list	*tmp2;

	if (*lst && del)
	{
		tmp1 = *lst;
		while (tmp1)
		{
			tmp2 = tmp1->next;
			del(tmp1->content);
			free(tmp1);
			tmp1 = tmp2;
		}
		*lst = NULL;
	}
}
