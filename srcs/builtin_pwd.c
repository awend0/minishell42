#include "../includes/minishell.h"
#include <limits.h>

char	*pwd_getcurpath(void)
{
	char	*buf;
	char	*cwd;

	buf = malloc(PATH_MAX);
	cwd = getcwd(buf, PATH_MAX);
	if (!cwd)
		return (0);
	return (cwd);
}

int	builtin_pwd(void)
{
	char	*cwd;

	cwd = pwd_getcurpath();
	if (!cwd)
		print_error("pwd", 0, 0);
	ft_puts(cwd, 1);
	ft_puts("\n", 1);
	return (0);
}
