/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 03:32:08 by takitaga          #+#    #+#             */
/*   Updated: 2025/04/26 14:05:16 by takitaga         ###   ########.fr       */
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
static void		kill_child_processes(t_minishell *m_shell);

bool	minishell_pipe(t_minishell *m_shell)
{
	int		last_pid;
	int		pipe_fd[2][2];
	bool	error_occurred;

	if (m_shell->proc_count == 1
		&& exec_parent_bultin_cmd(m_shell, m_shell->proc))
		return (false);
	m_shell->child_pids = ft_calloc(m_shell->proc_count, sizeof(pid_t));
	if (!m_shell->child_pids)
	{
		ft_putendl_fd("failed: malloc\n", 2);
		return (true);
	}
	m_shell->created_child_proc_count = 0;
	g_sig_flag = 0;
	if (set_handle_sigint_pipe(m_shell))
		return (free(m_shell->child_pids), true);
	last_pid = execute_pipeline(m_shell, pipe_fd);
	error_occurred = (last_pid < 0);
	wait_for_processes(m_shell, last_pid);
	set_handle_sigint(m_shell->env);
	free(m_shell->child_pids);
	m_shell->child_pids = NULL;
	return (error_occurred);
}

static int	execute_pipeline(t_minishell *m_shell, int pipe_fd[2][2])
{
	t_proc	*curr;
	int		pid;

	curr = m_shell->proc;
	while (curr)
	{
		if (g_sig_flag)
			return (kill_child_processes(m_shell), -1);
		if (curr->next && pipe(pipe_fd[CURR]) < 0)
			return (ft_putendl_fd("failed: create pipe\n", STDERR_FILENO), -1);
		pid = fork_proc(pipe_fd, m_shell, curr);
		if (pid < 0)
		{
			ft_putendl_fd("failed: fork\n", STDERR_FILENO);
			if (curr->next)
				close_pipe_fd(pipe_fd[CURR]);
			kill_child_processes(m_shell);
			return (-1);
		}
		m_shell->child_pids[m_shell->created_child_proc_count++] = pid;
		parent_process(pipe_fd, curr, m_shell->proc_count);
		curr = curr->next;
	}
	return (m_shell->child_pids[m_shell->created_child_proc_count - 1]);
}

static void	wait_for_processes(t_minishell *m_shell, int last_pid)
{
	int	status;

	if (g_sig_flag)
		m_shell->prev_status = 130;
	else if (last_pid > 0)
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

static void	kill_child_processes(t_minishell *m_shell)
{
	int	i;

	i = 0;
	while (i < m_shell->created_child_proc_count)
	{
		if (m_shell->child_pids[i] > 0)
			kill(m_shell->child_pids[i], SIGTERM);
		i++;
	}
}
