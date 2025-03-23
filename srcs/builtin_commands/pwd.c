/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:03:10 by takitaga          #+#    #+#             */
/*   Updated: 2025/03/23 11:49:53 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

static void	error(void);

void	pwd(int argc)
{
	char	*pwd;

	if (argc != 1)
	{
		error();
		return ;
	}
	pwd = getcwd(NULL, 0);
	printf("%s\n",pwd);
	free(pwd);
}

static void	error(void)
{
	write(2, "Usage: pwd\n", 11);
}
