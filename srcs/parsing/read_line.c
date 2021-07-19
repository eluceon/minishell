#include "parsing.h"

int	free_null_str(char	**str, int ret_value)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
	return (ret_value);
}

int	read_line(int fd, char **line)
{
	char	ch;
	int		len;
	int		ret;

	*line = ft_strdup("");
	if (!*line)
		error_handler(NULL, ENOMEM);
	len = 0;
	while (1)
	{
		ret = read(fd, &ch, 1);
		if (ret < 0 && errno == EINTR)
			continue ;
		else if (ret < 0)
			return (free_null_str(line, ret));
		if (!ret || ch == '\n')
			break ;
		*line = ft_realloc(*line, len + 2);
		if (!*line)
			error_handler(NULL, ENOMEM);
		(*line)[len] = ch;
		(*line)[++len] = '\0';
	}
	return (ret);
}
