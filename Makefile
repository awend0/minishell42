NAME	= minishell

SRC		= main.c \
			envs.c \
			gnl.c \
			test.c

DIR_SRC = srcs/
SRCS	= $(addprefix $(DIR_SRC), $(SRC))
OBJS	= $(SRCS:c=o)

all: $(NAME)

$(NAME): $(OBJS)
	gcc -Wall -Wextra -Werror -o $(NAME) $(OBJS)

%.o: %.c
	gcc -Wall -Wextra -Werror -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

norm:
	norminette .