/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:42:27 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/06 16:13:30 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_env(t_minishell *m_shell);

void	export(int argc, char **argv, t_minishell *m_shell)
{
	if (argc == 1)
	{
		print_env(m_shell);
	}
	else if (argc == 2)
	{
		add_env_node(m_shell->env, argv[1], 1);
	}
	else
	{
		ft_putstr_fd("Usage: export [key=value]\n", 2);
	}
}

static void	print_env(t_minishell *m_shell)
{
	t_env	*tmp;

	tmp = m_shell->env;
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
