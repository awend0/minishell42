#include "../includes/minishell.h"

char	*get_filename(char **line, t_env *envs)
{
	char	*filename;

	filename = 0;
	if (!(**line))
		return (0);
	while (ft_strchr(" \t", **line))
		(*line)++;
	filename = get_token(line, "<> ", '1', envs);
	return (filename);
}

char	*get_redirection_type(char **line)
{
	char	*type;

	type = 0;
	if (**line == '<')
		type = "input";
	else if (**line == '>')
		type = "output";
	(*line)++;
	if (**line == '>' && !ft_strcmp(type, "output"))
	{
		type = "append";
		(*line)++;
	}
	return (type);
}

char	**add_filename(char *filename, char **arr)
{
	int		len;

	if (!arr)
	{
		arr = ft_calloc_save(2 * sizeof(char *));
		arr[0] = filename;
	}
	else
	{
		len = ft_arrlen(arr);
		arr = array_append(arr, len);
		arr[len] = filename;
	}
	return (arr);
}

void	write_redirection(char *type, char *filename, t_cmdtable *table)
{
	if (!ft_strcmp(type, "output"))
	{
		if (table->output_file)
			close(open(table->output_file, O_CREAT | O_WRONLY | O_TRUNC,
					S_IRWXU));
		table->output_file = filename;
	}
	else if (!ft_strcmp(type, "input"))
		table->input_file = filename;
	else if (!ft_strcmp(type, "append"))
	{
		if (table->output_file)
			close(open(table->output_file, O_CREAT | O_WRONLY | O_TRUNC,
					S_IRWXU));
		table->output_file = filename;
		table->append = 1;
	}
}

void	add_redirection(char **line, t_cmdtable *table, t_env *envs)
{
	char	*filename;
	char	*type;

	type = get_redirection_type(line);
	filename = get_filename(line, envs);
	if (filename)
		write_redirection(type, filename, table);
}
