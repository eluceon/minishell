#include "utils.h"

void	free_doble_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
	{
		free(array[i]);
		array[i] = NULL;
	}
	free(array);
	array = NULL;
}

int	free_all_exit(t_all *all, int error_code)
{
	if (all->env)
		doubly_lst_clear(&all->env);
	if (all->lst_token)
		doubly_lst_clear(&all->lst_token);
	if (all->shell_history)
		doubly_lst_clear(&all->shell_history);
	exit (error_code);
	return (0);
}
