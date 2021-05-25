#include "../includes/minishell.h"

void	get_arg(char **line, t_cmdtable *table, t_env *envs)
{
	char	*arg;

	arg = get_token(line, " |;><", '1', envs);
	if (!arg)
		return ;
	arg_init(table->last);
	table->last->argv[table->last->argc - 1] = arg;
}

void	get_single_quote(char **line, t_cmdtable *table, t_env *envs)
{
	char	*arg;

	(*line)++;
	arg = get_token(line, "'", '2', envs);
	if (arg)
	{
		arg_init(table->last);
		table->last->argv[table->last->argc - 1] = arg;
	}
	(*line)++;
}

void	get_double_quote(char **line, t_cmdtable *table, t_env *envs)
{
	char	*arg;

	(*line)++;
	arg = get_token(line, "\"", '3', envs);
	if (arg)
	{
		arg_init(table->last);
		table->last->argv[table->last->argc - 1] = arg;
	}
	(*line)++;
}

void	add_pipe(t_cmdtable *table, char **line)
{
	t_cmd	*new;

	cmd_init(&new);
	table->last->next = new;
	table->last = table->last->next;
	(*line)++;
}

void	add_new_cmdtable(t_cmdtable **table, char **line)
{
	t_cmdtable	*new;

	cmdtable_init(&new);
	(*table)->next = new;
	(*table) = (*table)->next;
	(*line)++;
}

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
		if (filename)
			close(open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU));
		table->output_file = filename;
	}
	else if (!ft_strcmp(type, "input"))
		table->input_file = filename;
	else if (!ft_strcmp(type, "append"))
	{
		if (filename)
			close(open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU));
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

t_cmdtable	*parser(char *line, t_env *envs)
{
	t_cmdtable	*table;
	t_cmdtable	*buf;

	cmdtable_init(&table);
	buf = table;
	while (*line)
	{
		if (*line && !ft_strchr(" |;><'\"", *line))
			get_arg(&line, table, envs);
		else if (*line && *line == '\'')
			get_single_quote(&line, table, envs);
		else if (*line && *line == '"')
			get_double_quote(&line, table, envs);
		else if (*line && *line == '|')
			add_pipe(table, &line);
		else if (*line && *line == ';')
			add_new_cmdtable(&table, &line);
		else if (*line && (*line == '>' || *line == '<'))
			add_redirection(&line, buf, envs);
		else
			line++;
	}
	return (buf);
}