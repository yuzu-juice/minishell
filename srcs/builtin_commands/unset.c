/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:10:55 by takitaga          #+#    #+#             */
/*   Updated: 2025/04/13 13:43:01 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	error(void);

int	unset(int argc, char **argv, t_minishell *m_shell)
{
	t_env	*curr;
	t_env	*prev;

	if (argc != 2)
	{
		error();
		return (1);
	}
	curr = m_shell->env;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, argv[1]) == 0)
		{
			if (prev == NULL)
				m_shell->env = curr->next;
			else
				prev->next = curr->next;
			free_env(curr);
			return (1);
		}
		prev = curr;
		curr = curr->next;
	}
	return (0);
}

static void	error(void)
{
	ft_putendl_fd("Usage: unset [string]", 2);
}
