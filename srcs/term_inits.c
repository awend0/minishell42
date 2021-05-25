#include "../includes/minishell.h"

void	termcaps_init(t_env *envs)
{
	struct termios	term;

	tcgetattr(0, &term);
	g_signal.backup = ft_calloc_save2(sizeof(struct termios));
	tcgetattr(0, g_signal.backup);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	tgetent(0, get_env(envs, "TERM"));
}

void	term_init(t_term *term)
{
	term->position = 0;
	term->line = ft_calloc_save(2 * sizeof(char));
	term->size = 0;
}
