#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

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

int			get_next_line(int fd, char **line);

#endif