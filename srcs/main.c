#include "../includes/minishell.h"

t_signal	g_signal = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

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
		signal_init();
		print_prompt();
		term_loop(hist, envs);
		signal_init();
		if (*g_signal.line)
			save_cmd(g_signal.line, hist);
		cmdtable = parser(g_signal.line, envs);
		executor(cmdtable, envs, get_envs(envs));
		modify_env(envs, "?", ft_itoa(g_signal.status));
	}
	return (0);
}
