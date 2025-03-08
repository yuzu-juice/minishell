
#include"../includes/minishell.h"

static char **add_slash_last(char **env);

int	main(void)
{
	char	**path;
	char	*env;
	char	**expect;

	env = getenv("PATH");
	expect = ft_split(env, ':');
	expect = add_slash_last(expect);

	path = get_env_path();
	for (int i = 0; path[i] != NULL; i++)
		assert(strncmp(path[i], expect[i], strlen(path[i])) == 0);
	return (0);
}

static char **add_slash_last(char **env)
{
	int i;
	char *temp;

	i = 0;
	while (env[i])
	{
		temp = add_slash(env[i]);
		free(env[i]);
		env[i] = temp;
		i++;
	}
	return (env);
}

// cc -Wall -Wextra -Werror tests/get_env_path.c srcs/get_env_path.c libft/*.c srcs/utils/*.c
