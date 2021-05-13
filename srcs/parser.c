#include "../includes/minishell.h"

void	get_arg(char **line, t_cmdtable *buf, t_env *envs)
{
	char	*arg;

	arg = get_token(line, " |;><", '1', envs);
	if (!arg)
		return ;
	arg_init(buf);
	buf->cmds->argv[buf->cmds->argc - 1] = arg;
}

void	get_single_quote(char **line, t_cmdtable *buf, t_env *envs)
{
	char	*arg;

	(*line)++;
	arg = get_token(line, "'", '2', envs);
	if (arg)
	{
		arg_init(buf);
		buf->cmds->argv[buf->cmds->argc - 1] = arg;
	}
	(*line)++;
}

void	get_double_quote(char **line, t_cmdtable *buf, t_env *envs)
{
	char	*arg;

	(*line)++;
	arg = get_token(line, "\"", '3', envs);
	if (arg)
	{
		arg_init(buf);
		buf->cmds->argv[buf->cmds->argc - 1] = arg;
	}
	(*line)++;
}

void	add_pipe(t_cmdtable *buf, char **line)
{
	t_cmd	*new;

	new = cmd_init();
	buf->cmds->next = new;
	buf->cmds = buf->cmds->next;
	(*line)++;
}

void	add_new_cmdtable(t_cmdtable **buf, char **line)
{
	t_cmdtable	*new;

	cmdtable_init(&new);
	(*buf)->next = new;
	(*buf) = (*buf)->next;
	(*line)++;
}

t_cmdtable	*parser(char *line, t_env *envs)
{
	t_cmdtable	*table;
	t_cmdtable	*buf;
	t_cmd		*cmd_buf;

	cmdtable_init(&table);
	buf = table;
	cmd_buf = table->cmds;
	(void)envs;
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
		// else if (*line && *line == '>' || *line == '<')
		// 	add_redirection(&line, buf);
		else
			line++;
	}
	buf->cmds = cmd_buf;
	return (buf);
}
