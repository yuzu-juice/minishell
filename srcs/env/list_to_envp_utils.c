/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_envp_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:05:45 by takitaga          #+#    #+#             */
/*   Updated: 2025/03/19 15:28:48 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_node_count(t_env *env)
{
	int		count;
	t_env	*tmp;

	count = 0;
	tmp = env;
	while (tmp->next)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

char	*create_values_str(t_value *values)
{
	t_value	*tmp;
	char	*str;

	tmp = values;
	str = tmp->value;
	if (str == NULL)
		return (NULL);
	while (tmp->next)
	{
		str = ft_strjoin(str, tmp->value);
		if (str == NULL)
			return (NULL);
		str = ft_strjoin(str, ":");
		if (str == NULL)
			return (NULL);
		tmp = tmp->next;
	}
	return (str);
}
