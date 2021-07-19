#include "parsing.h"

char	*handle_backslash(char **line, t_all *all)
{
	char	*str;

	str = NULL;
	while (**line)
	{
		if (ft_iswhitespace(**line))
			break ;
		str = str_join_char(str, **line);
		if (!str)
			free_all_exit(all, ENOMEM);
		if (ft_strchr(SPECIAL_CHARS, (*line)[1]))
		{
			(*line)++;
			return (str);
		}
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

char	*get_variable_name(char **line, t_all *all)
{
	char	*str;

	str = NULL;
	while (**line)
	{
		if (ft_iswhitespace(**line))
			break ;
		else if (**line != '_' && !ft_isalnum(**line))
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

char	*get_status(char **str, t_all *all)
{
	char	*value;

	value = ft_itoa(all->exit_status);
	if (!value)
		free_all_exit(all, ENOMEM);
	(*str)++;
	return (value);
}

char	*dollar_handler(char **str, t_all *all)
{
	char	*name;
	char	*value;

	if (**str == '?' && last_token(all->lst_token) != HEREDOC)
		return (get_status(str, all));
	name = get_variable_name(str, all);
	if (last_token(all->lst_token) == HEREDOC || name[0] == '\0')
	{
		value = ft_strjoin("$", name);
		if (!value)
			error_handler(NULL, ENOMEM);
		free(name);
		return (value);
	}
	value = getenv_from_lst(all->env, name);
	free(name);
	if (!value)
	{
		value = ft_strdup("");
		if (!value)
			free_all_exit(all, ENOMEM);
	}
	return (value);
}
