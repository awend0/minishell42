#include "../includes/minishell.h"

int	ft_strlen(char *str)
{
	int		len;

	len = 0;
	if (!str)
		return (0);
	while (*str)
	{
		str++;
		len++;
	}
	return (len);
}

int	ft_arrlen(char **str)
{
	int		len;

	len = 0;
	if (!str)
		return (0);
	while (*str)
	{
		str++;
		len++;
	}
	return (len);
}

char	*ft_strdup(const char *str)
{
	int		len;
	char	*copy;
	char	*buf_copy;

	len = ft_strlen((char *)str);
	copy = malloc((len + 1) * sizeof(char));
	if (!copy)
		return (0);
	buf_copy = copy;
	while (*str)
	{
		*copy = *str;
		copy++;
		str++;
	}
	*copy = '\0';
	return (buf_copy);
}

void	free_arr(char **arr)
{
	if (!arr)
		return ;
	while (*arr)
	{
		free(*arr);
		arr++;
	}
}

int	get_envs_len(t_env *envs)
{
	int		size;

	size = 0;
	while (envs)
	{
		size++;
		envs = envs->next;
	}
	return (size);
}

int	isspecial(char c)
{
	return (c == 39 || c == '"'
			|| c == '|' || c == ';');
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t');
}

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (unsigned char)c)
			return ((char *)str);
		str++;
	}
	if (*str == (unsigned char)c)
		return ((char *)str);
	return (0);
}

void	ft_puts(char *str, int fd)
{
	while (*str)
	{
		write(fd, str, 1);
		str++;
	}
}

void	print_error_and_exit(char *str)
{
	if (errno != 0)
	{
		ft_puts(strerror(errno), 1);
		ft_puts("\n", 1);
	}
	else
	{
		ft_puts(str, 1);
		ft_puts("\n", 1);
	}
	exit(1);
}

char	*charcat(char *str, char c)
{
	char	*strjoin;
	char	*buf_strjoin;
	int		len;

	len = ft_strlen((char *)str);
	strjoin = ft_calloc(len + 2, sizeof(char));
	if (!strjoin)
		return (0);
	buf_strjoin = strjoin;
	while (*str)
		*strjoin++ = *str++;
	*strjoin++ = c;
	return (buf_strjoin);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*strjoin;
	char	*buf_strjoin;
	int		s1_len;
	int		s2_len;

	if (!s2)
		return ((char *)s1);
	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen((char *)s2);
	strjoin = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!strjoin)
		return (0);
	buf_strjoin = strjoin;
	while (*s1)
		*strjoin++ = *s1++;
	while (*s2)
		*strjoin++ = *s2++;
	*strjoin = '\0';
	return (buf_strjoin);
}

char	**arr_copy(char **dest, char **src)
{
	char	**buf;

	buf = dest;
	while (*src)
		*dest++ = ft_strdup(*src++);
	return (buf);
}
