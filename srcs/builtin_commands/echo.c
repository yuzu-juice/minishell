/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 10:45:06 by takitaga          #+#    #+#             */
/*   Updated: 2025/03/20 14:58:02 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	error(void);

void	echo(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc == 1)
	{
		error();
		return ;
	}
	if (argv[1][0] == '-' && argv[1][1] == 'n' && argv[1][2] == '\0')
		i++;
	else
	{
		error();
		return ;
	}
	while (i < argc)
	{
		write(1, argv[i], ft_strlen(argv[i]));
		i++;
		if (i < argc)
			write(1, " ", 1);
	}
}

static void	error(void)
{
	write(2, "Usage: echo -n [string]...\n", 27);
}
