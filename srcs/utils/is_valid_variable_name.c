#include "utils.h"

int	is_valid_variable_name(char *variable_name, char end_char)
{
	int	i;

	i = 0;
	if (variable_name[0] != '_' && !ft_isalpha(variable_name[0]))
		return (0);
	while (variable_name[++i] && variable_name[i] != end_char)
	{
		if (variable_name[i] != '_' && !ft_isalnum(variable_name[i]))
			return (0);
	}
	return (1);
}
