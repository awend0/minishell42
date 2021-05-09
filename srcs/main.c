#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	int			status;
	char		*line;
	t_cmdtable	*cmdtable;
	t_env		*envs;

	(void)argc;
	(void)argv;
	envs = init_envs(env);
	test_init_envs(envs);
	status = 0;
	while (!status)
	{
		putstr("sh» ", 1);
		line = get_next_line(0, &line);
		cmdtable = parser(line, envs);
		free(line);
		status = executor(cmdtable, envs);
	}
	return (status);
}
