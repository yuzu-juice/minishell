
#include"../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char	*path;

	path = create_cmd_path(envp, "");
	printf("path : %s\n", path);
	path = create_cmd_path(envp, "ls");
	printf("path : %s\n", path);
	path = create_cmd_path(envp, "/usr/bin/ls");
	printf("path : %s\n", path);
	path = create_cmd_path(envp, "./test.out");
	printf("path : %s\n", path);

	// これいるなあ　対応してねえ
	path = create_cmd_path(envp, "../test.out");
	printf("path : %s\n", path);
	return (0);
}
// cc -Wall -Wextra -Werror test/create_cmd_path.c srcs/create_cmd_path.c srcs/get_env_pwd.c srcs/get_env_path.c libft/*.c

