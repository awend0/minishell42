#include "../includes/minishell.h"

t_env	*env_add(t_env *list, char *env, int secret)
{
	t_env	*new;
	t_env	*cur;
	char	*tmp;

	cur = list;
	while (cur && cur->next)
		cur = cur->next;
	new = ft_calloc(sizeof(t_env));
	tmp = ft_strchr(env, '=');
	new->name = ft_strndup(env, (tmp - env), 0);
	new->value = ft_strdup(tmp + 1, 0);
	new->secret = secret;
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
		ret = env_add(ret, *env, 0);
		env++;
	}
	ret = env_add(ret, "?=0", 1);
	return (ret);
}

char	**get_env_as_string(t_env *envs)
{
	char	**env;
	int		len;
	int		i;
	int		j;

	len = get_envs_len(envs);
	env = ft_calloc_save((len + 1) * sizeof(char *));
	i = 0;
	while (envs)
	{
		env[i] = ft_calloc_save(ft_strlen(envs->name)
				+ ft_strlen(envs->value) + 2);
		j = 0;
		while (*(envs->name))
			env[i][j++] = *(envs->name++);
		env[i][j++] = '=';
		while (*(envs->value))
			env[i][j++] = *(envs->value++);
		envs = envs->next;
	}
	return (env);
}
