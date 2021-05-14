#include "../includes/minishell.h"
#include "limits.h"

int	builtin_cd(char **argv, t_env *envs)
{
	char	*path;

	(void)envs;
	if (!argv[1])
	{
		path = get_env(envs, "HOME");
		if (!path)
		{
			ft_puts("cd: You haven no HOME :(((\n", 1);
			return (-1);
		}
		if (chdir(path) == -1)
			return (-1);
		return (0);
	}
	if (!ft_strcmp(argv[1], "-"))
	{
		path = get_env(envs, "OLDPWD");
		if (!path)
		{
			ft_puts("cd: OLDPWD not set\n", 1);
			return (-1);
		}
		if (chdir(path) == -1)
			return (-1);
		return (0);
	}
	if (chdir(argv[1]) == -1)
	{
		ft_puts(strerror(errno), 1);
		ft_puts("\n", 1);
		return (-1);
	}
	return (0);
}
