#include "../includes/minishell.h"

int	executor_run_binary(char **argv, char **env)
{
	g_signal.pid = fork();
	if (g_signal.pid == -1)
		return (-1);
	if (g_signal.pid == 0)
	{
		if (execve(argv[0], argv, env) == -1)
			print_error(argv[0], 0, 0);
		_exit(1);
	}
	else
		if (waitpid(g_signal.pid, &g_signal.status, 0) == -1)
			return (-1);
	if (g_signal.status > 0)
		g_signal.status /= 2;
	return (g_signal.status);
}

int	executor_run_builtin(char **argv, t_env *envs, char **env)
{
	(void)env;
	if (!ft_strcmp(argv[0], "exit"))
	{
		ft_free_envs(envs);
		ft_free();
		tcsetattr(0, TCSANOW, &g_signal.backup);
		exit(0);
	}
	if (!ft_strcmp(argv[0], "pwd"))
		return (builtin_pwd());
	if (!ft_strcmp(argv[0], "echo"))
		return (builtin_echo(argv));
	if (!ft_strcmp(argv[0], "cd"))
		return (builtin_cd(argv, envs));
	if (!ft_strcmp(argv[0], "unset"))
		return (builtin_unset(argv, envs));
	if (!ft_strcmp(argv[0], "export"))
		return (builtin_export(argv, envs));
	if (!ft_strcmp(argv[0], "env"))
		return (builtin_env(envs, 0));
	return (1);
}

int	executor_cmd(t_cmd *cmd, t_env *envs, char **env)
{
	if (!cmd->argv[0])
		return (0);
	if (ft_strchr(cmd->argv[0], '/'))
	{
		g_signal.status = executor_run_binary(cmd->argv, env);
		return (g_signal.status);
	}
	else
	{
		if (is_builtin(cmd))
		{
			g_signal.status = executor_run_builtin(cmd->argv, envs, env);
			return (g_signal.status);
		}
		cmd->argv[0] = scan_path(cmd->argv[0], envs);
		if (!file_exist(cmd->argv[0]))
		{
			print_error(cmd->argv[0], 0, "command not found");
			g_signal.status = 128;
			return (g_signal.status);
		}
		g_signal.status = executor_run_binary(cmd->argv, env);
		return (g_signal.status);
	}
	return (-1);
}

int	executor_exec(t_cmdtable *cmdtable, t_env *envs, char **env)
{
	t_cmdtable	*curtable;
	t_cmd		*curcmds;
	int			tmp[6];

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
				|| executor_cmd(curcmds, envs, env) == -1)
				return (-1);
			curcmds = curcmds->next;
		}
		if (executor_redir(tmp[2], 0) == -1 || executor_redir(tmp[3], 1) == -1)
			return (-1);
		curtable = curtable->next;
	}
	return (g_signal.status);
}

int	executor(t_cmdtable *table, t_env *envs, char **env)
{
	g_signal.status = executor_exec(table, envs, env);
	ft_free();
	return (g_signal.status);
}
