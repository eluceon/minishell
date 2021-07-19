/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 20:07:34 by eluceon           #+#    #+#             */
/*   Updated: 2020/11/09 20:15:29 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*tmp_lst;

	if (lst && f)
	{
		tmp_lst = lst;
		while (tmp_lst)
		{
			f(tmp_lst->content);
			tmp_lst = tmp_lst->next;
		}
	}
}
