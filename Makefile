NAME	= minishell
MAIN = srcs/main.c
SRCS	= \
	srcs/exec_cmd.c\
	srcs/get_env_path.c\
	srcs/get_env_pwd.c\
	srcs/create_cmd_path.c\
	srcs/parser.c\
	srcs/create_token_list.c\
	srcs/create_token_util.c\
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
UNIT_TESTS = $(wildcard tests/unit/*.test.c)
INTEGRATION_TESTS = $(wildcard tests/integration/*.test.sh)

norm:
	norminette srcs includes

unit:
	@echo "Running unit tests..."
	@mkdir -p tests/unit/bin
	@for test in $(UNIT_TESTS); do \
		test_name=$$(basename $${test} .test.c); \
		out_path=tests/unit/bin/$${test_name}.out; \
		if $(CC) $${test} $(SRCS) -L$(LIBFT) -lft -lreadline -o $${out_path} && \
				./$${out_path}; then \
			echo "\033[32mPassed: $${test}\033[0m"; \
		else \
			echo "\033[31mFailed: $${test}\033[0m"; \
			rm -rf tests/unit/bin; \
			exit 1; \
		fi; \
	done
	@echo "⭐️\033[32mPassed all unit tests!\033[0m⭐️"
	@rm -rf tests/unit/bin

integration: all
	@echo "Running integration tests..."
	@for test in $(INTEGRATION_TESTS); do \
		if chmod 755 $${test} && $${test}; then \
			echo "\033[32mPassed: $${test}\033[0m";\
		else \
			echo "\033[31mFailed: $${test}\033[0m"; \
			exit 1; \
		fi; \
	done
	@echo "⭐️\033[32mPassed all integration tests!\033[0m⭐️"

.PHONY: all clean fclean re norm integration system unit
