/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 13:31:10 by eluceon           #+#    #+#             */
/*   Updated: 2020/11/01 02:03:40 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*tmp_src;
	unsigned char	*tmp_dst;
	size_t			i;

	tmp_src = (unsigned char *)src;
	tmp_dst = (unsigned char *)dest;
	i = 0;
	if (tmp_dst > tmp_src)
	{
		while (n)
		{
			n--;
			tmp_dst[n] = tmp_src[n];
		}
	}
	else if (tmp_dst < tmp_src)
	{
		while (i < n)
		{
			tmp_dst[i] = tmp_src[i];
			i++;
		}
	}
	return (dest);
}
