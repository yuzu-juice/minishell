# unit test

# TEST_DIR = pwd
CFAGS="-Wall -Wextra -Werror"
SRCS="srcs"
TEST="tests"
LIBFT="libft/*.c"
UTILS="srcs/utils/*.c"

# get_env_path
	cc ${CFLAGS} ${TEST}/get_env_path.c ${SRCS}/get_env_path.c ${LIBFT} ${UTILS}
	./a.out
	rm a.out

# get_env_pwd
	cc ${CFLAGS} ${TEST}/get_env_pwd.c ${SRCS}/get_env_pwd.c ${LIBFT} ${UTILS}
	./a.out
	rm a.out

# create_cmd_path
	cc ${CFLAGS} ${TEST}/create_cmd_path.c ${SRCS}/create_cmd_path.c ${SRCS}/get_env_pwd.c ${SRCS}/get_env_path.c ${LIBFT} ${UTILS}
	./a.out
	rm a.out

### TODO:これ結合じゃない？
#./unit_test.sh: 32: Syntax error: end of file unexpected (expecting "then")
# exec_cmd
	# cc ${CFLAGS} exec_cmd.c ${SRCS}/exec_cmd.c ${SRCS}/create_cmd_path.c ${SRCS}/get_env_path.c ${SRCS}/get_env_pwd.c ${LIBFT} ${UTILS}
	# ./a.out > a
	# ls > b
	# if (diff a b | wc -l = 0)
	# 	echo "exec_cmd OK" > unit_test.log
	# rm a.out a b c
