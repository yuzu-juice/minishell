/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:10:55 by takitaga          #+#    #+#             */
/*   Updated: 2025/03/23 12:45:09 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	error(void);

void	unset(int argc, char **argv, t_env *env)
{
	t_env	*prev;
	t_env	*tmp;

	if (argc != 2)
	{
		error();
		return ;
	}
	tmp = env;
	tmp = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, argv[1]))
		{
			prev->next = tmp->next;
			free_env(tmp);
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

static void	error(void)
{
	write(2, "Usage: unset [string]\n", 22);
}
