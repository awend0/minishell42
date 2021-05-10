#include "../includes/minishell.h"

void	init_env(t_env **envs)
{
	(*envs) = malloc(sizeof(t_env));
	if (!(*envs))
		return ;
	(*envs)->prev = 0;
	(*envs)->next = 0;
}

int	how_long_are_you(char *str)
{
	int		len;

	len = 0;
	while (*str && *str != '=')
	{
		str++;
		len++;
	}
	return (len);
}

t_env	*envs_split(char *line, t_env *envs)
{
	int		len;
	int		i;

	len = how_long_are_you(line);
	envs->name = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (*line != '=')
		envs->name[i++] = *(line++);
	envs->name[i] = '\0';
	len = how_long_are_you(++line);
	envs->value = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (*line)
		envs->value[i++] = *line++;
	envs->value[i] = '\0';
	return (envs);
}

t_env	*init_envs(char **env)
{
	t_env	*envs;
	t_env	*buf;
	t_env	*new;

	envs = 0;
	while (*env)
	{
		if (!envs)
		{
			init_env(&envs);
			envs = envs_split(*env, envs);
			buf = envs;
		}
		else
		{
			init_env(&new);
			new->prev = envs;
			envs->next = new;
			new = envs_split(*env, new);
			envs = new;
		}
		env++;
	}
	return (buf);
}

char	**get_env_as_string(t_env *envs)
{
	char	**env;
	int		len;
	int		i;
	int		j;

	len = get_envs_len(envs);
	env = malloc(sizeof(char *) * (len + 1));
	env[len] = 0;
	i = 0;
	while (envs)
	{
		env[i] = malloc(sizeof(char) * (ft_strlen(envs->name)
					+ ft_strlen(envs->value) + 2));
		j = 0;
		while (*(envs->name))
			env[i][j++] = *(envs->name++);
		env[i][j++] = '=';
		while (*(envs->value))
			env[i][j++] = *(envs->value++);
		env[i++][j] = '\0';
		envs = envs->next;
	}
	return (env);
}
