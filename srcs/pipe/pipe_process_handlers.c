/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process_handlers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 04:57:30 by takitaga          #+#    #+#             */
/*   Updated: 2025/04/22 12:32:09 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parent_process(int pipe_fd[2][2], t_proc *proc, int proc_count)
{
	if (proc_count == 1)
		return ;
	if (proc->index != 0)
		close_pipe_fd(pipe_fd[PREV]);
	if (proc->next)
	{
		pipe_fd[PREV][READ] = pipe_fd[CURR][READ];
		pipe_fd[PREV][WRITE] = pipe_fd[CURR][WRITE];
	}
}

void	child_process(t_minishell *m_shell, t_proc *proc, int pipe_fd[2][2])
{
	int	redir_status;

	redir_status = setup_redirections(proc);
	if (redir_status != 0)
		exit(redir_status);
	exec_cmd(m_shell, proc, pipe_fd);
	perror("minishell: exec_cmd error");
	exit(127);
}
