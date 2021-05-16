#include "../includes/minishell.h"

t_env	*export_init(char *name, char *value)
{
	t_env	*ret;

	ret = malloc(sizeof(t_env));
	ret->name = name;
	ret->value = value;
	ret->next = 0;
	ret->prev = 0;
	return (ret);
}

void	export_replace(t_env *cur, t_env *new)
{
	if (!cur || !new)
		return ;
	if (cur->prev)
		cur->prev->next = new;
	if (cur->next)
		cur->next->prev = new;
	free(cur->name);
	free(cur->value);
	free(cur);
}

void	export_insert(t_env *envs, t_env *new)
{
	t_env	*prev;

	prev = 0;
	while (envs)
	{
		if (!ft_strcmp(envs->name, new->name))
		{
			export_replace(envs, new);
			return ;
		}
		prev = envs;
		envs = envs->next;
	}
	prev->next = new;
	new->prev = prev;
}

int	builtin_export(char **argv, t_env *envs)
{
	char	*tmp;
	t_env	*new;

	if (!argv[1])
		return (builtin_env(envs, 1));
	argv++;
	while (*argv)
	{
		if (check_env_name(*argv))
		{
			print_error("export", *argv, "not a valid indentifier");
			return (1);
		}
		tmp = strchr(*argv, '=');
		new = export_init(strndup(*argv, (tmp - *argv)), strdup(tmp + 1));
		export_insert(envs, new);
		argv++;
	}
	return (0);
}
