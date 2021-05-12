#include "../includes/minishell.h"

int     ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != 0 && s2[i] != 0)
		i++;
	return (s1[i] - s2[i]);
}

char	*scan_path(char *binary, t_env *envs)
{
	DIR				*folder;
	struct dirent	*file;
	char			**dirs;
	char			*slash;
	t_env			*cur;

	cur = envs;
	slash = strdup("/");
	while (cur && ft_strcmp(cur->name, "PATH"))
		cur = cur->next;
	dirs = ft_split(cur->value, ':');
	while (*dirs)
	{
		folder = opendir(*dirs);
		while (1)
		{
			file = readdir(folder);
			if (!file)
				break;
			if (!ft_strcmp(file->d_name, binary))
				return (strcat(*dirs, strcat(slash, binary))); 
		}
		closedir(folder);
		dirs++;
	}
	return (binary);
}

int		file_exist(char *filename)
{
	struct stat	buf;

	return (stat(filename, &buf) == 0);
}
