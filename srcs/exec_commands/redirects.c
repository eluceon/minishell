#include "exec_commands.h"

int	open_fd_output_redirect(t_all *all, t_dlst **ptr_token, t_dlst *tmp_token)
{
	int		fd;

	go_to_end_or_separator(&tmp_token);
	if (tmp_token->next)
	{
		if (all->fd_in != STDIN_FILENO)
			close(all->fd_in);
		fd = open(tmp_token->next->str, O_RDONLY, S_IRWXU);
		if (fd < 0)
		{
			(cmd_error_message(NULL, tmp_token->next->str, strerror(errno)));
			while (*ptr_token)
				*ptr_token = (*ptr_token)->next;
			all->exit_status = 1;
			return (STDIN_FILENO);
		}
		return (fd);
	}
	return (all->fd_in);
}

int	open_fd_input_redirect(t_all *all, t_dlst **ptr_token, t_dlst*tmp_token)
{
	int	fd;

	fd = STDOUT_FILENO;
	if (tmp_token)
	{
		if (all->fd_out != STDOUT_FILENO)
			close(all->fd_out);
		if (all->next_operator == TRUNC)
			fd = open(tmp_token->next->str,
					O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
		else if (all->next_operator == APPEND)
			fd = open(tmp_token->next->str,
					O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
		if (fd < 0)
		{
			(cmd_error_message(NULL, tmp_token->next->str, strerror(errno)));
			while (*ptr_token)
				*ptr_token = (*ptr_token)->next;
			all->exit_status = 1;
			return (STDOUT_FILENO);
		}
		return (fd);
	}
	return (all->fd_out);
}

void	open_fd_here_document(t_all *all, t_dlst **ptr_token)
{
	t_dlst	*tmp;
	char	*line;
	int		ret;

	tmp = *ptr_token;
	go_to_end_or_separator(&tmp);
	while (tmp->next)
	{
		ret = read_line(all->fd_in, &line);
		if (ret < 0)
			error_handler(NULL, errno);
		if (!ft_strcmp(line, tmp->next->str))
		{
			free(line);
			break ;
		}
		line = handle_dollar_heredoc(line, all);
		ft_putendl_fd(line, all->fd_out);
		free(line);
		line = NULL;
	}
}

void	heredoc_processing(t_all *all, t_dlst **tmp_token)
{
	int		fd[2];

	if (pipe(fd) < 0)
		error_handler(NULL, errno);
	if (all->fd_out == STDOUT_FILENO)
		all->fd_out = fd[1];
	else
		close(fd[1]);
	close_fd(&all->fd_in, STDIN_FILENO);
	open_fd_here_document(all, tmp_token);
	close_fds(all);
	all->fd_in = fd[0];
}

void	redirections(t_all *all, t_dlst **ptr_token)
{
	t_dlst	*tmp_token;

	tmp_token = *ptr_token;
	while (all->next_operator == INPUT || all->next_operator == TRUNC
		|| all->next_operator == APPEND || all->next_operator == HEREDOC)
	{
		go_to_end_or_separator(&tmp_token);
		if (all->next_operator == INPUT)
			all->fd_in = open_fd_output_redirect(all, ptr_token, tmp_token);
		else if (all->next_operator == TRUNC
			|| all->next_operator == APPEND)
			all->fd_out = open_fd_input_redirect(all, ptr_token, tmp_token);
		else if (all->next_operator == HEREDOC)
			heredoc_processing(all, &tmp_token);
		tmp_token = tmp_token->next;
		all->next_operator = next_operator(tmp_token);
	}
}
