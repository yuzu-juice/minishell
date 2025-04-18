/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:16:50 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/18 16:26:33 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void		parent_process(int pipe_fd[2][2], \
							t_proc *proc, \
							int proc_count);
static void		chiled_process(t_minishell *m_shell, \
							t_proc *proc, \
							int pipe_fd[2][2]);
static bool		return_prpcess_err(char *str);
static int		fork_proc(int pipe_fd[2][2], \
						t_minishell *m_shell, \
						t_proc *curr);

bool	minishell_pipe(t_minishell *m_shell)
{
	t_proc	*curr;
	int		pid;
	int		pipe_fd[2][2];

	if (exec_parent_bultin_cmd(m_shell, m_shell->proc))
		return (false);
	curr = m_shell->proc;
	while (curr)
	{
		if (m_shell->proc_count > 1)
		{
			if (pipe(pipe_fd[CURR]) < 0)
				return_prpcess_err("failed: create pipe\n");
		}
		pid = fork_proc(pipe_fd, m_shell, curr);
		if (pid < 0)
			return_prpcess_err("failed: create process\n");
		curr = curr->next;
	}
	waitpid(pid, &(m_shell->prev_status), 0);
	wait(0);
	m_shell->prev_status = WEXITSTATUS(m_shell->prev_status);
	return (false);
}

static int	fork_proc(int pipe_fd[2][2], t_minishell *m_shell, t_proc *curr)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		chiled_process(m_shell, curr, pipe_fd);
	else
		parent_process(pipe_fd, curr, m_shell->proc_count);
	return (pid);
}

static bool	return_prpcess_err(char *str)
{
	write(2, str, ft_strlen(str));
	return (true);
}

static void	parent_process(int pipe_fd[2][2], \
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

static void	chiled_process(t_minishell *m_shell, \
						t_proc *proc, \
						int pipe_fd[2][2])
{
	// exec_cmd(m_shell, proc->cmd, proc->index, pipe_fd);
	exec_cmd(m_shell, proc, pipe_fd);
}
