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
		printf("i'm alive1\n");
		if (!envs)
		{
			printf("i'm alive2\n");
			envs = 0;
			printf("i'm alive3\n");
			init_env(&envs);
			printf("i'm alive4\n");
			envs = envs_split(*env, envs);
			buf = envs;
			printf("i'm alive5\n");
		}
		else
		{
			new = 0;
			printf("cur env: [%s]\n", *env);
			printf("i'm alive6\n");
			init_env(&new);
			printf("i'm alive7\n");
			new->prev = envs;
			envs->next = new;
			printf("i'm alive8\n");
			new = envs_split(*env, new);
			envs = new;
		}
		env++;
	}
	printf("i'm alive9\n");
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
