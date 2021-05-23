#include "../includes/minishell.h"

void	ft_putnbr(int nb);

void	sig_int(int code)
{
	(void)code;
	if (g_signal.pid != 0)
		g_signal.status = 130;
	else
		g_signal.status = 131;
	ft_putstr_fd(BOLDCYAN"\npaSHtet"BOLDYELLOW" » "RESET, 1);
	g_signal.inter = 1;
}

void	sig_quit(int code)
{
	(void)code;
	if (g_signal.pid != 0)
		ft_putstr_fd("Quit\n", 1);
}