
#include"../includes/minishell.h"

static char **add_slash(char **env);

int	main(void)
{
	char	**path;
	char	*env;
	char	**kitaiti;

	env = getenv("PATH");
	kitaiti = ft_split(env, ':');
	kitaiti = add_slash(kitaiti);

	path = get_env_path();
	for (int i = 0; path[i] != NULL; i++)
		assert(strncmp(path[i], kitaiti[i], strlen(path[i])) == 0);
	return (0);
}

static char **add_slash(char **env)
{
	int i;
	char *temp;

	i = 0;
	while (env[i])
	{
		temp = ft_strjoin(env[i], "/");
		free(env[i]);
		env[i] = temp;
		i++;
	}
	return (env);
}

// cc -Wall -Wextra -Werror tests/get_env_path.c srcs/get_env_path.c libft/*.c srcs/utils/*.c
