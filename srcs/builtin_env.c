#include "../includes/minishell.h"

int	builtin_env(t_env *envs, int declare_x)
{
	if (!envs)
		return (0);
	while (envs)
	{
		if (!envs->secret)
		{
			if (declare_x)
				ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(envs->name, 1);
			ft_putstr_fd("=", 1);
			if (envs->value)
				ft_putstr_fd(envs->value, 1);
			ft_putstr_fd("\n", 1);
		}
		envs = envs->next;
	}
	return (0);
}
