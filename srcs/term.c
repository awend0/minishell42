#include "../includes/minishell.h"

typedef struct	s_term
{
	int		position;
	char	*line;
	int		size;
}			t_term;

void	termcaps_init(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	tgetent(0, "xterm-256color");
}

int	ft_putchar_term(int c)
{
	return (write(1, &c, 1));
}

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
			write(1, (*hist)->cmd, ft_strlen((*hist)->cmd));
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
			write(1, (*hist)->cmd, ft_strlen((*hist)->cmd));
			term->position = ft_strlen((*hist)->cmd);
			term->size = term->position;
		}
		return ((*hist)->cmd);
	}
}

void	term_init(t_term *term)
{
	term->position = 0;
	term->line = ft_calloc_save(2 * sizeof(char));
	term->size = 0;
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
		write(1, str, ret);
		term->size++;
		term->position++;
		term->line = charcat(term->line, *str);
	}
	else
	{
		term->size += ret;
		tputs(tgetstr("im", 0), 1, ft_putchar_term);
		tputs(tgetstr("ic", 0), 1, ft_putchar_term);
		write(1, str, ret);
		tputs(tgetstr("ip", 0), 1, ft_putchar_term);
		tputs(tgetstr("ei", 0), 1, ft_putchar_term);
		term->line = insert_char(term->line, str, ret, term->position);
		term->position++;
	}
}

void	cursor_to_left(t_term *term)
{
	if (term->position)
	{
		term->position--;
		tputs(cursor_left, 1, ft_putchar_term);
	}
}

void	cursor_to_right(t_term *term)
{
	if (term->position < term->size)
	{
		term->position++;
		tputs(cursor_right, 1, ft_putchar_term);
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
		len = ft_strlen(&term->line[term->position]);
		ft_memcpy(&term->line[term->position],
					&term->line[term->position + 1],
					len);
	}
}

char	*term_loop(t_hist *hist)
{
	char	str[1000];
	int		ret;
	t_term	term;

	term_init(&term);
	tputs(save_cursor, 1, ft_putchar_term);
	ret = read(0, str, 999);
	str[ret] = 0;
	while (ret && ft_strcmp(str, "\n") && ft_strcmp(str, "\4"))
	{
		if (!strcmp(str, "\e[A"))
			term.line = get_privious(&hist, &term);
		else if (!strcmp(str, "\e[B"))
			term.line = get_next(&hist, &term);
		else if (!strcmp(str, "\e[D"))
			cursor_to_left(&term);
		else if (!strcmp(str, "\e[C"))
			cursor_to_right(&term);
		else if (!strcmp(str, "\x7f") && !strcmp(str, "\177"))
			del_one(&term);
		else
			write_char(str, ret, &term);
		ret = read(0, str, 999);
		str[ret] = 0;
	}
	write(1, "\n", 1);
	return (term.line);
}
