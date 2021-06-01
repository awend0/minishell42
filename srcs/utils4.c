#include "../includes/minishell.h"

int	is_regular_file(char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}

char	*get_result_color(void)
{
	if (g_signal.status == 0)
		return (GREEN);
	return (RED);
}

void	print_prompt(void)
{
	char	**arr;
	char	*curpath;
	int		len;

	curpath = pwd_getcurpath();
	if (!curpath || !ft_strcmp(curpath, "/"))
	{
		ft_putstr_fd(get_result_color(), 1);
		ft_putstr_fd("• "BOLDCYAN"/", 1);
		ft_putstr_fd(BOLDYELLOW" » "RESET, 1);
	}
	else
	{
		arr = ft_split(curpath, '/');
		len = ft_arrlen(arr);
		ft_putstr_fd(get_result_color(), 1);
		ft_putstr_fd("• "BOLDCYAN"/", 1);
		ft_putstr_fd(arr[len - 1], 1);
		ft_putstr_fd(BOLDYELLOW" » "RESET, 1);
	}
}

char	*ft_tolower(char *str)
{
	char	*ret;
	int		i;

	i = 0;
	ret = ft_calloc_save(ft_strlen(str) + 1);
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			ret[i] = str[i] + 32;
		else
			ret[i] = str[i];
		i++;
	}
	return (ret);
}

void	signal_init(void)
{
	g_signal.inter = 0;
	g_signal.quit = 0;
	g_signal.pid = 0;
}
