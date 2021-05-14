#include "../includes/minishell.h"

int	builtin_env(t_env *envs, int declare_x)
{
	if (!envs)
		return (0);
	while (envs)
	{
		if (declare_x)
			ft_puts("declare -x ", 1);
		ft_puts(envs->name, 1);
		ft_puts("=", 1);
		ft_puts(envs->value, 1);
		ft_puts("\n", 1);
		envs = envs->next;
	}
	return (0);
}