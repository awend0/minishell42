#include "../includes/minishell.h"

void	test_init_envs(t_env *envs)
{
	while (envs)
	{
		printf("%s=%s\n", envs->name, envs->value);
		envs = envs->next;
	}
}

void	test_envs_to_strings(t_env *envs)
{
	char	**env;

	env = get_env_as_string(envs);
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
