/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 21:11:17 by eluceon           #+#    #+#             */
/*   Updated: 2021/04/26 16:50:03 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substring;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
		i++;
	if (i < start)
	{
		substring = (char *)malloc(sizeof(char));
		if (!substring)
			return (NULL);
		substring[0] = '\0';
		return (substring);
	}
	substring = (char *)malloc(sizeof(char) * (len + 1));
	if (!substring)
		return (NULL);
	i = -1;
	while (++i < len)
		substring[i] = s[start + i];
	substring[i] = '\0';
	return (substring);
}
