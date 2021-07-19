/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 19:24:06 by eluceon           #+#    #+#             */
/*   Updated: 2020/11/04 19:57:30 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	i;

	ptr = (char *)malloc(count * size);
	if (ptr)
	{
		i = 0;
		while (i < count * size)
			ptr[i++] = '\0';
	}
	return ((void *)ptr);
}
