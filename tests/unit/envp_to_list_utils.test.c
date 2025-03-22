/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_to_list_utils.test.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:31:59 by takitaga          #+#    #+#             */
/*   Updated: 2025/03/20 14:13:47 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(void)
{
	t_env	*env;
	t_env	*second_env;
	t_env	*third_env;
	t_env	*tmp;
	
	// Test 1: Basic environment variable with single value
	env = ft_calloc(1, sizeof(t_env));
	add_env_node(env, "HOME=/home/user", 0);
	assert(strcmp(env->key, "HOME") == 0);
	assert(strcmp(env->value, "/home/user") == 0);
	assert(env->next == NULL);
	
	// Test 2: Environment variable with path value
	add_env_node(env, "PATH=/usr/bin:/bin:/usr/local/bin", 1);
	second_env = env->next;
	assert(second_env != NULL);
	assert(strcmp(second_env->key, "PATH") == 0);
	assert(strcmp(second_env->value, "/usr/bin:/bin:/usr/local/bin") == 0);
	assert(second_env->next == NULL);
	
	// Test 3: Environment variable with empty value
	add_env_node(env, "EMPTY=", 2);
	tmp = second_env->next;
	assert(tmp == NULL);
	
	// Test 4: Environment variable with special characters
	add_env_node(env, "SPECIAL=value with spaces:another$value:third*value", 3);
	third_env = second_env->next;
	assert(third_env != NULL);
	assert(strcmp(third_env->key, "SPECIAL") == 0);
	assert(strcmp(third_env->value, "value with spaces:another$value:third*value") == 0);
	assert(third_env->next == NULL);

	return (0);
}
