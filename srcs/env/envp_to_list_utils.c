/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_to_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:58:23 by takitaga          #+#    #+#             */
/*   Updated: 2025/03/19 15:58:59 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_value	*get_last_value_node(t_value *value);
static t_env	*get_last_env_node(t_env *env);
static void		add_value_node(t_value *value, char *str, int i);
static t_value	*values_to_list(char *str);

void	add_env_node(t_env *env, char *str, int i)
{
	char	**key_values;
	t_env	*new_node;

	key_values = ft_split(str, '=');
	if (key_values == NULL)
		return ;
	if (i == 0)
	{
		env->key = key_values[0];
		if (key_values[1] == NULL)
			env->values = values_to_list(ft_strdup(""));
		else
			env->values = values_to_list(key_values[1]);
	}
	else
	{
		new_node = ft_calloc(1, sizeof(t_env));
		if (new_node == NULL)
			return ;
		new_node->key = key_values[0];
		if (key_values[1] == NULL)
			new_node->values = values_to_list(ft_strdup(""));
		else
			new_node->values = values_to_list(key_values[1]);
		new_node->next = NULL;
		get_last_env_node(env)->next = new_node;
	}
	free(key_values);
}

static t_value	*get_last_value_node(t_value *value)
{
	t_value	*tmp;

	if (value == NULL)
		return (NULL);
	tmp = value;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
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

static void	add_value_node(t_value *value, char *str, int i)
{
	t_value	*new_node;

	if (i == 0)
	{
		value->value = str;
		value->next = NULL;
	}
	else
	{
		new_node = ft_calloc(1, sizeof(t_value));
		if (new_node == NULL)
			return ;
		new_node->value = str;
		new_node->next = NULL;
		get_last_value_node(value)->next = new_node;
	}
}

static t_value	*values_to_list(char *str)
{
	char	**values;
	int		i;
	t_value	*value;

	value = ft_calloc(1, sizeof(t_value));
	if (value == NULL)
		return (NULL);
	i = 0;
	values = ft_split(str, ':');
	free(str);
	if (values == NULL)
		return (NULL);
	if (values[0] == NULL)
	{
		value->value = ft_strdup("");
		value->next = NULL;
	}
	else
		while (values[i])
		{
			add_value_node(value, values[i], i);
			i++;
		}
	free(values);
	return (value);
}
