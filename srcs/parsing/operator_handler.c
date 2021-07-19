#include "parsing.h"

char	*single_operator_handler(char **line, t_all *all)
{
	char	*str;

	str = str_join_char(NULL, **line);
	if (!str || !doubly_lst_append(&all->lst_token, doubly_lst_new(str, NONE)))
		free_all_exit(all, 1);
	str = str_join_char(NULL, '\0');
	if (!str)
		free_all_exit(all, 1);
	(*line)++;
	return (str);
}

char	*double_operator_handler(char **line, t_all *all)
{
	char	*str;

	str = ft_substr(*line, 0, 2);
	if (!str || !doubly_lst_append(&all->lst_token, doubly_lst_new(str, NONE)))
		free_all_exit(all, 1);
	str = str_join_char(NULL, '\0');
	if (!str)
		free_all_exit(all, 1);
	(*line)++;
	(*line)++;
	return (str);
}
