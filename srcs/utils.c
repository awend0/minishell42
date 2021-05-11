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

int	ft_ischar(char c)
{
	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t');
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
		ft_puts(strerror(errno), 1);
	else
		ft_puts(str, 1);
	exit(1);
}
