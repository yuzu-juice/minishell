/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 10:45:06 by takitaga          #+#    #+#             */
/*   Updated: 2025/04/13 13:46:00 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	error(void);

int	echo(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc == 1)
	{
		error();
		return (1);
	}
	if (argv[1][0] == '-' && argv[1][1] == 'n' && argv[1][2] == '\0')
		i++;
	else
	{
		error();
		return (1);
	}
	while (i < argc)
	{
		write(1, argv[i], ft_strlen(argv[i]));
		i++;
		if (i < argc)
			write(1, " ", 1);
	}
	return (0);
}

static void	error(void)
{
	ft_putendl_fd("Usage: echo -n [string]...", 2);
}
