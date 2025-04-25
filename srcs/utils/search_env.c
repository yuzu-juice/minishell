/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 19:43:53 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/24 14:14:19 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*search_env(char *key, t_env *env)
{
	t_env	*temp;
	char	*trim_dollar;
	t_env	*result;

	if (!key)
		return (NULL);
	temp = env;
	trim_dollar = ft_strtrim(key, "$");
	if (!trim_dollar)
		return (NULL);
	result = NULL;
	while (temp)
	{
		if (ft_strcmp(trim_dollar, temp->key) == 0)
		{
			result = temp;
			break ;
		}
		temp = temp->next;
	}
	free(trim_dollar);
	return (result);
}
