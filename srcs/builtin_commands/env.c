/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:49:16 by takitaga          #+#    #+#             */
/*   Updated: 2025/04/06 16:12:07 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	error(void);

void	env(int argc, t_minishell *m_shell)
{
	t_env	*tmp;

	if (argc != 1 || m_shell->env == NULL)
	{
		error();
		return ;
	}
	tmp = m_shell->env;
	while (tmp)
	{
		if (tmp->value != NULL)
		{
			write(1, tmp->key, ft_strlen(tmp->key));
			write(1, "=", 1);
			ft_putendl_fd(tmp->value, 1);
		}
		tmp = tmp->next;
	}
}

static void	error(void)
{
	ft_putendl_fd("Usage: env", 2);
}
