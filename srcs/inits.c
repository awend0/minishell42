#include "../includes/minishell.h"

void	arg_init(t_cmdtable *buf)
{
	char	**arr;
	char	**arr_buf;

	buf->cmds->argc++;
	arr = ft_calloc(buf->cmds->argc + 1, sizeof(char *));
	arr = arr_copy(arr, buf->cmds->argv);
	arr_buf = buf->cmds->argv;
	buf->cmds->argv = arr;
	free_arr(arr_buf);
}

t_cmd	*cmd_init(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	cmd->next = 0;
	cmd->argc = 0;
	cmd->argv = ft_calloc(2, sizeof(char *));
	return (cmd);
}

void	cmdtable_init(t_cmdtable **table)
{
	*table = ft_calloc(1, sizeof(t_cmdtable));
	(*table)->cmds = cmd_init();
	(*table)->input_file = 0;
	(*table)->output_file = 0;
	(*table)->next = 0;
}
