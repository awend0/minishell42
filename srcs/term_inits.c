#include "../includes/minishell.h"

void	termcaps_init(t_env *envs)
{
	g_signal.cur_term = ft_calloc(sizeof(struct termios));
	g_signal.backup_term = ft_calloc(sizeof(struct termios));
	tcgetattr(0, g_signal.cur_term);
	tcgetattr(0, g_signal.backup_term);
	g_signal.cur_term->c_lflag &= ~(ECHO);
	g_signal.cur_term->c_lflag &= ~(ICANON);
	g_signal.cur_term->c_cc[VTIME] = 0;
	g_signal.cur_term->c_cc[VMIN] = 1;
	tcsetattr(0, TCSANOW, g_signal.cur_term);
	tgetent(0, get_env(envs, "TERM"));
}

void	term_init(void)
{
	g_signal.term = ft_calloc_save(sizeof(t_term));
	g_signal.term->position = 0;
	g_signal.line = ft_calloc_save(2 * sizeof(char));
	g_signal.term->size = 0;
}
