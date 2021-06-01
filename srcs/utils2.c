#include "../includes/minishell.h"

int	file_exist(char *filename)
{
	struct stat	buf;

	return (stat(filename, &buf) == 0);
}

int	is_builtin(t_cmd *cmd)
{
	if (!ft_strcmp(ft_tolower(cmd->argv[0]), "cd")
		|| !ft_strcmp(cmd->argv[0], "unset")
		|| !ft_strcmp(cmd->argv[0], "export")
		|| !ft_strcmp(ft_tolower(cmd->argv[0]), "pwd")
		|| !ft_strcmp(ft_tolower(cmd->argv[0]), "echo")
		|| !ft_strcmp(ft_tolower(cmd->argv[0]), "env")
		|| !ft_strcmp(cmd->argv[0], "exit"))
		return (1);
	return (0);
}

char	*get_env(t_env *envs, char *name)
{
	while (envs && ft_strcmp(envs->name, name))
		envs = envs->next;
	if (!envs || ft_strcmp(envs->name, name))
		return (0);
	return (ft_strdup(envs->value, 1));
}

void	print_error(char *bin, char *val, char *err)
{
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(bin, 1);
	ft_putstr_fd(": ", 1);
	if (err)
	{
		if (val)
		{
			ft_putstr_fd("`", 1);
			ft_putstr_fd(val, 1);
			ft_putstr_fd("': ", 1);
		}
		ft_putstr_fd(err, 1);
	}
	if (!err && val)
	{
		ft_putstr_fd(val, 1);
		ft_putstr_fd(": ", 1);
	}
	if (!err)
		ft_putstr_fd(strerror(errno), 1);
	ft_putstr_fd("\n", 1);
}

void	modify_env(t_env *envs, char *name, char *newvalue)
{
	while (envs && ft_strcmp(name, envs->name))
		envs = envs->next;
	if (!envs)
		return ;
	if (newvalue)
		envs->value = ft_strdup(newvalue, 0);
	else
		envs->value = 0;
}
