#include "../includes/minishell.h"

char	*scan_path(char *binary, t_env *envs)
{
	DIR				*folder;
	struct dirent	*file;
	char			**dirs;
	t_env			*cur;
	char			*ret;

	cur = envs;
	while (cur && ft_strcmp(cur->name, "PATH"))
		cur = cur->next;
	if (!cur)
		return (binary);
	dirs = ft_split(cur->value, ':');
	while (*dirs)
	{
		folder = opendir(*dirs);
		if (!folder)
		{
			dirs++;
			continue ;
		}
		while (folder)
		{
			file = readdir(folder);
			if (!file)
				break ;
			if (!ft_strcmp(file->d_name, binary))
			{
				ret = ft_concat(*dirs, ft_concat("/", file->d_name));
				closedir(folder);
				return (ret);
			}
		}
		closedir(folder);
		dirs++;
	}
	return (binary);
}

int	file_exist(char *filename)
{
	struct stat	buf;

	return (stat(filename, &buf) == 0);
}

int	is_builtin(t_cmd *cmd)
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
	else
		ft_putstr_fd(strerror(errno), 1);
	ft_putstr_fd("\n", 1);
}

void	modify_env(t_env *envs, char *name, char *newvalue)
{
	while (envs && ft_strcmp(name, envs->name))
		envs = envs->next;
	if (!envs)
		return ;
	free(envs->value);
	envs->value = strdup(newvalue);
}