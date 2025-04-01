/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:57:27 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/01 15:12:43 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	minishell_exit(int argc, char **argv)
{
	int	status;

	status = 0;
	if (argc == 1)
	{
		exit(0);
	}
	if (argc == 2)
	{
		status = ft_atoi(argv[1]);
		exit(status);
	}
	else
	{
		ft_putstr_fd("Usage: exit [exit_status]", 2);
	}
}
