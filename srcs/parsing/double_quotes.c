#include "parsing.h"

char	*get_str_dquotes(char **line, t_all *all)
{
	char	*str;

	str = NULL;
	while (**line)
	{
		if (ft_iswhitespace(**line))
			break ;
		else if ((**line == '\\' && ft_strchr(DQUOTES_EXCEPTION, (*line)[1])))
			break ;
		else if (ft_strchr("$`\"", **line))
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

char	*double_quotes_manager(t_line *l, t_all *all)
{
	char	*str;

	if (*l->line == '\"')
	{
		str = ft_strdup("");
		if (!str)
			free_all_exit(all, ENOMEM);
		return (str);
	}
	if (*l->line == '\\' && ft_strchr("\\$`\"", l->line[1]) && ++(l->line))
		str = handle_backslash(&l->line, all);
	else if (*l->line == '$' && ++(l->line))
		str = dollar_handler(&l->line, all);
	else if (*l->line == '|' || *l->line == ';' || *l->line == '<'
		|| *l->line == '>' || *l->line == '&' || ft_iswhitespace(*l->line))
	{
		str = str_join_char(NULL, *l->line);
		l->line++;
	}
	else
		str = get_str_dquotes(&l->line, all);
	return (str);
}

char	*join_str_dquotes(char	*merged_str, char *str, t_all *all)
{
	char	*tmp;

	if (!merged_str)
		merged_str = ft_strdup(str);
	else
	{
		tmp = merged_str;
		merged_str = ft_strjoin(tmp, str);
		free(tmp);
	}
	if (!merged_str)
	{
		free(str);
		free_all_exit(all, 1);
	}
	free(str);
	if (!(*merged_str))
	{
		free(merged_str);
		merged_str = NULL;
	}
	return (merged_str);
}

char	*double_quotes_handler(t_line *l, t_all *all)
{
	char	*str;
	char	*merged_str;

	merged_str = NULL;
	str = NULL;
	while (*l->line != '\"')
	{
		str = double_quotes_manager(l, all);
		if (!str)
			return (NULL);
		merged_str = join_str_dquotes(merged_str, str, all);
	}
	if (!str)
	{
		merged_str = ft_strdup("");
		if (!merged_str)
			free_all_exit(all, ENOMEM);
	}
	return (merged_str);
}
