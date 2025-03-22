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
	assert(env_list != NULL);
	
	// Verify first node
	assert(strcmp(env_list->key, "HOME") == 0);
	assert(strcmp(env_list->value, "/home/user") == 0);
	
	// Verify second node
	t_env *second = env_list->next;
	assert(second != NULL);
	assert(strcmp(second->key, "PATH") == 0);
	assert(strcmp(second->value, "/usr/bin:/bin") == 0);
	
	// Verify third node
	t_env *third = second->next;
	assert(third != NULL);
	assert(strcmp(third->key, "USER") == 0);
	assert(strcmp(third->value, "tester") == 0);
	
	// Verify fourth node
	t_env *fourth = third->next;
	assert(fourth != NULL);
	assert(strcmp(fourth->key, "PWD") == 0);
	assert(strcmp(fourth->value, "/workspaces") == 0);
	assert(fourth->next == NULL);
	
	// Test for list_to_envp
	char **new_envp = list_to_envp(env_list);
	assert(new_envp != NULL);
	
	// Verify converted environment variables
	assert(strcmp(new_envp[0], "HOME=/home/user") == 0);
	assert(strcmp(new_envp[1], "PATH=/usr/bin:/bin") == 0);
	assert(strcmp(new_envp[2], "USER=tester") == 0);
	assert(strcmp(new_envp[3], "PWD=/workspaces") == 0);
	assert(new_envp[4] == NULL);
	
	return (0);
}
