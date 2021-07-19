#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "utils.h"
# include "error_handlers.h"

void	set_environment(const char	*envp[], t_all *all);
char	*getenv_from_lst(t_dlst *env, const char *name);

#endif
