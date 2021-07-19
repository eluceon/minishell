#include "environment.h"

int	change_environment(t_dlst **env, char *name, char *value)
{
	char	*new_str;
	t_dlst	*tmp;

	tmp = *env;
	new_str = ft_strjoin(name, value);
	if (!new_str)
		error_handler(NULL, ENOMEM);
	while (tmp)
	{
		if (!ft_strncmp(name, tmp->str, ft_strlen(name)))
		{
			free(tmp->str);
			tmp->str = new_str;
			return (SUCCESS);
		}
		tmp = tmp->next;
	}
	if (!tmp)
		doubly_lst_append(env, doubly_lst_new(new_str, NONE));
	return (SUCCESS);
}

int	change_pwd(char *oldpwd, t_dlst **env)
{
	char	*cwd;
	int		status;

	status = SUCCESS;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		cmd_error_message("pwd", NULL, strerror(errno));
		status = ERROR;
	}
	else
	{
		status = change_environment(env, "PWD=", cwd);
		free(cwd);
	}
	status += change_environment(env, "OLDPWD=", oldpwd);
	return (status);
}
