#include "exec_commands.h"

char	*variable_value(char *line, t_all *all, int start, int i)
{
	char	*sub_str;
	char	*value;

	sub_str = ft_substr(line, start, i - start);
	if (!sub_str)
		error_handler(NULL, ENOMEM);
	value = getenv_from_lst(all->env, sub_str);
	free(sub_str);
	if (!value)
	{
		value = ft_strdup("");
		if (!value)
			error_handler(NULL, ENOMEM);
	}
	return (value);
}

char	*get_variable_value(char *line, t_all *all, int *i)
{
	char	*value;
	int		start;

	start = ++(*i);
	if (line[*i] == '?')
	{
		value = ft_itoa(all->exit_status);
		if (!value)
			error_handler(NULL, ENOMEM);
		(*i)++;
		return (value);
	}
	while (line[*i] && (line[*i] == '_' || ft_isalpha(line[*i]))
		&& !ft_iswhitespace(line[*i]))
		(*i)++;
	if (*i - start == 0)
	{
		value = ft_strdup("$");
		if (!value)
			error_handler(NULL, ENOMEM);
	}
	else
		value = variable_value(line, all, start, *i);
	return (value);
}

void	join_not_variable(char **new_line, char *line, int *i)
{
	int		start;
	char	*sub_str;
	char	*tmp;

	start = *i;
	while (line[*i] != '$' && line[*i])
		(*i)++;
	if (*i - start > 0)
	{
		sub_str = ft_substr(line, start, *i - start);
		tmp = *new_line;
		*new_line = ft_strjoin(tmp, sub_str);
		free(tmp);
		if (sub_str)
			free(sub_str);
		if (!*new_line)
			error_handler(NULL, ENOMEM);
	}
}

void	join_variable_value(char **new_line, char *line,	int *i, t_all *all)
{
	char	*sub_str;
	char	*tmp;

	if (line[*i] == '$')
	{
		tmp = *new_line;
		sub_str = get_variable_value(line, all, i);
		if (!sub_str)
			error_handler(NULL, ENOMEM);
		*new_line = ft_strjoin(tmp, sub_str);
		free(tmp);
		free(sub_str);
		if (!*new_line)
			error_handler(NULL, ENOMEM);
	}
}

char	*handle_dollar_heredoc(char *line, t_all *all)
{
	char	*new_line;
	int		i;

	if (!ft_strchr(line, '$')
		|| is_last_token_escaped(all->lst_token) & ESCAPED_CHAR)
		return (line);
	i = 0;
	new_line = ft_strdup("");
	if (!new_line)
		error_handler(NULL, ENOMEM);
	while (line[i])
	{
		join_not_variable(&new_line, line, &i);
		join_variable_value(&new_line, line, &i, all);
	}
	free(line);
	return (new_line);
}
