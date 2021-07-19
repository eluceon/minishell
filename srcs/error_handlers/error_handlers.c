#include "error_handlers.h"

int	error_handler(const char *message, int error_code)
{
	ft_putstr_fd(RED_COLOR, STDERR_FILENO);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(NONE_COLOR, STDERR_FILENO);
	if (!message)
		message = strerror(error_code);
	ft_putendl_fd((char *)message, STDERR_FILENO);
	if (error_code == ENOMEM)
		exit(error_code);
	return (error_code);
}

char	*check_memory_allocation_str(char *str)
{
	if (!str)
		error_handler(NULL, ENOMEM);
	return (str);
}
