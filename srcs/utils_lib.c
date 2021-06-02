#include "../includes/minishell.h"

char	*ft_strcat(char *s1, char *s2)
{
	int		i;
	int		j;

	j = 0;
	i = ft_strlen(s1);
	while (s2[j])
	{
		s1[i] = s2[j];
		i++;
		j++;
	}
	return (s1);
}

int	ft_strlen(char *str)
{
	int		size;

	if (!str || !(*str))
		return (0);
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

char	*ft_concat(char *s1, char *s2)
{
	char	*ret;

	if (!s2)
		return ((char *)s1);
	ret = ft_calloc_save(ft_strlen(s1) + ft_strlen(s2) + 1);
	ft_strcpy(ret, s1);
	ft_strcat(ret, s2);
	return (ret);
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
	strjoin = ft_calloc_save((s1_len + s2_len + 1) * sizeof(char));
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
