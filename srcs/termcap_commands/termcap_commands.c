#include "termcap_commands.h"

struct termios	init_settings(void)
{
	int				check_get;
	struct termios	term;
	struct termios	saved_attributes;

	check_get = 0;
	tcgetattr(0, &saved_attributes);
	memcpy(&term, &saved_attributes, sizeof(term));
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	check_get = tgetent(0, getenv("TERM"));
	if (check_get == -1)
		check_get = tgetent(0, "xterm-256color");
	if (check_get == -1)
		ft_crash("Error");
	return (saved_attributes);
}

static void 	check_key_press(char *str, t_all *all, t_dlst **ptr_history)
{
	if (str[0] > 31 && str[0] < 127)
		all->line = printf_symbols(str[0], all);
	else if (!ft_strncmp(str, K_UP, 3) && ft_strcmp(str, "\n") && *ptr_history)
		all->line = history_operation(ptr_history, all, PREVIOUS_HISTORY);
	else if (!ft_strncmp(str, K_DOWN, 3) && ft_strcmp(str, "\n")
		&& *ptr_history && all->hist_iter)
		all->line = history_operation(ptr_history, all, NEXT_HISTORY);
	else if (!ft_strcmp(str, K_CTRL_C))
		all->line = ctrlc_press(all);
	else if (*str == 12)
		all->line = ctrll_press(all);
}

void 	input_control(struct termios s_ats, t_all *all, t_dlst **ptr_history)
{
	char		str[1000];
	uint32_t	ret;
	int			flag;

	flag = 0;
	while (!flag)
	{
		ret = read(0, str, 999);
		if (!ret)
			ft_crash("Read input error");
		str[ret] = 0;
		check_g_sigint(all);
		if (!ft_strcmp(str, K_DEL))
			all->line = escape_press(all);
		else if (!ft_strcmp(str, K_CTRL_D))
			ctrld_press(all, all->sh_counter, s_ats);
		else if (!ft_strcmp(str, "\n"))
			all->line = enter_press(all, &flag);
		check_key_press(str, all, ptr_history);
	}
	tcsetattr(0, TCSANOW, &s_ats);
}

void 	termcap_start(t_all *all, t_dlst **ptr_history)
{
	struct termios	saved_attributes;

	print_promt();
	all->hist_iter = 0;
	all->sh_counter = 0;
	all->cursor_counter = 12;
	if (all->line)
	{
		free(all->line);
		all->line = NULL;
	}
	saved_attributes = init_settings();
	input_control(saved_attributes, all, ptr_history);
}
