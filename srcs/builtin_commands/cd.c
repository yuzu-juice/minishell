/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 11:15:38 by takitaga          #+#    #+#             */
/*   Updated: 2025/04/19 21:12:47 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	error(void);
static int	return_error(char *argv);

int	cd(int argc, char **argv)
{
	if (argc != 2)
	{
		error();
		return (1);
	}
	if (ft_strncmp(argv[1], "..", 2) != 0)
	{
		if (access(argv[1], X_OK) != 0)
			return (return_error(argv[1]));
	}
	if (access(argv[1], F_OK) == 0)
	{
		if (chdir(argv[1]) == -1)
			return (return_error(argv[1]));
	}
	else
		return (return_error(argv[1]));
	return (0);
}

static void	error(void)
{
	ft_putendl_fd("Usage: cd [relative path | absolute path]", 2);
}

static int	return_error(char *argv)
{
	perror(argv);
	return (1);
}
