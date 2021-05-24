#include "../includes/minishell.h"

t_signal g_signal = {0, 0, 0, 0, 0};

void	hist_init(t_hist **hist)
{
	(*hist) = malloc(sizeof(t_hist));
	(*hist)->next = 0;
	(*hist)->prev = 0;
	(*hist)->cmd = 0;
}

void	save_cmd(char *line, t_hist *hist)
{
	t_hist	*new;
	t_hist	*buf;

	buf = hist;
	if (!hist->cmd)
	{
		hist->next = buf;
		hist->prev = buf;
		hist->cmd = ft_strdup(line, 0);
	}
	else
	{
		while (hist->next && hist->next != buf)
			hist = hist->next;
		hist_init(&new);
		new->prev = hist;
		hist->next = new;
		new->cmd = ft_strdup(line, 0);
		new->next = buf;
		buf->prev = new;
	}
}

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_cmdtable	*cmdtable;
	t_env		*envs;
	t_hist		*hist;

	envs = env_split(env);
	termcaps_init();
	hist_init(&hist);
	if (argc == 3 && !ft_strcmp(argv[1], "-c"))
		return(executor(parser(argv[2], envs), envs, env));
	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
	while (1)
	{
		ft_putstr_fd(BOLDCYAN"paSHtet"BOLDYELLOW" » "RESET, 1);
		line = term_loop(hist);
		if (*line)
			save_cmd(line, hist);
		cmdtable = parser(line, envs);
		modify_env(envs, "?", ft_itoa(executor(cmdtable, envs, env)));
	}
	ft_free();
	ft_free_envs(envs);
	return (0);
}
