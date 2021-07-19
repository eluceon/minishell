#include "builtins.h"

int	print_sorted_env(t_dlst *env, int fd_out)
{
	t_dlst	*sorted_env;
	t_dlst	*tmp;

	sorted_env = doubly_lst_dup(env);
	if (!sorted_env)
		error_handler(NULL, ENOMEM);
	doubly_lst_merge_sort(&sorted_env);
	tmp = sorted_env;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", fd_out);
		ft_putendl_fd(tmp->str, fd_out);
		tmp = tmp->next;
	}
	doubly_lst_clear(&sorted_env);
	return (SUCCESS);
}

void	add_environment(t_dlst **env, char *str)
{
	char	*new_str;
	t_dlst	*tmp;
	int		len;

	len = 0;
	while (str[len] != '=')
		len++;
	new_str = ft_strdup(str);
	if (!new_str)
		error_handler(NULL, ENOMEM);
	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(new_str, tmp->str, len + 1))
		{
			free(tmp->str);
			tmp->str = new_str;
			return ;
		}
		tmp = tmp->next;
	}
	*env = doubly_lst_append(env, doubly_lst_new(new_str, NONE));
	if (!*env)
		error_handler(NULL, ENOMEM);
}

int	export_cmd(t_dlst **ptr_token, t_dlst *env, int fd_out)
{
	int	status;

	if (!env)
	{
		go_to_end_or_separator(ptr_token);
		return (errno = ERROR);
	}
	*ptr_token = (*ptr_token)->next;
	status = SUCCESS;
	if (!(*ptr_token) || is_separator(*ptr_token))
		return (print_sorted_env(env, fd_out));
	while (*ptr_token && !is_separator(*ptr_token))
	{
		if (!is_valid_variable_name((*ptr_token)->str, '='))
		{
			cmd_error_message("export", (*ptr_token)->str,
				"not a valid identifier");
			status = ERROR;
		}
		else if (ft_strchr((*ptr_token)->str, '='))
			add_environment(&env, (*ptr_token)->str);
		*ptr_token = (*ptr_token)->next;
	}
	return (status);
}
