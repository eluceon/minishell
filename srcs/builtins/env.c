#include "builtins.h"

int	env_cmd(t_dlst **ptr_token, t_dlst *env, int fd_out)
{
	*ptr_token = (*ptr_token)->next;
	go_to_end_or_separator(ptr_token);
	if (!env)
		return (errno = 126);
	while (env)
	{
		ft_putendl_fd(env->str, fd_out);
		env = env->next;
	}
	return (SUCCESS);
}
