#include "../includes/minishell.h"

int	ft_putchar_term(int c)
{
	return (write(1, &c, 1));
}

char	*scan_iterate_files(char *foldername, char *binary, DIR *folder)
{
	char			*ret;
	struct dirent	*file;

	while (folder)
	{
		file = readdir(folder);
		if (!file)
			break ;
		if (!ft_strcmp(file->d_name, binary))
		{
			ret = ft_concat(foldername, ft_concat("/", file->d_name));
			closedir(folder);
			return (ret);
		}
	}
	return (0);
}

char	*scan_iterate_folders(char *binary, char **dirs)
{
	DIR		*folder;
	char	*ret;

	while (*dirs)
	{
		folder = opendir(*dirs);
		if (!folder)
		{
			dirs++;
			continue ;
		}
		ret = scan_iterate_files(*dirs, binary, folder);
		if (ret)
			return (ret);
		closedir(folder);
		dirs++;
	}
	return (0);
}

char	*scan_path(char *binary, t_env *envs)
{
	char			**dirs;
	t_env			*cur;

	cur = envs;
	while (cur && ft_strcmp(cur->name, "PATH"))
		cur = cur->next;
	if (!cur)
		return (0);
	dirs = ft_split(cur->value, ':');
	return (scan_iterate_folders(binary, dirs));
}

int	check_env_name(char *str)
{
	if ((*str < 65 || *str > 90)
		&& (*str < 97 || *str > 122)
		&& *str != '_')
		return (1);
	str++;
	while (*str && *str != '=')
	{
		if ((*str < 65 || *str > 90)
			&& (*str < 97 || *str > 122)
			&& (*str < 48 || *str > 57)
			&& *str != '_')
			return (1);
		str++;
	}
	return (0);
}
