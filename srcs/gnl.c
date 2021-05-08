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

size_t	ft_strlen(const char *str)
{
	size_t		len;

	len = 0;
	if (!str)
		return (0);
	while (*str)
	{
		len++;
		str++;
	}
	return (len);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*array;

	array = malloc(count * size);
	if (!array)
		return (0);
	return (ft_bzero(array, count * size));
}

char	*ft_strjoin(char const *s1, char const s2)
{
	char	*strjoin;
	char	*buf_strjoin;
	int		s1_len;

	s1_len = ft_strlen((char *)s1);
	strjoin = malloc((s1_len + 2) * sizeof(char));
	if (!strjoin)
		return (0);
	buf_strjoin = strjoin;
	while (*s1)
		*strjoin++ = *s1++;
	*strjoin++ = s2;
	*strjoin = '\0';
	return (buf_strjoin);
}

int	get_next_line(int fd, char **line)
{
	char	buf;
	char	*tmp;

	if (fd < 0 || !line)
		return (-1);
	*line = ft_calloc(1, sizeof(char));
	while (read(fd, &buf, 1) > 0)
	{
		if (buf != '\n')
		{
			tmp = *line;
			*line = ft_strjoin(*line, buf);
			free(tmp);
		}
		else
			return (1);
	}
	return (0);
}
