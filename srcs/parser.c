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

t_cmdtable	*parser(char *line, t_env *envs)
{
	t_cmdtable	*table;
	t_cmdtable	*buf;

	cmdtable_init(&table);
	buf = table;
	(void)envs;
	while (*line)
	{
		if (*line && !ft_strchr(" |;><'\"", *line))
			get_arg(&line, buf, envs);
		else if (*line && *line == '\'')
			get_single_quote(&line, buf, envs);
		else if (*line && *line == '"')
			get_double_quote(&line, buf, envs);     
		// else if (*line && *line == '|')
		// 	add_pipe(&buf);
		// else if (*line && *line == ';')
		// 	add_new_cmd(&buf);
		// else if (*line && *line == '>' || *line == '<')
		// 	add_redirection(&line, buf);
		else
			line++;
	}
	return (table);
}
