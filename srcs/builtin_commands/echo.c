/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 10:45:06 by takitaga          #+#    #+#             */
/*   Updated: 2025/03/18 21:35:10 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	error(void)
{
	write(2, "Usage: echo -n [string]...\n", 27);
}

void	echo(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc == 1)
	{
		error();
		return ;
	}
	if (argv[1][0] == '-' &&  argv[1][1] == 'n' && argv[1][2] == '\0')
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

// int main(int argc, char **argv)
// {
//     echo(argc, argv);
//     return (0);
// }
