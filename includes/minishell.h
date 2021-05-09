#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
	struct s_env		*prev;
}						t_env;

typedef struct s_cmd
{
	char				*cmd;
	char				**flags;
	int					argc;
	char				**argv;
	int					pipe;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_cmdtable
{
	char				*input_file;
	char				*output_file;
	int					cmds_count;
	t_cmd				*cmds;
	struct s_cmdtable	*next;
}						t_cmdtable;

int			get_next_line(int fd, char **line);
t_env		*init_envs(char **env);
void		test_init_envs(t_env *envs);

#endif