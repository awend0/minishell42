#include "../includes/minishell.h"

char	*get_privious(t_hist **hist, t_term *term)
{
	tputs(restore_cursor, 1, ft_putchar_term);
	tputs(tigetstr("ed"), 1, ft_putchar_term);
	if (!(*hist)->cmd)
		return (0);
	else
	{
		if ((*hist)->prev)
		{
			(*hist) = (*hist)->prev;
			ft_putstr_fd((*hist)->cmd, 1);
			term->position = ft_strlen((*hist)->cmd);
			term->size = term->position;
		}
		return ((*hist)->cmd);
	}
}

char	*get_next(t_hist **hist, t_term *term)
{
	tputs(restore_cursor, 1, ft_putchar_term);
	tputs(tigetstr("ed"), 1, ft_putchar_term);
	if (!(*hist)->cmd)
		return (0);
	else
	{
		if ((*hist)->next)
		{
			(*hist) = (*hist)->next;
			ft_putstr_fd((*hist)->cmd, 1);
			term->position = ft_strlen((*hist)->cmd);
			term->size = term->position;
		}
		return ((*hist)->cmd);
	}
}

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

void	write_char(char *str, int ret, t_term *term)
{
	if (term->position == term->size)
	{
		ft_putstr_fd(str, 1);
		term->size++;
		term->position++;
		g_signal.line = charcat(g_signal.line, *str);
	}
	else
	{
		term->size += ret;
		tputs(tgetstr("im", 0), 1, ft_putchar_term);
		tputs(tgetstr("ic", 0), 1, ft_putchar_term);
		ft_putstr_fd(str, 1);
		tputs(tgetstr("ip", 0), 1, ft_putchar_term);
		tputs(tgetstr("ei", 0), 1, ft_putchar_term);
		g_signal.line = insert_char(g_signal.line, str, ret, term->position);
		term->position++;
	}
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
