#include "../includes/minishell.h"

int		ft_cw(char const *s, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

void	*ft_free_2d(char **str, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (0);
}

int		ft_ws(char const *str, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i] == c)
		i++;
	while (str[i] != c && str[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

char		**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		l;
	char	**str;

	i = -1;
	j = 0;
	if (!s || !c || !(str = (char**)malloc(sizeof(char*) * (ft_cw(s, c) + 1))))
		return (NULL);
	while (ft_cw(s, c) > ++i)
	{
		l = 0;
		if (!(str[i] = (char*)malloc(sizeof(char) * (ft_ws(&s[j], c) + 1))))
		{
			ft_free_2d(str, j);
			return (NULL);
		}
		while (s[j] == c)
			j++;
		while (s[j] != c && s[j])
			str[i][l++] = s[j++];
		str[i][l] = '\0';
	}
	str[i] = 0;
	return (str);
}