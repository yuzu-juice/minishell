/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 11:15:38 by takitaga          #+#    #+#             */
/*   Updated: 2025/04/13 13:38:45 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	error(void);

int	cd(int argc, char **argv)
{
	if (argc != 2)
	{
		error();
		return (1);
	}
	if (access(argv[1], F_OK) == 0)
	{
		if (chdir(argv[1]) == -1)
			perror(argv[1]);
	}
	else
	{
		perror(argv[1]);
		return (1);
	}
	return (0);
}

static void	error(void)
{
	ft_putendl_fd("Usage: cd [relative path | absolute path]", 2);
}
