/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:03:10 by takitaga          #+#    #+#             */
/*   Updated: 2025/03/19 19:22:04 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

static void	error(void)
{
	write(2, "Usage: pwd\n", 11);
}

void	pwd(int argc, char **envp)
{
    int i;

    i = 0;
    if (argc != 1)
    {
      error();
      return ;
    }
}
