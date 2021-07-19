#include "parsing.h"

int	find_closing_quotes(const char *line, char quote)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\\' && (line[i + 1] == '\\'))
			i += 2;
		if (line[i] == '\\' && (line[i + 1] == '"'))
			i++;
		else if (line[i] == quote)
			return (1);
		i++;
	}
	return (0);
}

char	*get_str_single_quotes(char **line, t_all *all)
{
	char	*str;

	str = NULL;
	while (**line)
	{
		if (ft_strchr("\'", **line))
			break ;
		str = str_join_char(str, **line);
		if (!str)
			free_all_exit(all, ENOMEM);
		(*line)++;
	}
	if (!str)
	{
		str = ft_strdup("");
		if (!str)
			free_all_exit(all, ENOMEM);
	}
	return (str);
}

char	*quote_handler(t_line *l, t_all *all)
{
	char	*str;

	str = NULL;
	if (!find_closing_quotes(l->line + 1, *l->line))
	{
		doubly_lst_clear(&all->lst_token);
		error_handler("No closing quotes", 1);
		return (NULL);
	}
	if (*l->line == '\'' && ++(l->line))
		str = get_str_single_quotes(&l->line, all);
	else if (*l->line == '\"' && ++(l->line))
		str = double_quotes_handler(l, all);
	(l->line)++;
	return (str);
}
