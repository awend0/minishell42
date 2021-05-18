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

char	*get_env_token(char **line, char *str, t_env *envs)
{
	char	*buf;

	(*line)++;
	buf = get_token(line, ":*^$=#@!%\\().,$ |;><'\"", '0', envs);
	str = ft_strjoin(str, find_env(buf, envs));
	return (str);
}

char	*get_double_token(char **line, char *str, t_env *envs)
{
	char	*buf;

	(*line)++;
	buf = get_token(line, "\"", '3', envs);
	str = ft_strjoin(str, buf);
	(*line)++;
	return (str);
}

char	*get_single_token(char **line, char *str, t_env *envs)
{
	char	*buf;

	(*line)++;
	buf = get_token(line, "'", '2', envs);
	str = ft_strjoin(str, buf);
	(*line)++;
	return (str);
}

char	*get_token(char **line, char *spec, char perm, t_env *envs)
{
	char	*str;

	str = ft_calloc_save(1);
	while (**line && !ft_strchr(spec, **line))
	{
		if (**line == '$' && ft_strchr("13", perm))
			str = get_env_token(line, str, envs);
		else if (**line == '"' && ft_strchr("1", perm))
			str = get_double_token(line, str, envs);
		else if (**line == '\'' && ft_strchr("1", perm))
			str = get_single_token(line, str, envs);
		else
			str = charcat(str, *((*line)++));
	}
	if (!*str)
		return (0);
	return (str);
}
