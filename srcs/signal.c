#include "../includes/minishell.h"

void	ft_putnbr(int nb);

void	sig_int(int code)
{
	(void)code;
	if (g_signal.pid == 0)
	{
		ft_puts(BOLDCYAN"\npaSHtet"BOLDYELLOW" » "RESET, 1);
		g_signal.status = 1;
	}
	else
	{
		ft_puts(BOLDCYAN"\npaSHtet"BOLDYELLOW" » "RESET, 1);
		g_signal.status = 130;
	}
	g_signal.inter = 1;
}

void	sig_quit(int code)
{
	if(g_signal.pid != 0)
	{
		ft_puts("Quit: ", 1);
		ft_putnbr(code);
		g_signal.status = 131;
		g_signal.quit = 1;
	}
	else
		ft_puts("\b\b \b\b", 1);
}

void	ft_putchar(char c)
{
	if (write(1, &c, 1) == 0)
		return ;
}

void	ft_putnbr(int nb)
{
	if (nb < 10 && nb >= 0)
	{
		ft_putchar(nb + '0');
	}
	else if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		ft_putchar(nb % 10 + '0');
		if (nb < 0)
			ft_putchar('-');
	}
	else
	{
		ft_putchar('-');
		ft_putnbr(nb * -1);
	}
}
