#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include "signal_handlers.h"
# include "environment.h"
# include "parsing.h"
# include "termcap_commands.h"
# include "builtins.h"
# include "exec_commands.h"

void	open_history_file(t_dlst **head_history, t_dlst **ptr_history);
int		executor_loop(t_all *all);

#endif
