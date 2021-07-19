#include "termcap_commands.h"

void	ctrld_press(t_all *all, int counter, struct termios s_ats)
{
	char	*signal;

	if (counter == 0 && !all->line)
	{
		write(1, "exit\n", 5);
		tcsetattr(0, TCSANOW, &s_ats);
		free_all_exit(all, all->exit_status);
	}
	else
	{
		signal = tgetstr("bl", NULL);
		if (!signal)
			free_all_exit(all, ERROR);
		tputs(signal, 1, myputchar);
	}
}

char	*ctrlc_press(t_all *all)
{
	if (all->line)
		free(all->line);
	all->line = ft_strdup(" ");
	if (!all->line)
		free_all_exit(all, ENOMEM);
	all->cursor_counter = 12;
	all->sh_counter = 0;
	print_promt();
	return (all->line);
}

char	*ctrll_press(t_all *all)
{
	char	*clear_scr;

	clear_scr = tgetstr("cl", NULL);
	if (!clear_scr)
		free_all_exit(all, ERROR);
	tputs(clear_scr, 1, myputchar);
	print_promt();
	if (all->line && all->sh_counter > 0 && all->cursor_counter > 12)
	{
		ft_putstr_fd(all->line, 1);
		all->sh_counter = ft_strlen(all->line);
		all->cursor_counter = 12 + all->sh_counter;
	}
	return (all->line);
}
