

#include"../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char *pwd;

	pwd = get_env_pwd(envp);
	printf("pwd : %s\n", pwd);
	return (0);
}

// cc -Wall -Wextra -Werror test/get_env_pwd.c srcs/get_env_pwd.c libft/*.c
