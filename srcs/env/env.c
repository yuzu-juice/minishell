/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:55:14 by takitaga          #+#    #+#             */
/*   Updated: 2025/04/06 13:16:35 by takitaga         ###   ########.fr       */
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
	char	*temp;

	envp = ft_calloc(get_node_count(env) + 1, sizeof(char *));
	if (envp == NULL)
		return (NULL);
	tmp = env;
	i = 0;
	while (tmp)
	{
		temp = ft_strjoin(tmp->key, "=");
		if (temp == NULL)
			return (NULL);
		envp[i] = ft_strjoin(temp, tmp->value);
		free(temp);
		if (envp[i] == NULL)
			return (NULL);
		tmp = tmp->next;
		i++;
	}
	return (envp);
}

void	free_env(t_env *env)
{
	if (env == NULL)
		return ;
	free(env->key);
	free(env->value);
	free(env);
}
