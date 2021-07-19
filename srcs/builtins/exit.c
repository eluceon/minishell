#include "builtins.h"

int	exit_error_msg(char *msg, char *arg_name, t_dlst **ptr_token, int status)
{
	cmd_error_message("exit", arg_name, msg);
	go_to_end_or_separator(ptr_token);
	return (status);
}

void	exit_cmd(t_all	*all, t_dlst **ptr_token,
		unsigned char exit_status, t_dlst **shell_hist)
{
	unsigned char	status;

	status = 0;
	*ptr_token = (*ptr_token)->next;
	ft_putendl_fd("exit", STDERR_FILENO);
	if (!(*ptr_token))
		status = exit_status;
	else if (!is_number((*ptr_token)->str) && !is_separator(*ptr_token))
		status = exit_error_msg("numeric argument required",
				(*ptr_token)->str, ptr_token, 2);
	else if (!is_separator(*ptr_token)
		&& (*ptr_token)->next && !is_separator((*ptr_token)->next))
		status = exit_error_msg("too many arguments", NULL, ptr_token, 1);
	else if (is_number((*ptr_token)->str))
	{
		status = ft_atoi((*ptr_token)->str);
		go_to_end_or_separator(ptr_token);
	}
	save_history_to_file_and_close(shell_hist);
	free_all_exit(all, status);
}
