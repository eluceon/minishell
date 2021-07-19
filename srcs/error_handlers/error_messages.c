#include "builtins.h"

void	cmd_error_message(char *cmd_name, char *arg_name, char *description)
{
	ft_putstr_fd(RED_COLOR, STDERR_FILENO);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(NONE_COLOR, STDERR_FILENO);
	if (cmd_name)
	{
		ft_putstr_fd(cmd_name, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (arg_name)
	{
		ft_putstr_fd("`", STDERR_FILENO);
		ft_putstr_fd(arg_name, STDERR_FILENO);
		ft_putstr_fd("': ", STDERR_FILENO);
	}
	ft_putendl_fd(description, STDERR_FILENO);
}

void	syntax_error_message(t_all *all, t_dlst **ptr_token, char *unexpected)
{
	while (*ptr_token)
		(*ptr_token) = (*ptr_token)->next;
	ft_putstr_fd(RED_COLOR, STDERR_FILENO);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(NONE_COLOR, STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(unexpected, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	all->exit_status = 2;
}
