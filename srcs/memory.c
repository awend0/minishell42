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

void	*ft_calloc_save2(int size)
{
	void	*ret;
	t_list	*new;
	t_list	*cur;

	ret = ft_calloc(size);
	new = ft_calloc(sizeof(t_list));
	new->node = ret;
	new->next = 0;
	if (!g_signal.memory2)
	{
		g_signal.memory2 = new;
	}
	else
	{
		cur = g_signal.memory2;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
	return (ret);
}

void	*ft_calloc_save(int size)
{
	void	*ret;
	t_list	*new;
	t_list	*cur;

	ret = ft_calloc(size);
	new = ft_calloc(sizeof(t_list));
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
			cur = cur->next;
		cur->next = new;
	}
	return (ret);
}

void	ft_free(int memory)
{
	t_list	*cur;
	t_list	*prev;

	if (memory == 0)
		cur = g_signal.memory;
	else
		cur = g_signal.memory2;
	while (cur)
	{
		prev = cur;
		cur = cur->next;
		free(prev->node);
		free(prev);
	}
	if (memory == 0)
		g_signal.memory = 0;
}
