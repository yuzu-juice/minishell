/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_to_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:58:23 by takitaga          #+#    #+#             */
/*   Updated: 2025/04/22 16:51:39 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_env	*get_last_env_node(t_env *env);
static char		**split_string(char *str, char delimiter);
static bool		return_error(char **key_values);

bool	add_env_node(t_env *env, char *str, int i)
{
	char	**key_values;
	t_env	*new_node;

	if (env == NULL || str == NULL)
		return (true);
	key_values = split_string(str, '=');
	if (key_values == NULL || key_values[0] == NULL)
		return (return_error(key_values));
	if (i == 0)
		new_node = env;
	else
	{
		if (search_env(key_values[0], env))
			return (cahnge_env_values(env, key_values));
		new_node = ft_calloc(1, sizeof(t_env));
		if (new_node == NULL)
			return (return_error(key_values));
		get_last_env_node(env)->next = new_node;
	}
	new_node->key = key_values[0];
	new_node->value = key_values[1];
	free(key_values);
	return (false);
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

static char	**split_string(char *str, char delimiter)
{
	char	*delimiter_pos;
	char	**result;
	int		first_str_len;
	int		second_str_len;

	result = ft_calloc(3, sizeof(char *));
	if (result == NULL)
		return (NULL);
	delimiter_pos = ft_strchr(str, delimiter);
	if (delimiter_pos == NULL)
	{
		result[0] = ft_strdup(str);
		result[1] = NULL;
	}
	else
	{
		first_str_len = delimiter_pos - str;
		second_str_len = ft_strlen(str) - first_str_len - 1;
		result[0] = ft_substr(str, 0, first_str_len);
		result[1] = ft_substr(str, first_str_len + 1, second_str_len);
	}
	return (result);
}

static bool	return_error(char **key_values)
{
	free_string_double_array(key_values);
	return (true);
}
