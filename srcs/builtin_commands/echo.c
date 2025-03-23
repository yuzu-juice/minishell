/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 10:45:06 by takitaga          #+#    #+#             */
/*   Updated: 2025/03/23 11:50:29 by takitaga         ###   ########.fr       */
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
		printf("%s", argv[i]);
		i++;
		if (i < argc)
			printf(" ");
	}
}

static void	error(void)
{
	write(2, "Usage: echo -n [string]...\n", 27);
}
