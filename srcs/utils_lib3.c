#include "../includes/minishell.h"

char	*ft_strchr(char *s, int c)
{
	while (*s && !(*s == c))
		s++;
	if (*s == c)
		return (s);
	else
		return (0);
}

char	*ft_strdup(char *s, int save)
{
	int		i;
	char	*result;

	if (!s || !(*s))
		return (0);
	if (!save)
		result = ft_calloc_save2(ft_strlen(s) + 1);
	else
		result = ft_calloc_save(ft_strlen(s) + 1);
	i = 0;
	while (s[i])
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strndup(char *s, int n, int save)
{
	char	*res;
	int		i;

	if (!s || !(*s))
		return (0);
	i = 0;
	if (!save)
		res = ft_calloc_save2(n + 1);
	else
		res = ft_calloc_save(n + 1);
	if (!res)
		return (0);
	while (i < n)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

void	*ft_memcpy(void *dst, void *src, int n)
{
	char	*dest;
	char	*source;

	if (!src && !dst)
		return (0);
	source = src;
	dest = dst;
	dest[n] = '\0';
	while (n--)
		*dest++ = *source++;
	return (dst);
}

char	*ft_strcpy(char *dst, char *src)
{
	int	len;

	len = ft_strlen(src);
	ft_memcpy(dst, src, len + 1);
	return (dst);
}
