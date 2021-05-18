#include "../includes/minishell.h"

t_signal g_signal = {0, 0, 0, 0};

// void	get_termcaps(char **line)
// {
	
// }

int	main(int argc, char **argv, char **env)
{
	int				status;
	char			*line;
	t_cmdtable		*cmdtable;
	t_env			*envs;
	struct termios	term;

	envs = env_split(env);
	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	tgetent(0, "xterm-256color");
	if (argc == 3 && !ft_strcmp(argv[1], "-c"))
		return(executor(parser(argv[2], envs), envs, env));
	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
	status = 0;
	while (1)
	{
		ft_puts(BOLDCYAN"paSHtet"BOLDYELLOW" » "RESET, 1);
		get_next_line(0, &line);
		cmdtable = parser(line, envs);
		executor(cmdtable, envs, env);
		printf("Status: %d\n", g_signal.status);
		free(line);
	}
	return (status);
}
