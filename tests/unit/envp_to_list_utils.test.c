/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_to_list_utils.test.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:31:59 by takitaga          #+#    #+#             */
/*   Updated: 2025/03/19 15:32:00 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <assert.h>

int	main(void)
{
	t_env	*env;
	t_env	*second_env;
	t_env	*third_env;
	t_env	*fourth_env;
	t_value	*value;
	
	// Test 1: Basic environment variable with single value
	env = ft_calloc(1, sizeof(t_env));
	add_env_node(env, "HOME=/home/user", 0);
	assert(strcmp(env->key, "HOME") == 0);
	assert(env->values != NULL);
	assert(strcmp(env->values->value, "/home/user") == 0);
	assert(env->next == NULL);
	
	// Test 2: Environment variable with multiple path values
	add_env_node(env, "PATH=/usr/bin:/bin:/usr/local/bin", 1);
	second_env = env->next;
	assert(second_env != NULL);
	assert(strcmp(second_env->key, "PATH") == 0);
	assert(second_env->values != NULL);
	value = second_env->values;
	assert(strcmp(value->value, "/usr/bin") == 0);
	value = value->next;
	assert(value != NULL);
	assert(strcmp(value->value, "/bin") == 0);
	value = value->next;
	assert(value != NULL);
	assert(strcmp(value->value, "/usr/local/bin") == 0);
	assert(value->next == NULL);
	
	// Test 3: Environment variable with empty value
	add_env_node(env, "EMPTY=", 2);
	third_env = second_env->next;
	assert(third_env != NULL);
	assert(strcmp(third_env->key, "EMPTY") == 0);
	assert(third_env->values != NULL);
	assert(strcmp(third_env->values->value, "") == 0);
	assert(third_env->values->next == NULL);
	
	// Test 4: Environment variable with special characters
	add_env_node(env, "SPECIAL=value with spaces:another$value:third*value", 3);
	fourth_env = third_env->next;
	assert(fourth_env != NULL);
	assert(strcmp(fourth_env->key, "SPECIAL") == 0);
	assert(fourth_env->values != NULL);
	value = fourth_env->values;
	assert(strcmp(value->value, "value with spaces") == 0);
	value = value->next;
	assert(value != NULL);
	assert(strcmp(value->value, "another$value") == 0);
	value = value->next;
	assert(value != NULL);
	assert(strcmp(value->value, "third*value") == 0);
	assert(value->next == NULL);

	return (0);
}
