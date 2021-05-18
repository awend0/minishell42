#include "../includes/minishell.h"

t_signal g_signal = {0, 0, 0, 0};

void	termcaps_init(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &term);
	tgetent(0, "xterm-256color");
}

typedef struct	s_term
{
	char	*line;
	int		size;
}			t_term;

int	ft_putchar_int(int c)
{
	return (write(1, &c, 1));
}

char	*get_termcaps(void)
{
	char	str[101];
	int		ret;
	t_term	term;

	term.line = ft_calloc(2, sizeof(char));
	term.size = 0;
	while (strcmp(str, "\4"))
	{
		tputs(save_cursor, 1, ft_putchar_int);
		do{
			ret = read(0, str, 100);
			if (!strcmp(str, "\e[A"))
			{
				tputs(restore_cursor, 1, ft_putchar_int);
				tputs(tigetstr("ed"), 1, ft_putchar_int);
				write(1, "up", 2);
			}
			else
			{
				write(1, str, ret);
				term.size++;
				term.line = charcat(term.line, *str);
			}
		} while (strcmp(str, "\4") && strcmp(str, "\n"));
	}
	// tputs(save_cursor, 1, ft_putchar_int);
	// while (ft_strcmp(str, "\n"))
	// {
	// 	ret = read(0, str, 100);
	// 	while (ft_strcmp(str, "\4") || ft_strcmp(str, "\n"))
	// 	{
	// 		write(1, "ch ", 3);
	// 		if (!ft_strcmp(str, "\e[A"))
	// 		{
	// 			tputs(restore_cursor, 1, ft_putchar_int);
	// 			tputs(tigetstr("ed"), 1, ft_putchar_int);
	// 			write(1, "up", 2);
	// 		}
	// 		else
	// 		{
	// 			write(1, str, ret);
	// 			term.size++;
	// 			term.line = charcat(term.line, *str);
	// 		}
	// 		ret = read(0, str, 100);
	// 	}
	// }
	// free(str);
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
