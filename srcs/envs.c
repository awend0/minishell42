#include "../includes/minishell.h"

void	init_env(t_env **envs)
{
	(*envs) = calloc(1, sizeof(t_env) + 1);
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

	len = strlen(line);
	envs->name = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (line[i] != '=')
	{
		envs->name[i] = line[i];
		i++;
	}
	envs->name[i] = '\0';
	len = strlen(line++);
	envs->value = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (line[i])
	{
		envs->value[i] = line[i];
		i++;
	}
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
			envs = 0;
			init_env(&envs);
			envs = envs_split(*env, envs);
			buf = envs;
		}
		else
		{
			new = 0;
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
