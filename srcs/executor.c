#include "../includes/minishell.h"

int		executor_run_cmd(char *path, char **argv, char **env)
{
	pid_t	pid;
	int		ret;

	pid = fork();
	if (pid == 0)
	{
		ret = execve(path, argv, env);
		printf("%s\n", strerror(errno));
	}
	if (pid < 0)
	{
		puts("Fork fail");
		return (-1);
	}
	waitpid(pid, &ret, 0);
	return (1);
}

int     executor(t_cmdtable *cmdtable, char **env)
{
	t_cmdtable	*cur;

	cur = cmdtable;
	while (cur)
	{
		executor_run_cmd(cmdtable->cmds->argv[0], cmdtable->cmds->argv, env);
		cur = cur->next;
	}
}

int     main(int argc, char **argv, char **env)
{
	t_cmdtable	*test;
	t_cmd		*cmd;

	cmd = malloc(sizeof(t_cmd));
	argv++;
	cmd->argv = argv;
	cmd->next = 0;
	test = malloc(sizeof(t_cmdtable));
	test->cmds = cmd;
	test->next = 0;
	executor(test, env);
}