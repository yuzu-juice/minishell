/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:37:48 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/22 17:52:51 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	cahnge_env_values(t_env *env, char **key_values)
{
	t_env	*old_env;

	old_env = search_env(key_values[0], env);
	free(old_env->value);
	old_env->value = key_values[1];
	return (false);
}

bool	validation_env_key(char *key)
{
	int	i;

	i = 0;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
		{
			return (true);
		}
		i++;
	}
	return (false);
}
