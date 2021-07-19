#include "minishell.h"
int	g_sigint;

int	main(int argc, char *argv[], char *envp[])
{
	t_all	all;

	ft_bzero(&all, sizeof(t_all));
	if (argc != 1 || !argv)
		return (error_handler("Wrong arguments", 1));
	set_signal_handlers();
	set_environment((const char **)envp, &all);
	open_history_file(&all.shell_history, &all.ptr_history);
	while (1)
	{
		g_sigint = 0;
		termcap_start(&all, &all.ptr_history);
		all.lst_token = parsing(&all);
		if (all.lst_token)
			executor_loop(&all);
		doubly_lst_clear(&all.lst_token);
		if (g_sigint)
			all.exit_status = 130;
	}
	save_history_to_file_and_close(&all.shell_history);
	doubly_lst_clear(&all.env);
	return (0);
}
