#include "../includes/minishell.h"

char	**arr_copy(char **dest, char **src)
{
	char	**buf;

	buf = dest;
	while (*src)
		*dest++ = ft_strdup(*src++);
	return (buf);
}

void	arg_init(t_cmdtable *buf)
{
	int		len;
	char	**arr;
	char	**arr_buf;

	buf->cmds->argc++;
	len = ft_arrlen(buf->cmds->argv);
	arr = ft_calloc(len + 2, sizeof(char *));
	arr = arr_copy(arr, buf->cmds->argv);
	arr_buf = buf->cmds->argv;
	buf->cmds->argv = arr;
	free_arr(arr_buf);
}

t_cmd	*cmd_init(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	cmd->next = 0;
	cmd->argc = 0;
	cmd->argv = ft_calloc(2, sizeof(char *));
	return (cmd);
}

void	cmdtable_init(t_cmdtable **table)
{
	*table = ft_calloc(1, sizeof(t_cmdtable));
	(*table)->cmds = cmd_init();
	(*table)->input_file = 0;
	(*table)->output_file = 0;
	(*table)->next = 0;
}

void	get_arg(char **line, t_cmdtable *buf)
{
	int		len;
	int		i;
	char	*str;

	arg_init(buf);
	len = 0;
	while (((*line)[len]) && !isspecial((*line)[len]))
		len++;
	str = ft_calloc(len + 1, sizeof(char));
	i = 0;
	while (i < len)
		str[i++] = *((*line)++);
	buf->cmds->argv[buf->cmds->argc - 1] = str;
}

void	get_single_quote(char **line, t_cmdtable *buf, t_env *envs)
{
	int		len;
	int		i;
	char	*str;

	(*line)++;
	arg_init(buf);
	len = 0;
	while ((*line)[len] != 39)
		len++;
	str = ft_calloc(len + 1, sizeof(char));
	i = 0;
	while (i < len)
		str[i++] = *((*line)++);
	buf->cmds->argv[buf->cmds->argc - 1] = str;
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
		if (*line && !isspecial(*line))
			get_arg(&line, buf);
		else if (*line && *line == 39)
			get_single_quote(&line, buf, envs);
		// else if (*line && *line == '"')
		// 	get_double_quote(&line, buf, envs);
		// else if (*line && *line == '$')
		// 	get_env_arg(&line, buf, envs);
		// else if (*line && *line == '|')
		// 	add_pipe(&buf);
		// else if (*line && *line == ';')
		// 	add_new_cmd(&buf);
		// else if (*line && *line == '>' || *line == '<')
		// 	add_redirection(&line, buf);
		line++;
	}
	return (table);
}
