#include "../includes/minishell.h"

int     main(int argc, char **argv, char **env)
{
	int			status;
	char        *line;
	t_cmdtable	*cmdtable;

	(void)argc;
	(void)argv;
	while (!status)
	{
		putstr("sh> ", 1);
		line = get_next_line(1, &line);
		cmdtable = parser(line);
		free(line);
		status = executor(cmdtable, env);
	}
	return (status);
}