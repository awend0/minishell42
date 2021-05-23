#include "../includes/minishell.h"

int	builtin_cd(char **argv, t_env *envs)
{
	char	*path;

	(void)envs;
	path = 0;
	if (!argv[1])
	{
		path = get_env(envs, "HOME");
		if (!path)
		{
			print_error("cd", 0, "HOME not set");
			return (1);
		}
		modify_env(envs, "OLDPWD", pwd_getcurpath());
		if (chdir(path) == -1)
		{
			print_error("cd", 0, 0);
			return (1);
		}
		return (0);
	}
	if (!ft_strcmp(argv[1], "-"))
	{
		path = get_env(envs, "OLDPWD");
		if (!path)
		{
			print_error("cd", 0, "OLDPWD not set");
			return (1);
		}
		modify_env(envs, "OLDPWD", pwd_getcurpath());
		if (chdir(path) == -1)
		{
			print_error("cd", 0, 0);
			return (1);
		}
		ft_putstr_fd(path, 1);
		ft_putstr_fd("\n", 1);
		return (0);
	}
	modify_env(envs, "OLDPWD", pwd_getcurpath());
	if (chdir(argv[1]) == -1)
	{
		print_error("cd", 0, 0);
		return (1);
	}
	return (0);
}
