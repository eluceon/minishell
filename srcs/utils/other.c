#include "utils.h"

void	free_char_and_null(char	**str)
{
	free(*str);
	*str = NULL;
}

void	go_to_end_or_separator(t_dlst **ptr_token)
{
	while (*ptr_token && !is_separator(*ptr_token))
		*ptr_token = (*ptr_token)->next;
}

int	last_token(t_dlst *ptr_token)
{
	if (!ptr_token)
		return (NONE);
	while (ptr_token->next != NULL)
		ptr_token = ptr_token->next;
	return (is_separator(ptr_token));
}

int	is_last_token_escaped(t_dlst *ptr_token)
{
	if (!ptr_token)
		return (NONE);
	while (ptr_token->next != NULL)
		ptr_token = ptr_token->next;
	return (ptr_token->flag);
}
