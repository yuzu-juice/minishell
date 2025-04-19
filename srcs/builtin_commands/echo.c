/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 10:45:06 by takitaga          #+#    #+#             */
/*   Updated: 2025/04/19 18:52:41 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	echo(int argc, char **argv)
{
	int		i;
	bool	option_flg;

	i = 1;
	option_flg = false;
	if (argc == 1)
	{
		write(1, "\n", 1);
		return (0);
	}
	if (argv[1][0] == '-' && argv[1][1] == 'n' && argv[1][2] == '\0')
	{
		option_flg = true;
		i++;
	}
	while (i < argc)
	{
		write(1, argv[i], ft_strlen(argv[i]));
		i++;
		if (i < argc)
			write(1, " ", 1);
	}
	if (option_flg == false)
		write(1, "\n", 1);
	return (0);
}
