NAME	= minishell
SRCS	= srcs/main.c
OBJS	= $(SRCS:.c=.o)

CC	= cc
CFLAGS	= -Wall -Wextra -Werror -I includes/

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAG) -o $(NAME) $(OBJS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
