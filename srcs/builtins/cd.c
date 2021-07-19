#include "builtins.h"

int	go_home(t_dlst *env)
{
	char	*home;
	int		ret;

	home = getenv_from_lst(env, "HOME");
	if (!home)
	{
		cmd_error_message("cd", NULL, "HOME not set");
		return (ERROR);
	}
	ret = chdir(home);
	free(home);
	if (ret)
	{
		cmd_error_message("cd", NULL, strerror(errno));
		return (ERROR);
	}
	return (SUCCESS);
}

int	go_path(t_dlst **ptr_token)
{
	int	ret;

	ret = chdir((*ptr_token)->str);
	go_to_end_or_separator(ptr_token);
	if (ret)
	{
		cmd_error_message("cd", NULL, strerror(errno));
		return (ERROR);
	}
	return (SUCCESS);
}

int	cd_error_msg(char *msg, t_dlst **ptr_token, int status)
{
	cmd_error_message("cd", NULL, msg);
	go_to_end_or_separator(ptr_token);
	return (status);
}

int	cd_cmd(t_dlst **ptr_token, t_dlst *env)
{
	char	*oldpwd;
	int		status;

	*ptr_token = (*ptr_token)->next;
	if ((*ptr_token) && !is_separator(*ptr_token)
		&& (*ptr_token)->next && !is_separator((*ptr_token)->next))
		return (cd_error_msg("too many arguments", ptr_token, ERROR));
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (cd_error_msg(strerror(errno), ptr_token, ERROR));
	status = 0;
	if (*ptr_token && !is_separator(*ptr_token)
		&& prev_operator(*ptr_token) != PIPE)
		status = go_path(ptr_token);
	else if ((!*ptr_token || is_separator(*ptr_token))
		&& prev_operator(*ptr_token) != PIPE)
		status = go_home(env);
	go_to_end_or_separator(ptr_token);
	if (!status)
		change_pwd(oldpwd, &env);
	free(oldpwd);
	return (status);
}
