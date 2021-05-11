#include "../includes/minishell.h"

t_env	*env_add(t_env *list, char *env)
{
	t_env	*new;
	t_env	*cur;
	char	*tmp;

	cur = list;
	while (cur && cur->next)
		cur = cur->next;
	new = malloc(sizeof(t_env));
	tmp = strchr(env, '=');
	new->name = strndup(env, (tmp - env));
	new->value = (tmp + 1);
	new->next = 0;
	if (cur)
	{
		cur->next = new;
		new->prev = cur;
	}
	else
	{
		new->prev = 0;
		return (new);
	}
	return (list);
}

t_env	*env_split(char **env)
{
	t_env	*ret;

	ret = 0;
	while (*env)
	{
		ret = env_add(ret, *env);
		env++;
	}
	return (ret);
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