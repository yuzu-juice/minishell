/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:03:10 by takitaga          #+#    #+#             */
/*   Updated: 2025/04/19 19:05:01 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	error(void);

int	pwd(int argc)
{
	char	*pwd;

	if (argc != 1)
	{
		error();
		return (1);
	}
	pwd = getcwd(NULL, 0);
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (0);
}

static void	error(void)
{
	ft_putendl_fd("Usage: pwd", 2);
}
