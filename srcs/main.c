#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_cmdtable	*test;
	t_cmd		*cmd1;
	t_env		*envs;

	printf("I'm alive1\n");
	envs = init_envs(env);
	printf("I'm alive2\n");
	cmd1 = malloc(sizeof(t_cmd));
	printf("I'm alive3\n");
	cmd1->next = 0;
	printf("I'm alive4\n");
	cmd1->argv = malloc(sizeof(char*));
	printf("I'm alive5\n");
	cmd1->argv[0] = strdup("pwd");
	printf("I'm alive6\n");
	cmd1->argv[1] = 0;
	printf("I'm alive7\n");
	test = malloc(sizeof(t_cmdtable));
	printf("I'm alive8\n");
	test->cmds = cmd1;
	printf("I'm alive9\n");
	test->input_file = 0;
	printf("I'm alive10\n");
	test->output_file = 0;
	printf("I'm alive11\n");
	test->next = 0;
	printf("I'm alive12\n");
	executor(test, envs);
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
