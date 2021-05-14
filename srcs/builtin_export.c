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
	t_env	*prev;
	t_env	*next;

	prev = cur->prev;
	if (prev)
	{
		new->prev = prev;
		prev->next = new;
	}
	next = cur->next;
	if (next)
	{
		new->next = next;
		next->prev = new;
	}
}

void	export_insert(t_env *envs, t_env *new)
{
	t_env	*prev;

	prev = 0;
	while (envs)
	{
		if (!ft_strcmp(envs->name, new->name))
			export_replace(envs, new);
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
		tmp = strchr(*argv, '=');
		if (!tmp)
			return (0);
		if (**argv >= '0' && **argv <= '9')
		{
			ft_puts("export: '", 1);
			ft_puts(strndup(*argv, (tmp - *argv)), 1);
			ft_puts("': not a valid identifier\n", 1);
			return (1);
		}
		new = export_init(strndup(*argv, (tmp - *argv)), strdup(tmp + 1));
		export_insert(envs, new);
		argv++;
	}
	return (0);
}
