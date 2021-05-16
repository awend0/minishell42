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
	free(envs->name);
	free(envs->value);
	free(envs);
	return ;
}

int	builtin_unset(char **argv, t_env *envs)
{
	if (!argv[1])
		return (0);
	argv++;
	while (*argv)
	{
		if (check_env_name(*argv))
		{
			print_error("unset", *argv, "not a valid identifier");
			return (1);
		}
		unset_del(envs, *argv);
		argv++;
	}
	return (0);
}
