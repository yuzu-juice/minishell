/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:49:16 by takitaga          #+#    #+#             */
/*   Updated: 2025/03/23 12:58:44 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	error(void);

void	env(int argc, t_env *env)
{
	t_env   *tmp;

	if (argc != 1)
	{
		error();
		return ;
	}
	tmp = env;
	while (tmp)
	{
		if (tmp->value == NULL)
			printf("%s=\n", tmp->key);
		else
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

static void	error(void)
{
	write(2, "Usage: env\n", 11);
}
