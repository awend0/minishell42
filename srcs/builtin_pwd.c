#include "../includes/minishell.h"

int		builtin_pwd(void)
{
	char	*cwd;

	cwd = malloc(_PC_PATH_MAX);
	if (!getcwd(cwd, _PC_PATH_MAX))
		print_error_and_exit("pwd: getcwd failed");
	ft_puts(cwd, 1);
}