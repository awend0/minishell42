#include "../includes/minishell.h"

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

void	print_error_and_exit(char *str)
{
	if (errno != 0)
	{
		ft_putstr_fd(strerror(errno), 1);
		ft_putstr_fd("\n", 1);
	}
	else
	{
		ft_putstr_fd(str, 1);
		ft_putstr_fd("\n", 1);
	}
	exit(1);
}

char	*charcat(char *str, char c)
{
	char	*strjoin;
	char	*buf_strjoin;
	int		len;

	len = ft_strlen((char *)str);
	strjoin = ft_calloc_save(len + 2);
	if (!strjoin)
		return (0);
	buf_strjoin = strjoin;
	while (*str)
		*strjoin++ = *str++;
	*strjoin++ = c;
	return (buf_strjoin);
}

char	**arr_copy(char **dest, char **src)
{
	char	**buf;

	buf = dest;
	while (*src)
		*dest++ = ft_strdup(*src++, 1);
	return (buf);
}

int	check_env_name(char *str)
{
	if ((*str < 65 || *str > 90)
		&& (*str < 97 || *str > 122)
		&& *str != '_')
		return (1);
	str++;
	while (*str && *str != '=')
	{
		if ((*str < 65 || *str > 90)
			&& (*str < 97 || *str > 122)
			&& (*str < 48 || *str > 57)
			&& *str != '_')
			return (1);
		str++;
	}
	return (0);
}
