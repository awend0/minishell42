#include "../includes/minishell.h"

int	executor_exec_binary(char **argv, char **env)
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
		ret = 1;
	return (ret);
}

int	executor_exec_builtin(char **argv, t_env *envs, char **env)
{
	(void)env;
	if (!ft_strcmp(argv[0], "exit"))
		return (builtin_exit(argv));
	if (!ft_strcmp(ft_tolower(argv[0]), "pwd"))
		return (builtin_pwd());
	if (!ft_strcmp(ft_tolower(argv[0]), "echo"))
		return (builtin_echo(argv));
	if (!ft_strcmp(ft_tolower(argv[0]), "cd"))
		return (builtin_cd(argv, envs));
	if (!ft_strcmp(argv[0], "unset"))
		return (builtin_unset(argv, envs));
	if (!ft_strcmp(argv[0], "export"))
		return (builtin_export(argv, envs));
	if (!ft_strcmp(ft_tolower(argv[0]), "env"))
		return (builtin_env(envs, 0));
	return (1);
}

int	executor_run_file(t_cmd *cmd, t_env *envs, char **env, int *tmp)
{
	(void)envs;
	if (!file_exist(cmd->argv[0]))
	{
		print_error(cmd->argv[0], 0, "No such file or directory");
		tmp[6] = 127;
		return (0);
	}
	else if (!is_regular_file(cmd->argv[0]))
	{
		print_error(cmd->argv[0], 0, "is a directory");
		tmp[6] = 126;
		return (0);
	}
	else
		tmp[6] = executor_exec_binary(cmd->argv, env);
	return (0);
}

int	executor_run_command(t_cmd *cmd, t_env *envs, char **env, int *tmp)
{
	char	*dup;

	if (is_builtin(cmd))
	{
		tmp[6] = executor_exec_builtin(cmd->argv, envs, env);
		return (0);
	}
	dup = ft_strdup(cmd->argv[0], 1);
	cmd->argv[0] = scan_path(cmd->argv[0], envs);
	if (!cmd->argv[0])
	{
		if (!get_env(envs, "PATH"))
			print_error(dup, 0, "No such file or directory");
		else
			print_error(dup, 0, "command not found");
		tmp[6] = 127;
		return (0);
	}
	tmp[6] = executor_exec_binary(cmd->argv, env);
	return (0);
}

int	executor_cmd(t_cmd *cmd, t_env *envs, char **env, int *tmp)
{
	if (!cmd->argv[0])
		return (0);
	if (ft_strchr(cmd->argv[0], '/'))
		return (executor_run_file(cmd, envs, env, tmp));
	else
		return (executor_run_command(cmd, envs, env, tmp));
	return (-1);
}
