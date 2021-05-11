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

void	test_parsing(t_cmdtable *table)
{
	int		i;

	i = -1;
	while (table)
	{
		while (table->cmds)
		{
			while (table->cmds->argv[++i])
			{
				printf("%s \n", table->cmds->argv[i]);
			}
			table->cmds = table->cmds->next;
		}
		table = table->next;
	}
}
