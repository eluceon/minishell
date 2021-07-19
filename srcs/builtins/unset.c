#include "builtins.h"

void	remove_variable(char *name, t_dlst *env)
{
	int		len;

	while (env)
	{
		len = ft_strlen(name);
		if (!ft_strncmp(name, env->str, len) && env->str[len] == '=')
		{
			doubly_lst_delete_element(&env);
			return ;
		}
		env = env->next;
	}
}

int	unset_cmd(t_dlst **ptr_token, t_dlst *env)
{
	int	status;

	*ptr_token = (*ptr_token)->next;
	if (!env)
	{
		go_to_end_or_separator(ptr_token);
		return (errno = ERROR);
	}
	status = 0;
	while (*ptr_token && !is_separator(*ptr_token))
	{
		if (is_valid_variable_name((*ptr_token)->str, '\0'))
			remove_variable((*ptr_token)->str, env);
		else
		{
			status = ERROR;
			errno = ERROR;
			cmd_error_message("unset", (*ptr_token)->str,
				"not a valid identifier");
		}
		*ptr_token = (*ptr_token)->next;
	}
	return (status);
}
