#include "../../includes/minishell.h"

int	main(void)
{
	// Test for envp_to_list
	char *test_envp[] = {
		"HOME=/home/user",
		"PATH=/usr/bin:/bin",
		"USER=tester",
		"PWD=/workspaces",
		NULL
	};

	t_env *env_list = envp_to_list(test_envp);

	// PATHが存在するか確認
	assert(strcmp(env_list->next->key, "PATH") == 0);

	char *unset_path[] = {
		"PATH=/usr/bin:/bin",
		NULL
	};

	//PATHをunset
	unset(1, unset_path, &env_list);
	while (env_list)
	{
		printf("%s=%s\n", env_list->key, env_list->value);
		assert(strcmp(env_list->key, "PATH") != 0);
		env_list = env_list->next;
	}
	return (0);
}
