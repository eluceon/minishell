#include "exec_commands.h"

int	find_file_in_dir(const char *path, const char *file)
{
	struct dirent	*entry;
	int				ret;
	DIR				*dirp;

	ret = 0;
	dirp = opendir(path);
	if (!dirp)
		return (0);
	errno = 0;
	while (1)
	{
		entry = readdir(dirp);
		if (!entry)
			break ;
		if (!ft_strcmp(entry->d_name, file))
		{
			ret = 1;
			break ;
		}
	}
	if (errno && !entry)
		error_handler(NULL, errno);
	closedir(dirp);
	return (ret);
}

void	make_full_cmd_name(char **path, char *file)
{
	int		len;
	char	*full_file_name;

	len = ft_strlen(*path) + ft_strlen(file) + 2;
	full_file_name = (char *)malloc(len * sizeof(char));
	if (!full_file_name)
		error_handler(NULL, ENOMEM);
	ft_strlcpy(full_file_name, *path, len);
	ft_strlcat(full_file_name, "/", len);
	ft_strlcat(full_file_name, file, len);
	free(*path);
	*path = full_file_name;
}

char	*find_path(t_dlst *ptr_token, char *path_lst)
{
	char	*path;
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (j < 0 || path_lst[j])
	{
		i = ++j;
		while (path_lst[j] && path_lst[j] != ':')
			j++;
		path = ft_substr(path_lst, i, j - i);
		if (!path)
			error_handler(NULL, ENOMEM);
		if (find_file_in_dir(path, ptr_token->str))
		{
			make_full_cmd_name(&path, ptr_token->str);
			return (path);
		}
		free(path);
	}
	return (NULL);
}
