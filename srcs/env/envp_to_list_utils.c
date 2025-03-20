/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_to_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:58:23 by takitaga          #+#    #+#             */
/*   Updated: 2025/03/20 14:07:08 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_env	*get_last_env_node(t_env *env);

void	add_env_node(t_env *env, char *str, int i)
{
	char	**key_values;
	t_env	*new_node;

	if (env == NULL || str == NULL)
		return ;
	key_values = ft_split(str, '=');
	if (key_values == NULL || key_values[1] == NULL)
		return (free_string_double_array(key_values));
	if (i == 0)
		new_node = env;
	else
	{
		new_node = ft_calloc(1, sizeof(t_env));
		if (new_node == NULL)
			return (free_string_double_array(key_values));
		get_last_env_node(env)->next = new_node;
	}
	new_node->key = key_values[0];
	new_node->value = key_values[1];
	free(key_values);
}

static t_env	*get_last_env_node(t_env *env)
{
	t_env	*tmp;

	if (env == NULL)
		return (NULL);
	tmp = env;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}
