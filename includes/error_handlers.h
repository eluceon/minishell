#ifndef ERROR_HANDLERS_H
# define ERROR_HANDLERS_H

# define RED_COLOR	"\033[1;31m"
# define NONE_COLOR "\033[0;0m"

# include <errno.h>
# include "libft.h"
# include "utils.h"

int		error_handler(const char *message, int error_code);
void	cmd_error_message(char *cmd_name, char *arg_name, char *description);
void	syntax_error_message(t_all *all, t_dlst **ptr_token, char *unexpected);
char	*check_memory_allocation_str(char *str);

#endif
