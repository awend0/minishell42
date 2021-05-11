#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_cmdtable	*test;
	t_cmd		*cmd1;
	t_env		*envs;

	argv++;
	cmd1 = malloc(sizeof(t_cmd));
	cmd1->next = 0;
	cmd1->argv = malloc(sizeof(char*));
	cmd1->argv = argv;
	test = malloc(sizeof(t_cmdtable));
	test->cmds = cmd1;
	test->input_file = 0;
	test->output_file = 0;
	test->next = 0;
	executor(test, env);
	/*
	int			status;
	char		*line;
	t_cmdtable	*cmdtable;
	t_env		*envs;

	(void)argc;
	(void)argv;
	envs = init_envs(env);
	status = 0;
	while (!status)
	{
		putstr("sh» ", 1);
		line = get_next_line(0, &line);
		cmdtable = parser(line, envs);
		free(line);
		status = executor(cmdtable, envs);
	}
	return (status);*/
}
