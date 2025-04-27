/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:37:48 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/27 11:46:56 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	change_env_values(t_env *env, char **key_values)
{
	t_env	*old_env;

	old_env = search_env(key_values[0], env);
	free(old_env->value);
	old_env->value = ft_strdup(key_values[1]);
	free_string_double_array(key_values);
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
