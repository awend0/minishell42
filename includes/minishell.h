#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_cmd
{
	char			*cmd;
	char			**flags;
	int				argc;
	char			**argv;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_cmdtable
{
	char			*input_file;
	char			*output_file;
	int				cmds_count;
	t_cmd			*cmds;
}					t_cmdtable;

#endif