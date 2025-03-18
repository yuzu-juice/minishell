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

void	echo(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc == 1)
		return ;
	while (i < argc)
	{
		write(1, argv[i], ft_strlen(argv[i]));
		write(1, " ", 1);
		i++;
	}
}

// int main(int argc, char **argv)
// {
//     echo(argc, argv);
//     return (0);
// }
