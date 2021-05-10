#include "../includes/minishell.h"
#include <fcntl.h>

int		executor_run_cmd(char **argv, char **env)
{
	pid_t	pid;
	int		ret;

	pid = fork();
	if (pid == 0)
	{
		ret = execve(argv[0], argv, env);
		exit(1);
	}
	if (pid < 0)
	{
		puts("Fork fail");
		return (1);
	}
	waitpid(pid, &ret, 0);
	return (ret);
}

void	executor_init_fds(int cur[6], t_cmdtable *table)
{
	cur[2] = dup(0);
	cur[3] = dup(1);
	if (table->input_file)
		cur[4] = open(table->input_file, O_RDONLY);
	else
		cur[4] = dup(cur[2]);
}

int     executor(t_cmdtable *cmdtable, char **env)
{
	int			fds[6];
	t_cmdtable	*curtable;
	t_cmd		*curcmd;

	curtable = cmdtable;
	while (curtable)
	{
		executor_init_fds(fds, curtable);
		curcmd = curtable->cmds;
		while (curcmd)
		{
			dup2(fds[4], 0);
			close(fds[4]);
			if (curcmd->next == 0)
			{
				if (curtable->output_file)
					fds[5] = open(curtable->output_file, O_CREAT | O_WRONLY | O_APPEND);
				else
					fds[5] = dup(fds[3]);
			}
			else
			{
				pipe(fds);
				fds[5] = fds[1];
				fds[4] = fds[0];
			}
			dup2(fds[5], 1);
			close(fds[5]);
			executor_run_cmd(curcmd->argv, env);
			curcmd = curcmd->next;
		}
		curtable = curtable->next;
	}
	dup2(fds[2], 0);
	dup2(fds[3], 1);
	close(fds[2]);
	close(fds[3]);
}

int     main(int argc, char **argv, char **env)
{
	t_cmdtable	*test;
	t_cmd		*cmd1;
	t_cmd		*cmd2;

	cmd1 = malloc(sizeof(t_cmd));
	cmd2 = malloc(sizeof(t_cmd));
	cmd1->argv = malloc(sizeof(char*));
	cmd2->argv = malloc(sizeof(char*) * 2);
	cmd1->argv[0] = strdup("/bin/ls");
	cmd1->argv[1] = NULL;
	cmd1->next = cmd2;
	cmd2->argv[0] = strdup("/bin/grep");
	cmd2->argv[1] = strdup("e");
	cmd2->argv[2] = NULL;
	cmd2->next = 0;
	test = malloc(sizeof(t_cmdtable));
	test->cmds = cmd1;
	test->input_file = 0;
	test->output_file = 0;
	test->next = 0;
	executor(test, env);
}