/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:16:50 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/01 17:23:48 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	pipe(t_minishell *minishell)
{
	t_proc	*curr;
	int		pid;
	int		status;

	curr = minishell->proc;
	while (curr)
	{
		// pipe();
		pid = fork();
		if (pid < 0)
		{
			return (true);
		}
		if (pid == 0)
		{
			exec_cmd(env, curr->cmd);
		}
		curr = curr->next;
	}
	waitpid(pid, &status, 0);
	minishell->env = status;
	return (false);
}
