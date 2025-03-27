/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 11:15:38 by takitaga          #+#    #+#             */
/*   Updated: 2025/03/27 14:32:04 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	error(void);

void	cd(int argc, char **argv)
{
	if (argc != 2)
	{
		error();
		return ;
	}
	if (access(argv[1], F_OK) == 0)
	{
		if (chdir(argv[1]) == -1)
			perror(argv[1]);
	}
	else
		perror(argv[1]);
}

static void	error(void)
{
	ft_putendl_fd("Usage: cd [relative path | absolute path]", 2);
}
