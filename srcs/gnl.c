#include "../includes/minishell.h"

int	get_next_line(int fd, char **line)
{
	char	buf;

	if (fd < 0 || !line)
		return (-1);
	*line = ft_calloc_save(1);
	while (read(fd, &buf, 1) >= 0)
	{
		if (buf != '\n')
			*line = charcat(*line, buf);
		else
		{
			// write(1, "\n", 1);
			return (1);
		}
	}
	return (0);
}
