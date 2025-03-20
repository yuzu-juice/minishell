/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:55:14 by takitaga          #+#    #+#             */
/*   Updated: 2025/03/19 15:48:02 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*envp_to_list(char **envp)
{
	int		i;
	t_env	*env;

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

char	**list_to_envp(t_env *env)
{
	t_env	*tmp;
	char	**envp;
	int		i;
	
	envp = ft_calloc(get_node_count(env), sizeof(char *));
	if (envp == NULL)
		return (NULL);
	tmp = env;
	i = 0;
	while (tmp)
	{
		envp[i] = ft_strjoin(tmp->key, "=");
		if (envp[i] == NULL)
			return (NULL);
		envp[i] = ft_strjoin(envp[i], create_values_str(tmp->values));
		printf("envp[%d]: %s\n", i, envp[i]);
		if (envp[i] == NULL)
			return (NULL);
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}
