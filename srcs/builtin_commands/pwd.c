/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:03:10 by takitaga          #+#    #+#             */
/*   Updated: 2025/03/20 14:56:18 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

static void	error(void)
{
	write(2, "Usage: pwd\n", 11);
}

void	pwd(int argc)
{
  char *pwd;

  if (argc != 1)
  {
    error();
    return ;
  }
  pwd = getcwd(NULL, 0);
  write(1, pwd, ft_strlen(pwd));
  write(1, "\n", 1);
  free(pwd);
}
