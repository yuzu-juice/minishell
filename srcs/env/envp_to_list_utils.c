/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_to_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:57:41 by takitaga          #+#    #+#             */
/*   Updated: 2025/03/19 22:05:59 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_value  *get_last_value_node(t_value *value)
{
    t_value *tmp;

    tmp = value;
    while (tmp->next)
        tmp = tmp->next;
    return (tmp);
}

static t_env  *get_last_env_node(t_env *env)
{
    t_env *tmp;

    tmp = env;
    while (tmp->next)
        tmp = tmp->next;
    return (tmp);
}

static void    add_value_node(t_value *value, char *str, int i)
{
    t_value *new_node;

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

static t_value *values_to_list(char *str)
{
    char    **values;
    int     i;
    t_value *value;

    value = ft_calloc(1, sizeof(t_value));
    if (value == NULL)
        return (NULL);
    i = 0;
    values = ft_split(str, ':');
    if (values == NULL)
        return (NULL);
    while (values[i])
    {
        add_value_node(value, values[i], i);
        i++;
    }
    return (value);
}

void    add_env_node(t_env *env, char *str, int i)
{
    char    **key_values;
    t_env   *new_node;

    key_values = ft_split(str, '=');
    if (key_values == NULL)
        return ;
    if (i == 0)
    {
        env->key = key_values[0];
        env->values = values_to_list(key_values[1]);
    }
    else
    {
        new_node = ft_calloc(1, sizeof(t_env));
        if (new_node == NULL)
            return ;
        new_node->key = key_values[0];
        new_node->values = values_to_list(key_values[1]);
        new_node->next = NULL;
        get_last_env_node(env)->next = new_node;
    }
}
