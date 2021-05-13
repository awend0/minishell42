#include "../includes/minishell.h"

void	free_env(t_env *env)
{
	free(env->name);
	free(env->value);
	free(env);
}

void	unset_middle(t_env **ptr)
{
	t_env	*prev;
	t_env	*next;
	t_env	*envs;

	prev = 0;
	next = 0;
	envs = *ptr;
	next = envs->next;
	prev = envs->prev;
	//free_env(envs);
	prev->next = next;
	next->prev = prev;
	envs = *ptr;
}

void	unset_first(t_env **ptr)
{
	t_env	*next;
	t_env	*envs;

	next = 0;
	envs = *ptr;
	if (envs->next)
		next = envs->next;
	//free_env(envs);
	next->prev = 0;
}

void	unset_last(t_env **ptr)
{
	t_env	*prev;
	t_env	*envs;

	prev = 0;
	envs = *ptr;
	if (envs->prev)
		prev = envs->prev;
	//free_env(envs);
	prev->next = 0;
}

int	builtin_unset(char **argv, t_env *envs)
{
	if (!argv[1])
	{
		ft_puts("unset: not enough arguments\n", 1);
		return (-1);
	}
	while (envs && ft_strcmp(envs->name, argv[1]))
		envs = envs->next;
	if (!envs || ft_strcmp(envs->name, argv[1]))
		return (0);
	if (envs->next && envs->prev)
	{
		unset_middle(&envs);
		return (0);
	}
	if (!envs->next)
	{
		unset_last(&envs);
		return (0);
	}
	if (!envs->prev)
	{
		unset_first(&envs);
		return (0);
	}
	return (0);
}