#include "utils.h"

char	*str_join_char(char *str, char ch)
{
	int		len;
	char	*new_str;

	if (!str)
	{
		str = (char *)malloc(1);
		if (!str)
			return (NULL);
		str[0] = '\0';
	}
	len = ft_strlen(str);
	new_str = (char *)malloc(len + 2);
	if (!new_str)
	{
		free(str);
		return (NULL);
	}
	len = -1;
	while (str[++len])
		new_str[len] = str[len];
	new_str[len] = ch;
	new_str[++len] = '\0';
	free(str);
	return (new_str);
}
