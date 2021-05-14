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

void	print_rediretion(char *str, char **arr)
{
	int		i;

	ft_puts(str, 1);
	if (arr)
	{
		i = -1;
		while (arr[++i])
		{
			ft_puts("<", 1);
			ft_puts(arr[i], 1);
			ft_puts("> ", 1);
		}
	}
}

void	test_parsing(t_cmdtable *table)
{
	int		i;

	while (table)
	{
		while (table->cmds)
		{
			i = -1;
			while (table->cmds->argv[++i])
			{
				ft_puts("<", 1);
				ft_puts(table->cmds->argv[i], 1);
				ft_puts("> ", 1);
			}
			table->cmds = table->cmds->next;
		}
		print_rediretion("\nInput Files: ", table->input_file);
		print_rediretion("\nOutput Files: ", table->output_file);
		print_rediretion("\nAppend Files: ", table->append_file);
		table = table->next;
		ft_puts("\n", 1);
	}
}
