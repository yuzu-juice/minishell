#include "../../includes/minishell.h"

// TODO :serch_exec_cmd_path()
// 	when 'return cmd_only',
// 	error message shoud be "command not found"
int	main(void)
{
	char	*path;

	// actual command
	path = create_cmd_path("ls");
	assert(strncmp(path, "/usr/bin/ls", 11) == 0);

	// absolute path
	path = create_cmd_path("/usr/bin/ls");
	assert(strncmp(path, "/usr/bin/ls", 11) == 0);

	// not exist command
	path = create_cmd_path("ca");
	assert(strncmp(path, "ca", 2) == 0);

	// execve()が勝手に補完してくれるので展開不要
	// start with "."
	path = create_cmd_path("./test.out");
	assert(strncmp(path, "./test.out", 10) == 0);
	path = create_cmd_path("../../test.out");
	assert(strncmp(path, "../../test.out", 14) == 0);

	// NULLは来ない予定なので不要
	// path = create_cmd_path("");
	// printf("path : %s\n", path);
	return (0);
}
// cc -Wall -Wextra -Werror tests/create_cmd_path.c srcs/create_cmd_path.c srcs/get_env_pwd.c srcs/get_env_path.c libft/*.c srcs/utils/*.c

