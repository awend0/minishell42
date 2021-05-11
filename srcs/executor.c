#include "../includes/minishell.h"

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

int		executor_isbuiltin(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->argv[0], "cd")
	|| !ft_strcmp(cmd->argv[0], "unset")
	|| !ft_strcmp(cmd->argv[0], "export")
	|| !ft_strcmp(cmd->argv[0], "pwd")
	|| !ft_strcmp(cmd->argv[0], "echo")
	|| !ft_strcmp(cmd->argv[0], "env")
	|| !ft_strcmp(cmd->argv[0], "exit"))
		return (1);
	return (0);
}

int		executor_run_binary(char **argv, char **env)
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

int		executor_run_builtin(char **argv, t_env *envs, char **env)
{
	if (!ft_strcmp(argv[0], "exit"))
		exit(0);
	if (!ft_strcmp(argv[0], "pwd"))
		builtin_pwd();
	if (!ft_strcmp(argv[0], "echo"))
		builtin_echo(argv);
}

int     executor_exec(t_cmdtable *cmdtable, t_env *envs, char **env)
{
	t_cmdtable	*curtable;
	t_cmd		*curcmds;
	int			tmp[7];

	curtable = cmdtable;
	while (curtable)
	{
		curcmds = curtable->cmds;
		executor_init_fds(tmp, curtable);
		while (curcmds)
		{
			executor_redir(tmp[4], 0);
			executor_run_and_redir(curcmds, curtable, tmp);
			executor_redir(tmp[5], 1);
			if (executor_isbuiltin(curcmds))
				executor_run_builtin(curcmds->argv, envs, env);
			else
				executor_run_binary(curcmds->argv, env);
			curcmds = curcmds->next;
		}
		curtable = curtable->next;
	}
	executor_redir(tmp[2], 0);
	executor_redir(tmp[3], 1);
	waitpid(tmp[6], 0, 0);
}

int		scan_path(t_env *envs)
{
	while (envs && ft_strcmp(envs->name, "PATH"))
	{
		printf("[%s]=[%s]\n", envs->name, envs->value);
		envs = envs->next;
	}
	printf("[%s]=[%s]\n", envs->name, envs->value);
}

int		executor(t_cmdtable *table, t_env *envs)
{
	scan_path(envs);
	executor_exec(table, envs, get_env_as_string(envs));
}
