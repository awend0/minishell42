#include "../includes/minishell.h"

// int	main(int argc, char **argv, char **env)
// {
// 	t_env		*envs = env_split(env);
// 	t_cmdtable	*test;
// 	t_cmd		*cmd1;

// 	argv++;
// 	envs = init_envs(env);
// 	cmd1 = malloc(sizeof(t_cmd));
// 	cmd1->next = 0;
// 	cmd1->argv = malloc(sizeof(char*));
// 	cmd1->argv = argv;
// 	test = malloc(sizeof(t_cmdtable));
// 	test->cmds = cmd1;
// 	test->input_file = 0;
// 	test->output_file = 0;
// 	test->next = 0;
// 	executor(test, env_split(env));
// }

int	main(int argc, char **argv, char **env)
{
	int			status;
	char		*line;
	t_cmdtable	*cmdtable;
	t_env		*envs;

	(void)argc;
	(void)argv;
	envs = env_split(env);
	status = 0;
	while (!status)
	{
		ft_puts(BOLDCYAN"paSHtet"BOLDYELLOW" » "RESET, 1);
		get_next_line(0, &line);
		if (*line)
		{
			cmdtable = parser(line, envs);
			//test_parsing(cmdtable);
			// printf("status %d\n", executor(cmdtable, envs, env));
			executor(cmdtable, envs, env);
		}
		free(line);
	}
	return (status);
}
