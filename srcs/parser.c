#include "../includes/minishell.h"

char	*find_env(char *env, t_env *envs)
{
	if (!env || !envs)
		return (0);
	while (envs)
	{
		if (!ft_strcmp(env, envs->name))
			return (envs->value);
		envs = envs->next;
	}
	return (0);
}

char	*get_token(char **line, char *spec, char perm, t_env *envs)
{
	char	*str;
	char	*buf;

	str = ft_calloc(1, sizeof(char));
	while (**line && !ft_strchr(spec, **line))
	{
		if (**line == '$' && ft_strchr("13", perm))
		{
			(*line)++;
			buf = get_token(line, "$ |;><'\"", '0', envs);
			str = ft_strjoin(str, find_env(buf, envs));
		}
		else if (**line == '"' && ft_strchr("1", perm))
		{
			(*line)++;
			buf = get_token(line, "\"", '3', envs);
			str = ft_strjoin(str, buf);
			(*line)++;
		}
		else if (**line == '\'' && ft_strchr("1", perm))
		{
			(*line)++;
			buf = get_token(line, "'", '2', envs);
			str = ft_strjoin(str, buf);
			(*line)++;
		}
		else
			str = charcat(str, *((*line)++));
	}
	if (!*str)
		return (0);
	return(str);
}

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
