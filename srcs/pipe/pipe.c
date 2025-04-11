/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:16:50 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/11 17:14:45 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		parent_process(int pipe_fd[2][2], \
							t_proc *proc, \
							int proc_count);
void		chiled_process(t_minishell *m_shell, \
							t_proc *proc, \
							int pipe_fd[2][2]);
static bool	return_prpcess_err(char *str);

bool	minishell_pipe(t_minishell *m_shell)
{
	t_proc	*curr;
	int		pid;
	int		pipe_fd[2][2];

	curr = m_shell->proc;
	while (curr)
	{
		if (m_shell->proc_count > 1)
		{
			if (pipe(pipe_fd[CURR]) < 0)
				return_prpcess_err("failed: create pipe\n");
		}
		pid = fork();
		if (pid < 0)
			return_prpcess_err("failed: create process\n");
		if (pid == 0)
			chiled_process(m_shell, curr, pipe_fd);
		else
			parent_process(pipe_fd, curr, m_shell->proc_count);
		curr = curr->next;
	}
	waitpid(pid, &(m_shell->prev_status), 0);
	wait(0);
	m_shell->prev_status = WEXITSTATUS(m_shell->prev_status);
	return (false);
}

static bool	return_prpcess_err(char *str)
{
	write(2, str, ft_strlen(str));
	return (true);
}

void	parent_process(int pipe_fd[2][2], \
						t_proc *proc, \
						int proc_count)
{
	if (proc_count == 1)
		return ;
	if (proc->index != 0)
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
		close(pipe_fd[PREV][READ]);
		close(pipe_fd[PREV][WRITE]);
		close(pipe_fd[CURR][READ]);
		close(pipe_fd[CURR][WRITE]);
	}
}

void	chiled_process(t_minishell *m_shell, \
						t_proc *proc, \
						int pipe_fd[2][2])
{
	exec_cmd(m_shell, proc->cmd, proc->index, pipe_fd);
}
