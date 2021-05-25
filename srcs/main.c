#include "../includes/minishell.h"

t_signal g_signal = {0, 0, 0, 0};

void	hist_init(t_hist **hist, int start)
{
	(*hist) = malloc(sizeof(t_hist));
	(*hist)->next = 0;
	(*hist)->prev = 0;
	if (start)
		(*hist)->cmd = ft_calloc(sizeof(char) * 2);
	else
		(*hist)->cmd = 0;
}

void	save_cmd(char *line, t_hist *hist)
{
	t_hist	*new;
	t_hist	*buf;

	buf = hist;
	while (hist->next && hist->next != buf)
		hist = hist->next;
	if (!ft_strcmp(line, hist->cmd))
		return ;
	hist_init(&new, 0);
	new->prev = hist;
	hist->next = new;
	new->cmd = ft_strdup(line, 0);
	new->next = buf;
	buf->prev = new;
}

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_cmdtable	*cmdtable;
	t_env		*envs;
	t_hist		*hist;

	envs = env_split(env);
	termcaps_init(envs);
	hist_init(&hist, 1);
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
		modify_env(envs, "?", ft_itoa(executor(cmdtable, envs, get_envs(envs))));
	}
	ft_free();
	ft_free_envs(envs);
	return (0);
}
