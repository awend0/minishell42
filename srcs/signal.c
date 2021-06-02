#include "../includes/minishell.h"

void	sig_int(int code)
{
	(void)code;
	g_signal.inter = 1;
	if (g_signal.pid != 0)
	{
		ft_putstr_fd("\n", 1);
		g_signal.status = 130;
	}
	else
	{
		g_signal.status = 1;
		g_signal.line[0] = 0;
		ft_putstr_fd("\n", 1);
		print_prompt();
		term_init();
		tputs(save_cursor, 1, ft_putchar_term);
	}
}

void	sig_quit(int code)
{
	if (g_signal.pid != 0)
	{
		ft_putstr_fd("Quit: ", 1);
		ft_putnbr_fd(code, 1);
		ft_putstr_fd("\n", 1);
		g_signal.status = 131;
	}
	g_signal.quit = 1;
}
