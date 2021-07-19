/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 21:11:52 by eluceon           #+#    #+#             */
/*   Updated: 2021/04/25 22:04:41 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isoverlap(char symmbol, char const *set)
{
	int	i;

	i = -1;
	while (set[++i])
	{
		if (set[i] == symmbol)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		i;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = 0;
	i = 0;
	while (s1[start] && ft_isoverlap(s1[start], set))
		start++;
	while (s1[end])
		end++;
	while (end >= start && ft_isoverlap(s1[end - 1], set))
		end--;
	str = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!str)
		return (NULL);
	while (start < end)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}
