#include "../includes/minishell.h"

int	is_regular_file(char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}

int	executor_iterate(t_cmdtable *cmdtable, t_env *envs, char **env)
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
				|| executor_fork(curcmds, curtable, tmp) == -1
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

	ret = executor_iterate(table, envs, env);
	ft_free(0);
	if (!g_signal.quit && !g_signal.inter)
	{
		g_signal.status = ret;
	}
	return (0);
}
