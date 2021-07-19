#include "termcap_commands.h"

void	reallocated_memory(t_all *all, int counter)
{
	if (counter == 1 && all->cursor_counter == 13)
	{
		free(all->line);
		all->line = NULL;
	}
	else if (counter > 1 && all->cursor_counter > 12)
	{
		all->line = ft_realloc(all->line, counter);
		all->line[--counter] = '\0';
	}
}

char	*escape_press(t_all *all)
{
	int		counter;
	char	*left_step;
	char	*delete_char;

	counter = all->sh_counter;
	left_step = tgetstr("le", NULL);
	if (!left_step)
		free_all_exit(all, ERROR);
	delete_char = tgetstr("dc", NULL);
	if (!delete_char)
		free_all_exit(all, ERROR);
	if (counter >= 1 && all->cursor_counter >= 13)
	{
		tputs(left_step, 1, myputchar);
		tputs(delete_char, 1, myputchar);
		reallocated_memory(all, counter);
		--all->sh_counter;
		--all->cursor_counter;
	}
	return (all->line);
}

char	*printf_symbols(char c, t_all *all)
{
	int	counter;

	counter = all->sh_counter;
	if (counter >= 0)
	{
		all->line = ft_realloc(all->line, counter + 2);
		all->line[counter] = c;
		all->line[++counter] = '\0';
		ft_putchar_fd(c, 1);
		++all->sh_counter;
		++all->cursor_counter;
	}
	return (all->line);
}

char	*enter_press(t_all *all, int *flag)
{
	int	counter;

	counter = all->sh_counter;
	if (counter == 0)
	{
		if (all->line)
		{
			free(all->line);
			all->line = NULL;
		}
	}
	write(1, "\n", 1);
	if (!all->line)
		print_promt();
	else
		++*flag;
	return (all->line);
}

char	*history_operation(t_dlst **ptr_history, t_all *all, int iter_hist)
{
	char	*left_step;
	char	*delete_char;

	left_step = tgetstr("cr", NULL);
	if (!left_step)
		free_all_exit(all, ERROR);
	delete_char = tgetstr("dl", NULL);
	if (!delete_char)
		free_all_exit(all, ERROR);
	check_history_i(all, iter_hist, ptr_history);
	tputs(left_step, 1, myputchar);
	tputs(delete_char, 1, myputchar);
	print_promt();
	print_minishell_history(ptr_history, iter_hist);
	if (all->line)
		free(all->line);
	all->line = ft_strdup((*ptr_history)->str);
	if (!all->line)
		free_all_exit(all, ENOMEM);
	ft_putstr_fd(all->line, 1);
	all->sh_counter = (int)ft_strlen(all->line);
	all->cursor_counter = 12 + all->sh_counter;
	return (all->line);
}
