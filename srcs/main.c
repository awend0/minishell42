#include "../includes/minishell.h"

t_signal g_signal = {0, 0, 0, 0, 0};

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_cmdtable	*cmdtable;
	t_env		*envs;

	envs = env_split(env);
	termcaps_init();
	if (argc == 3 && !ft_strcmp(argv[1], "-c"))
		return(executor(parser(argv[2], envs), envs, env));
	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
	while (1)
	{
		ft_putstr_fd(BOLDCYAN"paSHtet"BOLDYELLOW" » "RESET, 1);
		line = term_loop();
		cmdtable = parser(line, envs);
		modify_env(envs, "?", ft_itoa(executor(cmdtable, envs, env)));
	}
	ft_free();
	ft_free_envs(envs);
	return (0);
}
