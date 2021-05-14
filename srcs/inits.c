#include "../includes/minishell.h"

void	arg_init(t_cmd *last)
{
	char	**arr;
	char	**arr_buf;

	last->argc++;
	arr = ft_calloc(last->argc + 1, sizeof(char *));
	arr = arr_copy(arr, last->argv);
	arr_buf = last->argv;
	last->argv = arr;
	free_arr(arr_buf);
}

void	cmd_init(t_cmd **cmd)
{

	(*cmd) = ft_calloc(1, sizeof(t_cmd));
	(*cmd)->next = 0;
	(*cmd)->argc = 0;
	(*cmd)->argv = ft_calloc(2, sizeof(char *));
}

void	cmdtable_init(t_cmdtable **table)
{
	*table = ft_calloc(1, sizeof(t_cmdtable));
	cmd_init(&(*table)->cmds);
	(*table)->last = (*table)->cmds;
	(*table)->input_file = 0;
	(*table)->output_file = 0;
	(*table)->next = 0;
}
