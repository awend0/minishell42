#include "../includes/minishell.h"

t_env	*export_init(char *name, char *value, t_env *prev)
{
	t_env	*new;

	new = ft_calloc_save2(sizeof(t_env));
	new->next = 0;
	new->prev = prev;
	new->secret = 0;
	new->value = ft_strdup(value, 0);
	new->name = ft_strdup(name, 0);
	return (new);
}

int	export_insert(char *name, char *value, t_env *envs)
{
	t_env	*prev;

	prev = 0;
	if (check_env_name(name))
	{
		print_error("export", name, "not a valid identifier");
		return (1);
	}
	while (envs && ft_strcmp(name, envs->name))
	{
		prev = envs;
		envs = envs->next;
	}
	if (envs && !ft_strcmp(envs->name, name))
	{
		envs->value = ft_strdup(value, 0);
		return (0);
	}
	if (prev)
		prev->next = export_init(name, value, prev);
	else
		envs = export_init(name, value, prev);
	return (0);
}

int	export_iterate(char **argv, t_env *envs)
{
	int		ret;
	char	*tmp;

	ret = 0;
	while (*argv)
	{
		tmp = ft_strchr(*argv, '=');
		if (!tmp)
		{
			if (check_env_name(*argv))
			{
				print_error("export", *argv, "not a valid identifier");
				ret = 1;
			}
			argv++;
			continue ;
		}
		if (export_insert(ft_strndup(*argv, (tmp - *argv), 1),
				ft_strdup(tmp + 1, 1), envs))
			ret = 1;
		argv++;
	}
	return (ret);
}

int	builtin_export(char **argv, t_env *envs)
{
	if (!argv[1])
		return (builtin_env(envs, 1));
	argv++;
	return (export_iterate(argv, envs));
}
