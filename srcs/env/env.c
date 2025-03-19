/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:55:14 by takitaga          #+#    #+#             */
/*   Updated: 2025/03/19 22:10:50 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env   *envp_to_list(char **envp)
{
    int     i;
    t_env   *env;

    env = ft_calloc(1, sizeof(t_env));
    if (env == NULL)
        return (NULL);
    i = 0;
    while (envp[i])
    {
        add_env_node(env, envp[i], i);
        i++;
    }
    return (env);
}

char   **list_to_envp(t_env *env)
{

    return (NULL);
}
