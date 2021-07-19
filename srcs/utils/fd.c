#include "minishell.h"

void	close_fds(t_all *all)
{
	if (all->fd_in != STDIN_FILENO)
	{
		close(all->fd_in);
		all->fd_in = STDIN_FILENO;
	}
	if (all->fd_out != STDOUT_FILENO)
	{
		close(all->fd_out);
		all->fd_out = STDOUT_FILENO;
	}
}

void	close_fd(int *fd, int value)
{
	if (*fd != value)
	{
		close(*fd);
		*fd = value;
	}
}
