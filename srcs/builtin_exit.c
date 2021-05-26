#include "../includes/minishell.h"

void	builtin_exit(void)
{
	ft_free(0);
	ft_free(1);
	exit(0);
}
