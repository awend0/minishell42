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

char	*term_loop(void)
{
	char	str[1000];
	int		ret;
	t_term	term;

	term.position = 0;
	term.line = ft_calloc_save(2 * sizeof(char));
	term.size = 0;
	tputs(save_cursor, 1, ft_putchar_term);
	ret = read(0, str, 999);
	str[ret] = 0;
	while (ret && ft_strcmp(str, "\n") && ft_strcmp(str, "\4"))
	{
		if (!strcmp(str, "\e[A"))
		{
			tputs(restore_cursor, 1, ft_putchar_term);
			tputs(tigetstr("ed"), 1, ft_putchar_term);
			write(1, "previous", 8);
		}
		else if (!strcmp(str, "\e[B"))
		{
			tputs(restore_cursor, 1, ft_putchar_term);
			tputs(tigetstr("ed"), 1, ft_putchar_term);
			write(1, "next", 4);
		}
		else if (!strcmp(str, "\x7f") && !strcmp(str, "\177"))
		{
			tputs(cursor_left, 1, ft_putchar_term);
			tputs(tigetstr("ed"), 1, ft_putchar_term);
		}
		else
		{
			write(1, str, ret);
			term.size++;
			term.line = charcat(term.line, *str);
		}
		ret = read(0, str, 999);
		str[ret] = 0;
	}
	write(1, "\n", 1);
	return (term.line);
}
