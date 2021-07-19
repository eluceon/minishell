#include <minishell.h>

void	exec_builtins_or_external_programs(t_all *all, t_dlst **ptr_token)
{
	if (!*ptr_token)
		return ;
	else if (!builtins(ptr_token, all) && !external_programs(ptr_token, all))
	{
		cmd_error_message((*ptr_token)->str, NULL, "command not found");
		go_to_end_or_separator(ptr_token);
		all->exit_status = 127;
	}
}

t_dlst	*check_syntax_and_get_token_pos(t_all *all)
{
	t_dlst	*ptr_token;
	t_dlst	*tmp;

	ptr_token = all->lst_token;
	tmp = ptr_token;
	while (tmp->next)
		tmp = tmp->next;
	if (ptr_token->flag & ESCAPED_CHAR)
		return (ptr_token);
	else if (is_separator(ptr_token) == PIPE
		|| is_separator(ptr_token) == SEMICOLON)
		syntax_error_message(all, &ptr_token, ptr_token->str);
	else if ((is_separator(tmp) == PIPE)
		|| (is_separator(tmp) == SEMICOLON
			&& is_separator(tmp->prev) == SEMICOLON)
		|| (is_separator(tmp) == SEMICOLON && is_separator(tmp->prev)))
		syntax_error_message(all, &ptr_token, tmp->str);
	else if (is_separator(tmp) && is_separator(tmp) != SEMICOLON)
		syntax_error_message(all, &ptr_token, "newline");
	return (ptr_token);
}

void	skip_separator(t_dlst **ptr_token)
{
	while (*ptr_token && (is_separator(*ptr_token) == INPUT
			|| is_separator(*ptr_token) == TRUNC
			|| is_separator(*ptr_token) == APPEND
			|| is_separator(*ptr_token) == HEREDOC))
	{
		*ptr_token = (*ptr_token)->next;
		go_to_end_or_separator(ptr_token);
	}
	if (*ptr_token && (is_separator(*ptr_token)))
		*ptr_token = (*ptr_token)->next;
}

void	check_redirections(t_all *all, t_dlst **ptr_token)
{
	if (all->next_operator == INPUT || all->next_operator == TRUNC
		|| all->next_operator == APPEND || all->next_operator == HEREDOC)
		redirections(all, ptr_token);
}

int	executor_loop(t_all *all)
{
	t_dlst		*ptr_token;
	int			fd[2];
	int			next_pipe;

	ptr_token = check_syntax_and_get_token_pos(all);
	while (ptr_token)
	{
		all->next_operator = next_operator(ptr_token);
		next_pipe = is_pipe(ptr_token);
		if (next_pipe)
		{
			if (pipe(fd) < 0)
				return (error_handler(NULL, errno));
			all->fd_out = fd[1];
		}
		else
			all->fd_out = STDOUT_FILENO;
		check_redirections(all, &ptr_token);
		exec_builtins_or_external_programs(all, &ptr_token);
		close_fds(all);
		all->fd_in = (next_pipe != NONE) * fd[0];
		skip_separator(&ptr_token);
	}
	return (all->exit_status);
}
