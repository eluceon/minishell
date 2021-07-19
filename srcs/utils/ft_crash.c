#include "utils.h"

void	ft_crash(const char *str)
{
	write(2, "\033[31m", 5);
	write(2, str, ft_strlen(str));
	write(2, "\033[0m\n", 5);
	exit(EXIT_FAILURE);
}
