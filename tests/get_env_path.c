
#include"../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char	**path;

	path = get_env_path(envp);

	// envp = NULL
	// envp[i] = NULL
	// PWD=""

	for (int i = 0; path[i] != NULL; i++)
		printf("path[i] : %s\n", path[i]);
	return (0);
}

// cc -Wall -Wextra -Werror test/get_env_path.c srcs/get_env_path.c libft/*.c
