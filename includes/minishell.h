#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
	struct s_env		*prev;
}						t_env;

typedef struct s_cmd
{
	int					argc;
	char				**argv;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_cmdtable
{
	char				*input_file;
	char				*output_file;
	t_cmd				*cmds;
	struct s_cmdtable	*next;
}						t_cmdtable;

int			get_next_line(int fd, char **line);
t_env		*init_envs(char **env);
char		**get_env_as_string(t_env *envs);

// tests
void		test_init_envs(t_env *envs);
void		test_envs_to_strings(t_env *envs);

// utils
int			ft_strlen(char *str);
int			get_envs_len(t_env *envs);

#endif
