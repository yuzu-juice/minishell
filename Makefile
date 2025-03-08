NAME	= minishell
MAIN = srcs/main.c
SRCS	= \
	srcs/exec_cmd.c\
	srcs/get_env_path.c\
	srcs/get_env_pwd.c\
	srcs/create_cmd_path.c\
	srcs/utils/free_string_array.c\
	srcs/utils/add_slash.c
MAIN_OBJ = $(MAIN:.c=.o)
OBJS	= $(SRCS:.c=.o)

CC	= cc
CFLAGS	= -Wall -Wextra -Werror -I includes/

.DEFAULT:	all

all: $(NAME)

# libft
LIBFT = libft
$(LIBFT)/libft.a:
	make -C $(LIBFT)

$(NAME): $(MAIN_OBJ) $(OBJS) $(LIBFT)/libft.a
	$(CC) $(CFLAG) -o $(NAME) $(MAIN_OBJ) $(OBJS) -L$(LIBFT) -lft -lreadline

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	make -C $(LIBFT) clean
	rm -f $(MAIN_OBJ) $(OBJS)

fclean: clean
	make -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all

# test
UNIT_TESTS = $(wildcard tests/*.test.c)

norm:
	norminette srcs includes

unit:
	@echo "Running unit tests..."
	@mkdir -p tests/bin
	@for test in $(UNIT_TESTS); do \
		test_name=$$(basename $${test} .test.c); \
		out_path=tests/bin/$${test_name}.out; \
		if $(CC) $${test} $(SRCS) -L$(LIBFT) -lft -lreadline -o $${out_path} && \
				./$${out_path}; then \
			echo "\033[32mPassed: $${test}\033[0m"; \
		else \
			echo "\033[31mFailed: $${test}\033[0m"; \
			rm -rf tests/bin; \
			exit 1; \
		fi; \
	done
	@echo "⭐️\033[32mPassed all unit tests!\033[0m⭐️"
	@rm -rf tests/bin

integration: all

system: all
	tests/run_test.sh

.PHONY: all clean fclean re norm integration system unit
