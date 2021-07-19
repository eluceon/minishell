#include "termcap_commands.h"

int	check_history_i(t_all *all, int i, t_dlst **ptr_h)
{
	if (!(all->hist_iter) && i == PREVIOUS_HISTORY && *ptr_h
		&& (*ptr_h)->prev && !all->hist_iter)
		++all->hist_iter;
	return (i);
}
