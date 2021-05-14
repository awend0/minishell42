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
			tmp = *line;
			*line = charcat(*line, buf);
			free(tmp);
		}
		else
			return (1);
	}
	return (0);
}
