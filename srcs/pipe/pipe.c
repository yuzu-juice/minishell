/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 03:32:08 by takitaga          #+#    #+#             */
/*   Updated: 2025/04/23 14:54:39 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int		fork_proc(
					int pipe_fd[2][2],
					t_minishell *m_shell,
					t_proc *curr
					);
static int		execute_pipeline(t_minishell *m_shell, int pipe_fd[2][2]);
static void		wait_for_processes(t_minishell *m_shell, int last_pid);

bool	minishell_pipe(t_minishell *m_shell)
{
	int		last_pid;
	int		pipe_fd[2][2];

	if (m_shell->proc_count == 1
		&& exec_parent_bultin_cmd(m_shell, m_shell->proc))
		return (false);
	last_pid = execute_pipeline(m_shell, pipe_fd);
	if (last_pid < 0)
		return (true);
	wait_for_processes(m_shell, last_pid);
	return (false);
}

static int	execute_pipeline(t_minishell *m_shell, int pipe_fd[2][2])
{
	t_proc	*curr;
	int		pid;
	int		last_pid;

	curr = m_shell->proc;
	last_pid = -1;
	while (curr)
	{
		if (curr->next)
		{
			if (pipe(pipe_fd[CURR]) < 0)
				return (
					ft_putendl_fd("failed: create pipe\n", STDERR_FILENO),
					-1);
		}
		pid = fork_proc(pipe_fd, m_shell, curr);
		if (pid < 0)
			return (
				ft_putendl_fd("failed: create process\n", STDERR_FILENO),
				-1);
		last_pid = pid;
		parent_process(pipe_fd, curr, m_shell->proc_count);
		curr = curr->next;
	}
	return (last_pid);
}

static void	wait_for_processes(t_minishell *m_shell, int last_pid)
{
	int	status;

	if (last_pid > 0)
	{
		waitpid(last_pid, &status, 0);
		if (WIFEXITED(status))
			m_shell->prev_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			m_shell->prev_status = 128 + WTERMSIG(status);
		else
			m_shell->prev_status = status;
	}
	while (wait(NULL) > 0)
		;
}

static int	fork_proc(int pipe_fd[2][2], t_minishell *m_shell, t_proc *curr)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		child_process(m_shell, curr, pipe_fd);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		return (-1);
	return (pid);
}
