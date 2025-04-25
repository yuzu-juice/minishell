/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:57:27 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/25 13:58:56 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_digit(char *argv);

int	minishell_exit(int argc, char **argv, t_minishell *m_shell)
{
	int	status;

	status = 0;
	if (argc == 1)
	{
		write(1, "exit\n", 5);
		exit(m_shell->prev_status);
	}
	if (argc == 2)
	{
		if (is_digit(argv[1]))
		{
			ft_putstr_fd("Usage: exit [exit_status].\n", 2);
			return (2);
		}
		status = ft_atoi(argv[1]);
		write(1, "exit\n", 5);
		exit(status);
	}
	else
	{
		ft_putstr_fd("Usage: exit [exit_status]\n", 2);
		return (1);
	}
}

static bool	is_digit(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (i == 0 && argv[i] == '-')
			i++;
		if (argv[i] < '0' || argv[i] > '9')
			return (true);
		i++;
	}
	return (false);
}
