

#include"../includes/minishell.h"

static char *add_slash(char *env);

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	char *pwd;
	char *env;

	env = getenv("PWD");
	env = add_slash(env);
	pwd = get_env_pwd();
	assert(strncmp(pwd, env, strlen(pwd)) == 0);
	return (0);
}

static char *add_slash(char *env)
{
	char *temp;

	temp = ft_strjoin(env, "/");
	return (temp);
}

// cc -Wall -Wextra -Werror tests/get_env_pwd.c srcs/get_env_pwd.c libft/*.c srcs/utils/*.c
