#include "../includes/minishell.h"
#include <limits.h>

char	*pwd_getcurpath(void)
{
	char	*buf;
	char	*cwd;

	buf = ft_calloc_save(PATH_MAX);
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
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	return (0);
}
