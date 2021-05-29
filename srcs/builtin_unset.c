#include "../includes/minishell.h"

void	unset_del(t_env *envs, char *name)
{
	while (envs && ft_strcmp(envs->name, name))
		envs = envs->next;
	if (!envs)
		return ;
	if (envs->next)
		envs->next->prev = envs->prev;
	if (envs->prev)
		envs->prev->next = envs->next;
	return ;
}

int	builtin_unset(char **argv, t_env *envs)
{
	int		ret;

	ret = 0;
	if (!argv[1])
		return (0);
	argv++;
	while (*argv)
	{
		if (check_env_name(*argv))
		{
			print_error("unset", *argv, "not a valid identifier");
			ret = 1;
		}
		unset_del(envs, *argv);
		argv++;
	}
	return (ret);
}
