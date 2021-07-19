#include "builtins.h"

int	builtins(t_dlst **ptr_token, t_all *all)
{
	if (!ft_strcmp(((*ptr_token))->str, "echo"))
		all->exit_status = echo_cmd(ptr_token, all->fd_out);
	else if (!ft_strcmp((*ptr_token)->str, "cd"))
		all->exit_status = cd_cmd(ptr_token, all->env);
	else if (!ft_strcmp((*ptr_token)->str, "pwd"))
		all->exit_status = pwd_cmd(ptr_token, all->fd_out);
	else if (!ft_strcmp((*ptr_token)->str, "export"))
		all->exit_status = export_cmd(ptr_token, all->env, all->fd_out);
	else if (!ft_strcmp((*ptr_token)->str, "unset"))
		all->exit_status = unset_cmd(ptr_token, all->env);
	else if (!ft_strcmp((*ptr_token)->str, "env"))
		all->exit_status = env_cmd(ptr_token, all->env, all->fd_out);
	else if (!ft_strcmp((*ptr_token)->str, "exit"))
		exit_cmd(all, ptr_token, all->exit_status, &all->shell_history);
	else
		return (0);
	return (1);
}
