NAME	= minishell

SRC		= main.c \
		envs.c \
		gnl.c \
		test.c \
		parser.c \
		utils.c \
		utils2.c \
		executor.c \
		builtin_pwd.c \
		builtin_echo.c

DIR_SRC = srcs/
SRCS	= $(addprefix $(DIR_SRC), $(SRC))
OBJS	= $(SRCS:c=o)
FLAGS	= -O3

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(FLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	gcc $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

norm:
	norminette .