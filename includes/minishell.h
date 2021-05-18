#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <term.h>

# define RESET			"\033[0m"
# define BLACK			"\033[30m"
# define RED			"\033[31m"
# define GREEN			"\033[32m"
# define YELLOW			"\033[33m"
# define BLUE			"\033[34m"
# define MAGENTA		"\033[35m"
# define CYAN			"\033[36m"
# define WHITE			"\033[37m"
# define BOLDBLACK		"\033[1m\033[30m"
# define BOLDRED		"\033[1m\033[31m"
# define BOLDGREEN		"\033[1m\033[32m"
# define BOLDYELLOW		"\033[1m\033[33m"
# define BOLDBLUE		"\033[1m\033[34m"
# define BOLDMAGENTA	"\033[1m\033[35m"
# define BOLDCYAN		"\033[1m\033[36m"
# define BOLDWHITE		"\033[1m\033[37m"

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
	char				**input_file;
	char				**output_file;
	char				**append_file;
	t_cmd				*cmds;
	t_cmd				*last;
	struct s_cmdtable	*next;
}						t_cmdtable;

typedef struct s_signal
{
	int					pid;
	int					status;
	int					inter;
	int					quit;
}						t_signal;

int			get_next_line(int fd, char **line);
t_env		*env_split(char **env);
char		**get_env_as_string(t_env *envs);
t_cmdtable	*parser(char *line, t_env *envs);
void		*ft_calloc(size_t count, size_t size);
char		**ft_split(char const *s, char c);
char		*get_token(char **line, char *spec, char perm, t_env *envs);

// tests
void		test_init_envs(t_env *envs);
void		test_envs_to_strings(t_env *envs);
void		test_parsing(t_cmdtable *table);

// utils
int			ft_strlen(char *str);
int			ft_arrlen(char **str);
char		*ft_strchr(const char *str, int c);
char		*ft_strdup(const char *str);
int			get_envs_len(t_env *envs);
void		free_arr(char **arr);
int			isspecial(char c);
int			ft_isspace(char c);
void		print_error_and_exit(char *str);
int			ft_strcmp(char *s1, char *s2);
void		ft_puts(char *str, int fd);
int			file_exist(char *filename);
char		*scan_path(char *binary, t_env *envs);
char		*charcat(char *str, char c);
char		*ft_concat(const char *s1, const char *s2);
char		*ft_strjoin(char const *s1, char const *s2);
char		**arr_copy(char **dest, char **src);
int			is_builtin(t_cmd *cmd);
char		*get_env(t_env *envs, char *name);
int			check_env(char *str);
void		print_error(char *bin, char *val, char *err);
int			check_env_name(char *name);
void		modify_env(t_env *envs, char *name, char *newvalue);
char		*pwd_getcurpath(void);

// executor
int			executor(t_cmdtable *table, t_env *envs, char **env);
int			executor_run_and_redir(t_cmd *cmd, t_cmdtable *table, int tmp[7]);
int			executor_redir(int oldfd, int newfd);
int			executor_init_fds(int tmp[7], t_cmdtable *table);

// builtins
int			builtin_pwd(void);
int			builtin_echo(char **argv);
int			builtin_cd(char **argv, t_env *envs);
int			builtin_unset(char **argv, t_env *envs);
int			builtin_export(char **argv, t_env *envs);
int			builtin_env(t_env *envs, int declare_x);

// inits
void		arg_init(t_cmd *cur);
void		cmd_init(t_cmd **cmd);
void		cmdtable_init(t_cmdtable **table);
char		**array_append(char **arr, int len);

// signal
void		sig_int(int code);
void		sig_quit(int code);
extern t_signal g_signal;
#endif
