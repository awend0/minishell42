#include "../includes/minishell.h"

char	*insert_char(char *line, char *str, int ret, int pos)
{
	char	*new;
	int		len;
	int		i;

	len = ft_strlen(line);
	new = ft_calloc_save(ret + len + 1);
	i = -1;
	while (++i < pos)
		new[i] = line[i];
	while (ret--)
		new[i++] = *str++;
	while (line[pos])
		new[i++] = line[pos++];
	return (new);
}

void	del_one(t_term *term)
{
	int		len;

	if (term->position)
	{
		tputs(cursor_left, 1, ft_putchar_term);
		tputs(delete_character, 1, ft_putchar_term);
		term->size--;
		term->position--;
		len = ft_strlen(&g_signal.line[term->position]);
		ft_memcpy(&g_signal.line[term->position],
			&g_signal.line[term->position + 1],
			len);
	}
}

void	del_front(t_term *term)
{
	int		len;

	if (term->position < term->size)
	{
		tputs(delete_character, 1, ft_putchar_term);
		term->size--;
		len = ft_strlen(&g_signal.line[term->position]);
		ft_memcpy(&g_signal.line[term->position],
			&g_signal.line[term->position + 1],
			len);
	}
}
