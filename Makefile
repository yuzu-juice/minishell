NAME	= minishell
SRCS	= \
	srcs/main.c\
	srcs/exec_cmd.c\
	srcs/get_env_path.c\
	srcs/get_env_pwd.c\
	srcs/create_cmd_path.c\
	srcs/utils/free_string_array.c
OBJS	= $(SRCS:.c=.o)

CC	= cc
CFLAGS	= -Wall -Wextra -Werror -I includes/

.DEFAULT:	all

all: $(NAME)

# libft
LIBFT = libft
$(LIBFT)/libft.a:
	make -C $(LIBFT)

$(NAME): $(OBJS) $(LIBFT)/libft.a
	$(CC) $(CFLAG) -o $(NAME) $(OBJS) -L$(LIBFT) -lft -lreadline

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	make -C $(LIBFT) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIBFT) fclean
	rm -f $(NAME)

norm:
	norminette srcs includes

re: fclean all

# test
integration: all

system: all
	tests/run_test.sh

unit:
	tests/unit_test.sh

.PHONY: all clean fclean re
