#include "../includes/minishell.h"

int	cd_home(t_env *envs)
{
	char	*path;

	path = get_env(envs, "HOME");
	if (!path)
	{
		print_error("cd", 0, "HOME not set");
		return (1);
	}
	modify_env(envs, "OLDPWD", pwd_getcurpath());
	if (chdir(path) == -1)
	{
		print_error("cd", path, 0);
		return (1);
	}
	return (0);
}

int	cd_back(t_env *envs)
{
	char	*path;

	path = get_env(envs, "OLDPWD");
	if (!path)
	{
		print_error("cd", 0, "OLDPWD not set");
		return (1);
	}
	modify_env(envs, "OLDPWD", pwd_getcurpath());
	if (chdir(path) == -1)
	{
		print_error("cd", path, 0);
		return (1);
	}
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\n", 1);
	return (0);
}

int	builtin_cd(char **argv, t_env *envs)
{
	if (!argv[1])
		return (cd_home(envs));
	if (!ft_strcmp(argv[1], "-"))
		return (cd_back(envs));
	modify_env(envs, "OLDPWD", pwd_getcurpath());
	if (chdir(argv[1]) == -1)
	{
		print_error("cd", argv[1], 0);
		return (1);
	}
	return (0);
}
