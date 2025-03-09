#include "../../includes/minishell.h"

int	main(void)
{
	char	*pwd;
	char	*env;

	env = getenv("PWD");
	env = add_slash(env);
	pwd = get_env_pwd();
	assert(strncmp(pwd, env, strlen(pwd)) == 0);
	return (0);
}

// cc -Wall -Wextra -Werror tests/get_env_pwd.c srcs/get_env_pwd.c libft/*.c srcs/utils/*.c
