#include "builtins.h"

int	pwd_cmd(t_dlst **ptr_token, int fd_out)
{
	char	*cwd;

	*ptr_token = (*ptr_token)->next;
	go_to_end_or_separator(ptr_token);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		cmd_error_message("pwd", NULL, strerror(errno));
		return (ERROR);
	}
	ft_putendl_fd(cwd, fd_out);
	free(cwd);
	return (SUCCESS);
}
