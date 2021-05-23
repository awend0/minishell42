#include "../includes/minishell.h"

t_signal g_signal = {0, 0, 0, 0};

void	termcaps_init(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	tgetent(0, "xterm-256color");
}

typedef struct	s_term
{
	char	*line;
	int		size;
}			t_term;

char	*get_termcaps(void)
{
	char	*str;
	int		ret;
	t_term	term;

	str = ft_calloc(101, sizeof(char));
	term.line = ft_calloc(2, sizeof(char));
	term.size = 0;
	while (ft_strcmp(str, "\n"))
	{
		ret = read(0, str, 100);
		if (!ft_strcmp(str, "\e[A"))
			write(0, "up", 2);
		else
		{
			write(1, str, ret);
			term.size++;
			term.line = charcat(term.line, *str);
		}
	}
	return (term.line);
}

int	main(int argc, char **argv, char **env)
{
	int				status;
	char			*line;
	t_cmdtable		*cmdtable;
	t_env			*envs;
	
	envs = env_split(env);
	termcaps_init();
	if (argc == 3 && !ft_strcmp(argv[1], "-c"))
		return(executor(parser(argv[2], envs), envs, env));
	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
	status = 0;
	while (1)
	{
		ft_puts(BOLDCYAN"paSHtet"BOLDYELLOW" » "RESET, 1);
		line = get_termcaps();
		// get_next_line(0, &line);
		cmdtable = parser(line, envs);
		executor(cmdtable, envs, env);
		printf("Status: %d\n", g_signal.status);
		free(line);
	}
	return (status);
}
