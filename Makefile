NAME	= minishell
MAIN = srcs/main.c
SRCS	= \
	srcs/exec_cmd.c\
	srcs/get_env_path.c\
	srcs/create_cmd_path.c\
	srcs/signal_handler.c\
	srcs/utils/free_string_array.c\
	srcs/utils/add_slash.c\
	srcs/utils/remove_quotes.c\
	srcs/utils/search_env.c\
	srcs/builtin_commands/echo.c\
	srcs/builtin_commands/pwd.c\
	srcs/builtin_commands/cd.c\
	srcs/env/env.c\
	srcs/env/envp_to_list_utils.c\
	srcs/env/list_to_envp_utils.c\
	srcs/builtin_commands/unset.c\
	srcs/builtin_commands/env.c\
	srcs/redirections/redirect.c\
	srcs/redirections/input_utils.c\
	srcs/redirections/output_utils.c\
	srcs/builtin_commands/export.c\
	srcs/builtin_commands/exit.c\
	srcs/parser/create_normal_token.c\
	srcs/parser/create_process_list_utils1.c\
	srcs/parser/create_process_list_utils2.c\
	srcs/parser/create_process_list.c\
	srcs/parser/create_split_token.c\
	srcs/parser/create_token_list.c\
	srcs/parser/create_token_util.c\
	srcs/parser/expand_dollar_util.c\
	srcs/parser/expand_dollar.c\
	srcs/parser/parser.c\
	srcs/parser/error.c\
	srcs/get_input_line.c\
	srcs/create_minishell_struct.c\
	srcs/pipe/pipe.c\
	srcs/pipe/pipe_process_handlers.c\
	srcs/pipe/change_fds.c\
	srcs/exec_builtin_cmd.c\
	srcs/parser/parser_redirection.c
HEADERS	= \
	includes/minishell.h\
	includes/core_feature.h\
	includes/signal_handlings.h\
	includes/utils.h\
	includds/builtin_commands.h\
	includds/env.h
MAIN_OBJ = $(MAIN:.c=.o)
OBJS	= $(SRCS:.c=.o)

CC	= cc
CFLAGS	= -Wall -Wextra -Werror -I includes/ -g

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

unit: all
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

test: norm unit integration

valgrind: all
	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --gen-suppressions=all ./minishell

.PHONY: all clean fclean re norm integration system unit
