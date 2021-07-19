#include "utils.h"

char	*ft_str_replace(char *dst, char *src, int dst_start, int dst_end)
{
	char	*new_str;
	int		len;

	if (!dst || !src || dst_end < dst_start
		|| dst_start < 0 || dst_end > (int)(ft_strlen(dst) - 1))
		return (NULL);
	len = ft_strlen(dst) - (dst_end - dst_start + 1) + ft_strlen(src);
	new_str = (char *)calloc((len + 1), sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strlcat(new_str, dst, dst_start + 1);
	ft_strlcat(new_str, src, ft_strlen(new_str) + ft_strlen(src) + 1);
	ft_strlcat(new_str, dst + dst_end + 1,
		ft_strlen(new_str) + ft_strlen(dst + dst_end + 1) + 1);
	return (new_str);
}
