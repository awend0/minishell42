#include "../includes/minishell.h"

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

void	check_command(char *str, t_hist **hist, t_term *term, int ret)
{
	if (!ft_strcmp(str, "\e[A"))
		g_signal.line = get_privious(hist, term);
	else if (!ft_strcmp(str, "\e[B"))
		g_signal.line = get_next(hist, term);
	else if (!ft_strcmp(str, "\e[D"))
		cursor_to_left(term);
	else if (!ft_strcmp(str, "\e[C"))
		cursor_to_right(term);
	else if (!ft_strcmp(str, "\x7f") && !ft_strcmp(str, "\177"))
		del_one(term);
	else
		write_char(str, ret, term);
}

void	term_loop(t_hist *hist)
{
	char	str[10];
	int		ret;
	t_term	term;

	term_init(&term);
	tputs(save_cursor, 1, ft_putchar_term);
	ret = read(0, str, 9);
	str[ret] = 0;
	while (ret && ft_strcmp(str, "\n") && ft_strcmp(str, "\4"))
	{
		tcsetattr(0, TCSANOW, g_signal.cur_term);
		check_command(str, &hist, &term, ret);
		ret = read(0, str, 9);
		str[ret] = 0;
	}
	if (!ft_strcmp(str, "\4"))
	{
		g_signal.line = ft_strdup("exit", 1);
		ft_putstr_fd("exit\n", 1);
		return ;
	}
	ft_putstr_fd("\n", 1);
}
