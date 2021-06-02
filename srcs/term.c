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
	else if (!ft_strcmp(str, "\e[3~"))
		del_front(term);
	else if (!ft_strcmp(str, "\4") || !ft_strcmp(str, "\b"))
		return ;
	else if (ft_strlen(str) > 1)
		return ;
	else
		write_char(str, ret, term);
}

void	ctrl_d_l(char *str)
{
	if (!ft_strcmp(g_signal.line, "exit"))
	{
		tputs("\nexit", 1, ft_putchar_term);
	}
	else if (!ft_strcmp(str, "\4"))
	{
		g_signal.line = ft_strdup("exit", 1);
		ft_putstr_fd("exit", 1);
	}
	else if (!ft_strcmp(str, "\f"))
		g_signal.line = ft_strdup("clear", 1);
}

void	term_loop(t_hist *hist, t_env *envs)
{
	char	str[1000];
	int		ret;

	term_init();
	tputs(save_cursor, 1, ft_putchar_term);
	ret = read(0, str, 999);
	str[ret] = 0;
	while (ft_strcmp(str, "\f") && ft_strcmp(str, "\4") && ft_strcmp(str, "\n"))
	{
		while (ft_strcmp(str, "\n"))
		{
			if (g_signal.inter || g_signal.quit)
				modify_env(envs, "?", ft_itoa(g_signal.status));
			tcsetattr(0, TCSANOW, g_signal.cur_term);
			check_command(str, &hist, g_signal.term, ret);
			ret = read(0, str, 999);
			str[ret] = 0;
			if ((!ft_strcmp(str, "\4") && !ft_strlen(g_signal.line))
				|| !ft_strcmp(str, "\f"))
				break ;
		}
	}
	ctrl_d_l(str);
	ft_putstr_fd("\n", 1);
}
