#include "../includes/minishell.h"

int	executor_run_binary(char **argv, char **env)
{
	int		ret;

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
		if (waitpid(g_signal.pid, &ret, 0) == -1)
			return (-1);
	if (ret > 0)
		ret /= 2;
	return (ret);
}

int	executor_run_builtin(char **argv, t_env *envs, char **env)
{
	(void)env;
	if (!ft_strcmp(argv[0], "exit"))
	{
		ft_free_envs(envs);
		ft_free();
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

int	executor_cmd(t_cmd *cmd, t_env *envs, char **env, int *tmp)
{
	if (!cmd->argv[0])
		return (0);
	if (ft_strchr(cmd->argv[0], '/'))
	{
		tmp[6] = executor_run_binary(cmd->argv, env);
		return (0);
	}
	else
	{
		if (is_builtin(cmd))
		{
			tmp[6] = executor_run_builtin(cmd->argv, envs, env);
			return (0);
		}
		cmd->argv[0] = scan_path(cmd->argv[0], envs);
		if (!file_exist(cmd->argv[0]))
		{
			print_error(cmd->argv[0], 0, "command not found");
			tmp[6]= 128;
			return (0);
		}
		tmp[6] = executor_run_binary(cmd->argv, env);
		return (0);
	}
	return (-1);
}

int	executor_exec(t_cmdtable *cmdtable, t_env *envs, char **env)
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
			if (executor_redir(tmp[4], 0) == -1
				|| executor_run_and_redir(curcmds, curtable, tmp) == -1
				|| executor_redir(tmp[5], 1) == -1
				|| executor_cmd(curcmds, envs, env, tmp) == -1)
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
	int		ret;

	ret = executor_exec(table, envs, env);
	ft_free();
	if (!g_signal.status)
		g_signal.status = ret;
	return (0);
}
