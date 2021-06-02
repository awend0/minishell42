NAME	= minishell

SRC		= main.c \
		term.c \
		term_inits.c \
		term_del_insert.c \
		term_commands.c \
		envs.c \
		parser.c \
		parser_redirection.c \
		tokens.c \
		inits.c \
		utils.c \
		utils2.c \
		utils3.c \
		utils4.c \
		utils_lib.c \
		utils_lib2.c \
		utils_lib3.c \
		memory.c \
		executor.c \
		executor_pipe.c \
		executor_run.c \
		signal.c \
		builtin_pwd.c \
		builtin_echo.c \
		builtin_cd.c \
		builtin_unset.c \
		builtin_export.c \
		builtin_env.c \
		builtin_exit.c \
		ft_split.c \

DIR_SRC = srcs/
SRCS	= $(addprefix $(DIR_SRC), $(SRC))
OBJS	= $(SRCS:c=o)
FLAGS	= -O3 -Wall -Wextra -Werror -fsanitize=address

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(FLAGS) -o $(NAME) $(OBJS) -ltermcap

%.o: %.c
	gcc $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

norm:
	norminette .
