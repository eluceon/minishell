/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:40:09 by eluceon           #+#    #+#             */
/*   Updated: 2020/11/04 12:27:35 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t len)
{
	unsigned char	*tmp_src;
	unsigned char	*tmp_dst;
	size_t			i;

	tmp_src = (unsigned char *)src;
	tmp_dst = (unsigned char *)dst;
	i = 0;
	while (i < len)
	{
		tmp_dst[i] = tmp_src[i];
		if (tmp_src[i] == (unsigned char)c)
			return (tmp_dst + i + 1);
		i++;
	}
	return ((void *)0);
}
