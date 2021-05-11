NAME	= minishell

SRC		= main.c \
		envs.c \
		gnl.c \
		test.c \
		utils.c \
		utils2.c \
		executor.c \
		builtin_pwd.c \
		builtin_echo.c

DIR_SRC = srcs/
SRCS	= $(addprefix $(DIR_SRC), $(SRC))
OBJS	= $(SRCS:c=o)

all: $(NAME)

$(NAME): $(OBJS)
	gcc -o $(NAME) $(OBJS)

%.o: %.c
	gcc -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

norm:
	norminette .