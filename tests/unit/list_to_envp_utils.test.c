/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_envp_utils.test.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:00:00 by takitaga          #+#    #+#             */
/*   Updated: 2025/03/20 14:23:43 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <assert.h>

int	main(void)
{	
	// Create a linked list of t_env nodes for testing
	t_env *env = ft_calloc(1, sizeof(t_env));
	assert(env != NULL);
	env->key = ft_strdup("HOME");
	env->value = ft_strdup("/home/user");
	
	// Create second node
	t_env *second = ft_calloc(1, sizeof(t_env));
	assert(second != NULL);
	second->key = ft_strdup("PATH");
	second->value = ft_strdup("/usr/bin:/bin");
	env->next = second;
	
	// Create third node
	t_env *third = ft_calloc(1, sizeof(t_env));
	assert(third != NULL);
	third->key = ft_strdup("USER");
	third->value = ft_strdup("tester");
	second->next = third;
	
	// Test with 3 nodes
	assert(get_node_count(env) == 3);
	
	// Add fourth node
	t_env *fourth = ft_calloc(1, sizeof(t_env));
	assert(fourth != NULL);
	fourth->key = ft_strdup("PWD");
	fourth->value = ft_strdup("/workspaces");
	third->next = fourth;
	
	// Test with 4 nodes
	assert(get_node_count(env) == 4);
	
	// Test with NULL
	assert(get_node_count(NULL) == 0);
	
	// Test with single node
	t_env *single = ft_calloc(1, sizeof(t_env));
	assert(single != NULL);
	single->key = ft_strdup("SINGLE");
	single->value = ft_strdup("value");
	assert(get_node_count(single) == 1);
	
	return (0);
}
