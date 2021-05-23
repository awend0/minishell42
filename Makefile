NAME	= minishell

SRC		= main.c \
		term.c \
		envs.c \
		gnl.c \
		test.c \
		parser.c \
		tokens.c \
		inits.c \
		utils.c \
		utils2.c \
		utils_lib.c \
		memory.c \
		executor.c \
		executor_pipe.c \
		signal.c \
		builtin_pwd.c \
		builtin_echo.c \
		builtin_cd.c \
		builtin_unset.c \
		builtin_export.c \
		builtin_env.c \
		ft_split.c

DIR_SRC = srcs/
SRCS	= $(addprefix $(DIR_SRC), $(SRC))
OBJS	= $(SRCS:c=o)
<<<<<<< HEAD
FLAGS	= -O3 -Wall -Wextra -Werror -fsanitize=address
=======
FLAGS	= -O3 -Wall -Wextra -Werror
>>>>>>> 6cd39239a1ac36e23a651e5fe2309c4d23100206

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(FLAGS) -o $(NAME) $(OBJS) -ltermcap

%.o: %.c
	gcc -g $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

norm:
	norminette .
