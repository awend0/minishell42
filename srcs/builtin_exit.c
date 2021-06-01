#include "../includes/minishell.h"

int	builtin_exit(char **argv)
{
	int		code;

	if (argv[2])
	{
		print_error("exit", 0, "too many arguments");
		return (1);
	}
	if (!argv[1])
		code = 0;
	else
		code = ft_atoi(argv[1]) % 256;
	ft_free(0);
	ft_free(1);
	exit(code);
}
