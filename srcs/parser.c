#include "../includes/minishell.h"

void	arg_init(t_cmdtable *buf)
{
	int		len;

	buf->cmds->argc++;
	if (!buf->cmds->argv)
		buf->cmds->argv = malloc(sizeof(char *));
}

t_cmd	*cmd_init(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->next = 0;
	cmd->argc = 0;
	cmd->argv = malloc(sizeof(char *));
	cmd->argv[0] = 0;
	*cmd->argv = 0;
	return (cmd);
}

void	cmdtable_init(t_cmdtable **table)
{
	*table = malloc(sizeof(t_cmdtable));
	(*table)->cmds = cmd_init();
	(*table)->input_file = 0;
	(*table)->output_file = 0;
	(*table)->next = 0;
}

void	get_arg(char **line, t_cmdtable *buf)
{
	arg_init(buf);
	while (**line && ft_ischar(**line))
	{

		(*line)++;
	}
}

t_cmdtable	*parser(char *line, t_env *envs)
{
	t_cmdtable	*table;
	t_cmdtable	*buf;
	
	cmdtable_init(&table);
	buf = table;
	while (*line)
	{
		if (*line && ft_ischar(*line))
			get_arg(&line, buf);
		else if (*line && *line == 39)
			get_single_quote(&line, buf, envs);
		else if (*line && *line == '"')
			get_double_quote(&line, buf, envs);
		else if (*line && *line == '$')
			get_env_arg(&line, buf, envs);
		else if (*line && *line == '|')
			add_pipe(&buf);
		else if (*line && *line == ';')
			add_new_cmd(&buf);
		else if (*line && *line == '>' || *line == '<')
			add_redirection(&line, buf);
		line++;
	}
	return (table);
}
