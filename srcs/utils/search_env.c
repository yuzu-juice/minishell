/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 19:43:53 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/24 20:13:34 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*search_env(char *key, t_env *env)
{
	t_env	*temp;
	char	*trim_dollar;

	temp = env;
	trim_dollar = ft_strtrim(key, "$");
	if (!key)
		return (NULL);
	while (temp)
	{
		if (ft_strcmp(trim_dollar, temp->key) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}
