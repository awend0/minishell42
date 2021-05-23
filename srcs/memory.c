#include "../includes/minishell.h"

void	ft_bzero(void *s, int n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
		*ptr++ = '\0';
}

void	*ft_calloc(int size)
{
	void	*ret;

	ret = malloc(size);
	ft_bzero(ret, size);
	return (ret);
}

void	*ft_calloc_save(int size)
{
	void	*ret;
	t_list	*new;
	t_list	*cur;

	ret = ft_calloc(size);
	new = malloc(sizeof(t_list));
	new->node = ret;
	new->next = 0;
	if (!g_signal.memory)
	{
		g_signal.memory = new;
	}
	else
	{
		cur = g_signal.memory;
		while (cur->next)
			cur=cur->next;
		cur->next = new;
	}
	return (ret);
}

void	ft_free(void)
{
	t_list	*cur;
	t_list	*prev;

	cur = g_signal.memory;
	while (cur)
	{
		prev = cur;
		cur = cur->next;
		free(prev->node);
		free(prev);
	}
	g_signal.memory = 0;
}

void	ft_free_envs(t_env *envs)
{
	t_env	*tmp;

	while (envs)
	{
		tmp = envs;
		envs = tmp->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}