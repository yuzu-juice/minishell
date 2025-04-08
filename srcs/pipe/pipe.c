/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:16:50 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/08 17:30:46 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parent_process(int pipe_fd[2][2], int index, t_proc *proc);

bool	minishell_pipe(t_minishell *m_shell)
{
	t_proc	*curr;
	int		pid;
	int		status;
	int		pipe_fd[2][2];
	int		index;

	curr = m_shell->proc;
	index = 0;
	while (curr)
	{
		if (m_shell->proc_count != 0)
		{
			if (pipe(pipe_fd[CURR]) < 0)
			{
				ft_putendl_fd("failed: create pipe\n", 2);
				return (true);
			}
		}
		pid = fork();
		if (pid < 0)
		{
			ft_putendl_fd("failed: create process\n", 2);
			return (true);
		}
		if (pid == 0)
		{
			exec_cmd(m_shell, curr->cmd, index, pipe_fd);
		}
		else
			parent_process(pipe_fd, index, curr);
		curr = curr->next;
		index++;
	}
	waitpid(pid, &(m_shell->prev_status), 0);
	wait(&status);
	m_shell->prev_status = WEXITSTATUS(m_shell->prev_status);
	return (false);
}

void	parent_process(int pipe_fd[2][2], int index, t_proc *proc)
{
	if (index != 0)
	{
		close(pipe_fd[PREV][READ]);
		close(pipe_fd[PREV][WRITE]);
	}
	if (proc->next)
	{
		pipe_fd[PREV][READ] = pipe_fd[CURR][READ];
		pipe_fd[PREV][WRITE] = pipe_fd[CURR][WRITE];
	}
	else
	{
		close(pipe_fd[CURR][READ]);
		close(pipe_fd[CURR][WRITE]);
	}
}
