/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:16:50 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/06 17:09:10 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	minishell_pipe(t_minishell *m_shell)
{
	t_proc	*curr;
	int		pid;
	int		status;
	int		pipe_fd[2][2];

	curr = m_shell->proc;
	while (curr)
	{
		// 単一コマンドだったらパイプしない
		if (m_shell->proc_count != 0)
		{
			if (pipe(pipe_fd[1]) < 0)
			{
				ft_putendl_fd("filed: create pipe\n", 2);
				return (true);
			}
		}
		pid = fork();
		if (pid < 0)
		{
			ft_putendl_fd("filed: create process\n", 2);
			return (true);
		}
		if (pid == 0)
		{
			printf("child process\n");
			// redirect
			exec_cmd(m_shell, curr->cmd);
		}
		curr = curr->next;
	}
	waitpid(pid, &status, 0);
	m_shell->prev_status = status;
	return (false);
}
