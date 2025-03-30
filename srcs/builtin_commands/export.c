/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:42:27 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/30 19:48:04 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	export(int argc, char **argv, t_env **env)
{
	t_env	*tmp;

	if (argc == 1)
	{
		tmp = *env;
		while (tmp)
		{
			if (tmp->value == NULL)
			{
				write(1, tmp->key, ft_strlen(tmp->key));
				write(1, "\n", 1);
			}
			else
			{
				write(1, tmp->key, ft_strlen(tmp->key));
				write(1, "=", 1);
				write(1, tmp->value, ft_strlen(tmp->value));
				write(1, "\n", 1);
			}
			tmp = tmp->next;
		}
	}
	else if (argc == 2)
	{
		printf("argv[2] %s\n", argv[1]);
		add_env_node(*env, argv[1], 1);
	}
	else
	{
		ft_putendl_fd("args is only 1", 2) ;
	}
}
