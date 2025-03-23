/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 11:15:38 by takitaga          #+#    #+#             */
/*   Updated: 2025/03/23 11:53:26 by takitaga         ###   ########.fr       */
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
    if (chdir(argv[1]) == -1)
        perror(argv[1]);
}

static void	error(void)
{
	write(2, "Usage: cd [relative path | absolute path]\n", 42);
}
