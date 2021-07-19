#include "exec_commands.h"

int	get_exit_status(int wstatus)
{
	int	signal;

	if (WIFSIGNALED(wstatus))
	{
		signal = WTERMSIG(wstatus);
		if (signal == SIGQUIT)
		{
			ft_putstr_fd("Quit:\t", STDERR_FILENO);
			ft_putnbr_fd(signal, STDERR_FILENO);
			write(STDERR_FILENO, "\n", 1);
		}
		return (signal + 128);
	}
	return (WEXITSTATUS(wstatus));
}

void	child_process(t_dlst **ptr_token, t_all *all, char *path)
{
	char	**arg_array;
	char	**envp_array;
	int		status;

	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (all->fd_in != STDIN_FILENO)
		dup2(all->fd_in, STDIN_FILENO);
	if ((all->fd_out != STDOUT_FILENO))
		dup2(all->fd_out, STDOUT_FILENO);
	close_fds(all);
	arg_array = make_arg_array_from_lst(*ptr_token, all->next_operator);
	envp_array = make_array_from_lst(all->env);
	status = execve(path, arg_array, envp_array);
	cmd_error_message((*ptr_token)->str, NULL, strerror(errno));
	clear_array(arg_array);
	clear_array(envp_array);
	exit(status);
}

void	run_program(t_dlst **ptr_token, t_all *all, char *path)
{
	pid_t	pid;
	int		status;

	pid = fork();
	signal(SIGINT, SIG_IGN);
	if (pid < 0)
		all->exit_status = error_handler(NULL, errno);
	else if (!pid)
		child_process(ptr_token, all, path);
	waitpid(pid, &status, 0);
	signal(SIGINT, handle_sigint);
	all->exit_status = get_exit_status(status);
}

int	external_programs(t_dlst **ptr_token, t_all *all)
{
	char		*path;
	char		*path_lst;
	struct stat	s_stat;

	path = NULL;
	path_lst = getenv_from_lst(all->env, "PATH");
	if (path_lst)
	{
		path = find_path(*ptr_token, path_lst);
		free(path_lst);
	}
	if (path)
	{
		run_program(ptr_token, all, path);
		free(path);
	}
	else if (!stat((*ptr_token)->str, &s_stat))
		run_program(ptr_token, all, (*ptr_token)->str);
	else
		return (0);
	go_to_end_or_separator(ptr_token);
	return (1);
}
