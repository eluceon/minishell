#include "termcap_commands.h"

void	check_g_sigint(t_all *all)
{
	if (g_sigint)
	{
		free(all->line);
		all->line = NULL;
		all->sh_counter = 0;
		all->cursor_counter = 12;
		all->exit_status = 130;
		g_sigint = 0;
	}
}
