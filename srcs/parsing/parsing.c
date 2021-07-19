#include "parsing.h"

char	*get_str(char **line, t_all *all)
{
	char	*str;

	str = NULL;
	while (**line)
	{
		if (ft_iswhitespace(**line))
			break ;
		else if ((ft_strchr(SPECIAL_CHARS, **line)))
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

char	*parse_line(t_line *l, t_all *all, int *escaped_char)
{
	t_str	s;

	while (ft_iswhitespace(*l->line))
		++(l->line);
	s.escaped_char = NONE;
	if ((*l->line == '\\')
		|| (*l->line == '\'' || *l->line == '"'))
		s.escaped_char |= ESCAPED_CHAR;
	if (*l->line == '\\' && ++(l->line))
		s.str = handle_backslash(&l->line, all);
	else if (*l->line == '\'' || *l->line == '"')
		s.str = quote_handler(l, all);
	else if (*l->line == '$' && ++(l->line))
		s.str = dollar_handler(&l->line, all);
	else if ((*l->line == '>' && l->line[1] == '>')
		|| (*l->line == '<' && l->line[1] == '<'))
		s.str = double_operator_handler(&l->line, all);
	else if (*l->line == '|' || *l->line == ';' || *l->line == '<'
		|| *l->line == '>' || *l->line == '&')
		s.str = (single_operator_handler(&l->line, all));
	else
		s.str = get_str(&l->line, all);
	*escaped_char = s.escaped_char;
	return (s.str);
}

void	merge_str_and_lst_append(t_line *l, t_all *all)
{
	char	*tmp;

	if (!l->merged_str)
		l->merged_str = ft_strdup(l->str);
	else
	{
		tmp = l->merged_str;
		l->merged_str = ft_strjoin(tmp, l->str);
		free(tmp);
	}
	free(l->str);
	if (!l->merged_str)
		free_all_exit(all, ERROR);
	if (!(*l->merged_str))
		free_char_and_null(&l->merged_str);
	else if (!*l->line || (ft_strchr("\'\"", *l->line) && (!(*(l->line + 1))))
		|| ft_iswhitespace(*l->line) || ft_strchr("|><;", (*l->line)))
	{
		if (!doubly_lst_append(&all->lst_token,
				doubly_lst_new(l->merged_str, l->escaped_char)))
			error_handler(NULL, ENOMEM);
		l->merged_str = NULL;
	}
}

t_dlst	*parsing(t_all *all)
{
	t_line	line;

	line.merged_str = NULL;
	line.line = ft_strdup(all->line);
	free(all->line);
	all->line = NULL;
	if (!line.line)
		free_all_exit(all, ERROR);
	add_history_to_lst(line.line, &all->shell_history, &all->ptr_history);
	while (line.line && *line.line)
	{
		line.str = parse_line(&line, all, &line.escaped_char);
		if (!line.str)
			return (NULL);
		merge_str_and_lst_append(&line, all);
	}
	return (all->lst_token);
}
