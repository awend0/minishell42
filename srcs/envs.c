#include "../includes/minishell.h"

t_env	*env_add(t_env *list, char *env, int secret)
{
	t_env	*new;
	t_env	*cur;
	char	*tmp;

	cur = list;
	while (cur && cur->next)
		cur = cur->next;
	new = ft_calloc_save2(sizeof(t_env));
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
	if (!get_env(ret, "OLDPWD"))
		ret = env_add(ret, "OLDPWD=.", 0);
	ret = env_add(ret, "?=0", 1);
	return (ret);
}

int	envs_len(t_env *envs)
{
	int		ret;

	ret = 0;
	while (envs)
	{
		envs = envs->next;
		ret++;
	}
	return (ret);
}

char	**get_envs(t_env *envs)
{
	char	**ret;
	char	**buf;
	int		len;

	len = envs_len(envs);
	ret = ft_calloc_save((len + 1) * sizeof(char *));
	buf = ret;
	while (len--)
	{
		*buf = ft_concat(envs->name, ft_concat("=", envs->value));
		envs = envs->next;
		buf++;
	}
	*buf = 0;
	return (ret);
}
