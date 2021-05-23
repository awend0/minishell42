#include "../includes/minishell.h"

int	builtin_echo(char **argv)
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
		ft_putstr_fd("\n", 1);
		return (0);
	}
	argv++;
	while (*argv)
	{
		ft_putstr_fd(*argv, 1);
		argv++;
		if (!(*argv) && !n_flag)
			ft_putstr_fd("\n", 1);
		if (*argv)
			ft_putstr_fd(" ", 1);
	}
	return (0);
}
