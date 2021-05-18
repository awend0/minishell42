#include "../includes/minishell.h"

void	*ft_bzero(void *s, size_t n)
{
	unsigned char	*buf;

	buf = s;
	while (n > 0)
	{
		*buf = '\0';
		buf++;
		n--;
	}
	return (s);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*array;

	array = malloc(count * size);
	if (!array)
		return (0);
	return (ft_bzero(array, count * size));
}

// int	check_termcaps(char s)
// {
// 	if (!ft_strcmp(&s, "\e[A"))
// 	{
// 		write(1, " up ", 4);
// 		return (1);
// 	}
// 	return (0);
// }

int	get_next_line(int fd, char **line)
{
	char	buf;
	char	*tmp;

	if (fd < 0 || !line)
		return (-1);
	*line = ft_calloc(1, sizeof(char));
	while (read(fd, &buf, 1) >= 0)
	{
		if (buf != '\n')
		{
			// if (!check_termcaps(buf))
			// {
			// write(1, &buf, 1);
			tmp = *line;
			*line = charcat(*line, buf);
			free(tmp);
			// }
		}
		else
		{
			// write(1, "\n", 1);
			return (1);
		}
	}
	return (0);
}
