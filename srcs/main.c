#include "../includes/minishell.h"

t_signal	g_signal = {0, 0, 0, 0, 0, 0};

void	hist_init(t_hist **hist, int start)
{
	(*hist) = ft_calloc_save2(sizeof(t_hist));
	(*hist)->next = 0;
	(*hist)->prev = 0;
	if (start)
		(*hist)->cmd = ft_calloc_save2(sizeof(char) * 2);
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
	char			*line;
	t_cmdtable		*cmdtable;
	t_env			*envs;
	t_hist			*hist;

	(void)argc;
	(void)argv;
	envs = env_split(env);
	termcaps_init(envs);
	hist_init(&hist, 1);
	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
	while (1)
	{
		g_signal.pid = 0;
		ft_putstr_fd(BOLDCYAN"paSHtet"BOLDYELLOW" » "RESET, 1);
		line = term_loop(hist);
		if (*line)
			save_cmd(line, hist);
		modify_env(envs, "?", ft_itoa(g_signal.status));
		cmdtable = parser(line, envs);
		executor(cmdtable, envs, get_envs(envs));
	}
	return (0);
}
