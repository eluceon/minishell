/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 21:10:40 by eluceon           #+#    #+#             */
/*   Updated: 2021/04/25 22:12:56 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		len;
	char	*new_str;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	len = 0;
	while (s1[len])
		len++;
	while (s2[i])
		i++;
	len += i;
	new_str = (char *)malloc(sizeof(new_str) * (len + 1));
	if (!new_str)
		return (NULL);
	len = -1;
	while (s1[++len])
		new_str[len] = s1[len];
	i = -1;
	while (s2[++i])
		new_str[len++] = s2[i];
	new_str[len] = '\0';
	return (new_str);
}
