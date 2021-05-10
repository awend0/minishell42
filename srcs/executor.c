#include "../includes/minishell.h"

int     main(int argc, char **argv, char **env)
{
	t_cmdtable	*test;
	t_cmd		*cmd;

	cmd = calloc(1, sizeof(t_cmd));
	cmd->argc = 1;
	cmd->argv[0] = strdup("/bin/ls");
	cmd->next = 0;
	test = calloc(1, sizeof(t_cmdtable));
	test->cmds = cmd;
	test->input_file = 0;
	test->output_file = 1;
	test->next = 0;
	executor(cmd, env);
}

int		executor_run_cmd(char *path, char **argv, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execve(path, argv, env);
	}
}

int     executor(t_cmdtable *cmdtable, char **env)
{
	t_cmdtable	*cur;

	while (cur)
	{
		
		cur = cur->next;
	}
}