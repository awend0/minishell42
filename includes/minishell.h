#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <term.h>
# include <termios.h>
# include <termcap.h>
# include <stdio.h>

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
	int					secret;
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
	int					append;
	t_cmd				*cmds;
	t_cmd				*last;
	struct s_cmdtable	*next;
}						t_cmdtable;

typedef struct s_list
{
	void				*node;
	void				*next;
}						t_list;

typedef struct s_term
{
	int					position;
	int					size;
}						t_term;

typedef struct s_hist
{
	char				*cmd;
	struct s_hist		*prev;
	struct s_hist		*next;
}						t_hist;

typedef struct s_signal
{
	int					pid;
	int					status;
	int					inter;
	int					quit;
	char				*line;
	t_list				*memory;
	t_list				*memory2;
	t_term				*term;
	struct termios		*cur_term;
	struct termios		*backup_term;
}						t_signal;

int			get_next_line(int fd, char **line);
t_env		*env_split(char **env);
char		**get_envs(t_env *envs);
t_cmdtable	*parser(char *line, t_env *envs);
char		**ft_split(char const *s, char c);
char		*get_token(char **line, char *spec, char perm, t_env *envs);
void		termcaps_init(t_env *envs);
void		term_loop(t_hist *hist, t_env *envs);
void		add_redirection(char **line, t_cmdtable *table, t_env *envs);
void		print_prompt(void);

int			ft_arrlen(char **str);
int			get_envs_len(t_env *envs);
int			isspecial(char c);
int			file_exist(char *filename);
int			is_regular_file(char *path);
char		*scan_path(char *binary, t_env *envs);
char		*charcat(char *str, char c);
char		*ft_concat(char *s1, char *s2);
char		*ft_strjoin(char const *s1, char const *s2);
char		**arr_copy(char **dest, char **src);
int			is_builtin(t_cmd *cmd);
char		*get_env(t_env *envs, char *name);
int			check_env(char *str);
void		print_error(char *bin, char *val, char *err);
int			check_env_name(char *name);
void		modify_env(t_env *envs, char *name, char *newvalue);
char		*pwd_getcurpath(void);
int			ft_putchar_term(int c);

int			executor(t_cmdtable *table, t_env *envs, char **env);
int			executor_open(t_cmd *cmd, t_cmdtable *table, int tmp[7]);
int			executor_redir(int oldfd, int newfd);
int			executor_init_fds(int tmp[7], t_cmdtable *table);
int			executor_exec_binary(char **argv, char **env);
int			executor_exec_builtin(char **argv, t_env *envs, char **env);
int			executor_run_file(t_cmd *cmd, t_env *envs, char **env, int *tmp);
int			executor_run_command(t_cmd *cmd, t_env *envs, char **env, int *tmp);
int			executor_cmd(t_cmd *cmd, t_env *envs, char **env, int *tmp);

int			builtin_pwd(void);
int			builtin_echo(char **argv);
int			builtin_cd(char **argv, t_env *envs);
int			builtin_unset(char **argv, t_env *envs);
int			builtin_export(char **argv, t_env *envs);
int			builtin_env(t_env *envs, int declare_x);
int			builtin_exit(char **argv);

void		arg_init(t_cmd *cur);
void		cmd_init(t_cmd **cmd);
void		cmdtable_init(t_cmdtable **table);
char		**array_append(char **arr, int len);
void		add_new_cmdtable(t_cmdtable **table, char **line);

void		signal_init(void);
void		sig_int(int code);
void		sig_quit(int code);
extern t_signal	g_signal;

void		ft_free(int memory);
void		*ft_calloc_save(int size);
void		*ft_calloc_save2(int size);
void		*ft_calloc(int size);

void		del_one(t_term *term);
void		del_front(t_term *term);
void		write_char(char *str, int ret, t_term *term);
char		*insert_char(char *line, char *str, int ret, int pos);
char		*get_next(t_hist **hist, t_term *term);
char		*get_privious(t_hist **hist, t_term *term);
void		termcaps_init(t_env *envs);
void		term_init(void);

char		*ft_strchr(char *str, int c);
int			ft_strcmp(char *s1, char *s2);
void		ft_putstr_fd(char *str, int fd);
char		*ft_itoa(int n);
int			ft_strlen(char *str);
void		ft_putnbr_fd(int n, int fd);
char		*ft_strcpy(char *dst, char *src);
char		*ft_strdup(char *s, int save);
char		*ft_strndup(char *s, int n, int save);
char		*ft_strcat(char *s1, char *s2);
void		*ft_memcpy(void *dest, void *src, int n);
int			ft_atoi(const char *str);
char		*ft_tolower(char *str);
#endif
