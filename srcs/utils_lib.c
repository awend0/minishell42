#include "../includes/minishell.h"

int	ft_strlen(char *str)
{
	int		size;

	size = 0;
	while (*str)
	{
		size++;
		str++;
	}
	return (size);
}

int	ft_strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != 0 && s2[i] != 0)
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_concat(const char *s1, const char *s2)
{
	char	*ret;

	if (!s2)
		return ((char *)s1);
	ret = malloc(strlen(s1) + strlen(s2) + 1);
	strcpy(ret, s1);
	strcat(ret, s2);
	return (ret);
}

void	ft_putchar_fd(char c, int fd)
{
	if (write(fd, &c, 1) < 1)
        return ;
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nbr;

	(n < 0) ? ft_putchar_fd('-', fd) : (void)0;
	nbr = (n < 0) ? n * -1 : n;
	if (nbr >= 10)
	{
		ft_putnbr_fd(nbr / 10, fd);
		ft_putnbr_fd(nbr % 10, fd);
	}
	else
		ft_putchar_fd(nbr + '0', fd);
}

static char *ft_strnew(int size)
{
    char    *ret;

    ret = ft_calloc(size + 1, sizeof(char));
    return (ret);
}

static int	ft_nbrlen(int n)
{
	unsigned int	nbr;
	int				neg;
	int				res;

	res = 1;
	neg = (n < 0) ? 1 : 0;
	nbr = (neg) ? n * -1 : n;
	nbr /= 10;
	while (nbr)
	{
		nbr /= 10;
		res++;
	}
	return ((neg) ? res + 1 : res);
}

char    *ft_itoa(int n)
{
	char			*s;
	char			*s1;
	int				neg;
	unsigned int	nbr;
	int				len;

	neg = (n < 0) ? 1 : 0;
	nbr = (neg) ? n * -1 : n;
	len = ft_nbrlen(n);
	s = ft_strnew(len);
	if (!s)
		return (0);
	s1 = s;
	s = s + len - 2;
	*(s1 + len - 1) = nbr % 10 + '0';
	nbr /= 10;
	while (nbr)
	{
		*s = nbr % 10 + '0';
		nbr /= 10;
		s--;
	}
	(neg) ? *s = '-' : (void)0;
	return (s1);
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

char	*ft_strchr(char *s, int c)
{
	while (*s && !(*s == c))
		s++;
	return ((*s == c) ? s : 0);
}

char		*ft_strdup(char *s)
{
	int		i;
	char	*result;

	if ((result = ft_strnew(ft_strlen(s))))
	{
		i = 0;
		while (s[i])
		{
			result[i] = s[i];
			i++;
		}
		result[i] = '\0';
	}
	return (result);
}

char	*ft_strndup(const char *s, size_t n)
{
	char			*res;
	unsigned int	i;

	i = 0;
	res = malloc(sizeof(char) * (n + 1));
	if (res == NULL)
		return (NULL);
	while (i < n)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dest;
	const char	*source;

	if (!src && !dst)
		return (0);
	source = src;
	dest = dst;
	while (n--)
		*dest++ = *source++;
	return (dst);
}

char	*ft_strcpy(char *dst, char *src)
{
	int		len;

	len = ft_strlen(src);
	ft_memcpy(dst, src, len + 1);
	return (dst);
}
