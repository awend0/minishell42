#include "../includes/minishell.h"
#include <limits.h>

int	builtin_pwd(void)
{
	char	*buf;
	char	*cwd;

	buf = malloc(PATH_MAX);
	cwd = getcwd(buf, PATH_MAX);
	if (!cwd)
		print_error_and_exit(0);
	ft_puts(cwd, 1);
	ft_puts("\n", 1);
	return (0);
}
