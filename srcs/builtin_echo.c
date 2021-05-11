#include "../includes/minishell.h"

int     builtin_echo(char **argv)
{
	int		n_flag;

	if (argv[1] && !ft_strcmp(argv[1], "-n"))
	{
		n_flag = 1;
		argv++;
	}
	else
		n_flag = 0;
	if (!argv[1] && !n_flag)
	{
		write(1, "\n", 1);
		return (0);
	}
	argv++;
	while (*argv)
	{
		ft_puts(*argv, 1);
		argv++;
		if (!(*argv) && !n_flag)
			ft_puts("\n", 1);
		if (*argv)
			ft_puts(" ", 1);
	}
	return (1);
}