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
		if (**line)
			(*line)++;
	}
	else
	{
		if (**line && **line == '\'')
			(*line)++;
	}
	if (**line && **line != ' ' && **line != '$' && **line != '\''
		&& **line != '"')
	{
		arg = ft_strjoin(arg, get_token(line, " |;><", '1', envs));
		table->last->argv[table->last->argc - 1] = arg;
		if (**line)
			(*line)++;
	}
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
		if (**line)
			(*line)++;
	}
	else
	{
		if (**line && **line == '"')
			(*line)++;
	}
	if (**line && **line != ' ' && **line != '$' && **line != '"'
		&& **line != '\'')
	{
		arg = ft_strjoin(arg, get_token(line, " |;><", '1', envs));
		table->last->argv[table->last->argc - 1] = arg;
		if (**line)
			(*line)++;
	}
}

void	add_pipe(t_cmdtable *table, char **line)
{
	t_cmd	*new;

	cmd_init(&new);
	table->last->next = new;
	table->last = table->last->next;
	(*line)++;
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
