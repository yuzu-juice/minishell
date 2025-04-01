/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:42:27 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/01 14:19:00 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_env(t_env **env);

void	export(int argc, char **argv, t_env **env)
{
	if (argc == 1)
	{
		print_env(env);
	}
	else if (argc == 2)
	{
		printf("argv[0] %s\n", argv[0]);
		printf("argv[1] %s\n", argv[1]);
		printf("argv[2] %s\n", argv[2]);
		add_env_node(*env, argv[1], 1);
		print_env(env);
	}
	else
	{
		ft_putendl_fd("too many args", 2);
	}
}

static void	print_env(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		printf("print_env() : tmp %p\n", tmp);
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
