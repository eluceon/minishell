/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 04:36:05 by eluceon           #+#    #+#             */
/*   Updated: 2020/11/10 15:58:29 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	d_len;
	size_t	s_len;

	d_len = 0;
	s_len = 0;
	while (dst[d_len] && d_len < size)
		d_len++;
	while (src[s_len] && size > d_len + s_len + 1)
	{
		dst[d_len + s_len] = src[s_len];
		s_len++;
	}
	if (d_len < size)
		dst[d_len + s_len] = '\0';
	while (src[s_len])
		s_len++;
	return (d_len + s_len);
}
