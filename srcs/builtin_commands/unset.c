/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:10:55 by takitaga          #+#    #+#             */
/*   Updated: 2025/03/27 14:32:36 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	error(void);

void	unset(int argc, char **argv, t_env **env)
{
	t_env	*curr;
	t_env	*prev;

	if (argc != 2)
	{
		error();
		return ;
	}
	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, argv[1]) == 0)
		{
			if (prev == NULL)
				*env = curr->next;
			else
				prev->next = curr->next;
			free_env(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

static void	error(void)
{
	ft_putendl_fd("Usage: unset [string]", 2);
}
