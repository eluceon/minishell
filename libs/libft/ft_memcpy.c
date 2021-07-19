/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:08:15 by eluceon           #+#    #+#             */
/*   Updated: 2020/11/10 15:45:13 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	unsigned char	*tmp_src;
	unsigned char	*tmp_dst;

	if (!dst && !src)
		return (NULL);
	tmp_src = (unsigned char *)src;
	tmp_dst = (unsigned char *)dst;
	while (len)
	{
		len--;
		tmp_dst[len] = tmp_src[len];
	}
	return (dst);
}
