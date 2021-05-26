#include "../includes/minishell.h"

int	ft_atoi(const char *str)
{
	long			res;
	long			sign;
	unsigned int	i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return ((int)(res * sign));
}

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
	tcsetattr(0, TCSANOW, g_signal.backup_term);
	ft_free(0);
	ft_free(1);
	exit(code);
}
