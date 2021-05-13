#include "../includes/minishell.h"

int	executor_run_binary(char **argv, char **env)
{
	int		pid;
	int		ret;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		if (execve(argv[0], argv, env) == -1)
		{
			ft_puts(strerror(errno), 1);
			ft_puts("\n", 1);
		}
		_exit(1);
	}
	else
		if (waitpid(pid, &ret, 0) == -1)
			return (-1);
	return (ret);
}

int	executor_run_builtin(char **argv, t_env *envs, char **env)
{
	(void)envs;
	(void)env;
	if (!ft_strcmp(argv[0], "exit"))
		exit(0);
	if (!ft_strcmp(argv[0], "pwd"))
		return (builtin_pwd());
	if (!ft_strcmp(argv[0], "echo"))
		return (builtin_echo(argv));
	if (!ft_strcmp(argv[0], "cd"))
		return (builtin_cd(argv, envs));
	return (0);
}

int	executor_cmd(t_cmd *cmd, t_env *envs, char **env, int *ret)
{
	if (is_builtin(cmd))
	{
		*ret = executor_run_builtin(cmd->argv, envs, env);
		return (*ret);
	}
	if (!file_exist(cmd->argv[0]))
		cmd->argv[0] = scan_path(cmd->argv[0], envs);
	*ret = executor_run_binary(cmd->argv, env);
	return (*ret);
}

int	executor_exec(t_cmdtable *cmdtable, t_env *envs, char **env)
{
	t_cmdtable	*curtable;
	t_cmd		*curcmds;
	int			tmp[7];

	tmp[6] = 0;
	curtable = cmdtable;
	while (curtable)
	{
		curcmds = curtable->cmds;
		executor_init_fds(tmp, curtable);
		while (curcmds)
		{
			if (executor_redir(tmp[4], 0) == -1
				|| executor_run_and_redir(curcmds, curtable, tmp) == -1
				|| executor_redir(tmp[5], 1) == -1
				|| executor_cmd(curcmds, envs, env, &tmp[6]) == -1)
				return (-1);
			curcmds = curcmds->next;
		}
		if (executor_redir(tmp[2], 0) == -1 || executor_redir(tmp[3], 1) == -1)
			return (-1);
		curtable = curtable->next;
	}
	return (tmp[6]);
}

int	executor(t_cmdtable *table, t_env *envs, char **env)
{
	return (executor_exec(table, envs, env));
}
