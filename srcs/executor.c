#include "../includes/minishell.h"
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

int		executor_init_fds(int tmp[7], t_cmdtable *table)
{
	tmp[2] = dup(0);
	tmp[3] = dup(1);
	if (table->input_file)
	{
		tmp[4] = open(table->input_file, O_RDONLY);
		if (tmp[4] == -1)
			print_error_and_exit("Error: file opening error\n");
	}
	else
	{
		tmp[4] = dup(tmp[2]);
		if (tmp[4] == -1)
			print_error_and_exit("Error: file descriptor duplication error\n");
	}
	return (0);
}

int		executor_redir(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
		print_error_and_exit("Error: redirection failed");
	close(oldfd);
	return (0);
}

int		executor_run_and_redir(t_cmd *cmd, t_cmdtable *table, int tmp[7])
{
	if (cmd->next == 0)
	{
		if (table->output_file)
		{
			tmp[5] = open(table->output_file, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
			if (tmp[5] == -1)
				print_error_and_exit("Error: failed file creation\n");
		}
		else
		{
			tmp[5] = dup(tmp[3]);
			if (tmp[5] == -1)
				print_error_and_exit("Error: file descriptor duplication error\n");
		}
	}
	else
	{
		if (pipe(tmp) == -1)
			print_error_and_exit("Error: pipe creation error\n");
		tmp[5] = tmp[1];			
		tmp[4] = tmp[0];
		return (0);
	}
}

int		executor_fork_run(char **argv, char **env)
{
	int		pid;
	int		ret;

	pid = fork();
	if (pid == -1)
		print_error_and_exit("Error: fork failed\n");
	if (pid == 0)
	{
		if (execve(argv[0], argv, env) == -1)
			print_error_and_exit("Error: binary execution error\n");
		_exit(1);
	}
	else
		if (waitpid(pid, &ret, 0) == -1)
			print_error_and_exit("Error: waitpid error o.o\n");
	return (0);
}

int     executor(t_cmdtable *cmdtable, t_env **envs)
{
	t_cmdtable	*curtable;
	t_cmd		*curcmds;
	int			tmp[7];
	char		**env;

	env = get_env_as_string(envs);
	curtable = cmdtable;
	while (curtable)
	{
		curcmds = curtable->cmds;
		if (executor_init_fds(tmp, curtable))
			return (1);
		while (curcmds)
		{
			executor_redir(tmp[4], 0);
			executor_run_and_redir(curcmds, curtable, tmp);
			executor_redir(tmp[5], 1);
			executor_fork_run(curcmds->argv, env);
			curcmds = curcmds->next;
		}
		curtable = curtable->next;
	}
	executor_redir(tmp[2], 0);
	executor_redir(tmp[3], 1);
	waitpid(tmp[6], 0, 0);
}

/*
** Test "/bin/ls | grep e" 
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
*/