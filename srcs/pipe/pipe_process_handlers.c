/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process_handlers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 04:57:30 by takitaga          #+#    #+#             */
/*   Updated: 2025/04/27 12:25:56 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	setup_child_pipe_input(t_proc *proc, int pipe_fd[2][2]);
static void	setup_child_pipe_output(t_proc *proc, int pipe_fd[2][2]);

void	parent_process(int pipe_fd[2][2], t_proc *proc, int proc_count)
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
}

void	child_process(t_minishell *m_shell, t_proc *proc, int pipe_fd[2][2])
{
	int	redir_status;

	signal(SIGQUIT, SIG_DFL);
	setup_child_pipe_input(proc, pipe_fd);
	setup_child_pipe_output(proc, pipe_fd);
	redir_status = setup_redirections(proc);
	if (redir_status != 0)
		exit(redir_status);
	exec_cmd(m_shell, proc);
	exit(0);
}

static void	setup_child_pipe_input(t_proc *proc, int pipe_fd[2][2])
{
	if (proc->index != 0)
	{
		close(pipe_fd[PREV][WRITE]);
		if (dup2(pipe_fd[PREV][READ], STDIN_FILENO) == -1)
		{
			perror("minishell: dup2 pipe read");
			close(pipe_fd[PREV][READ]);
			exit(EXIT_FAILURE);
		}
		close(pipe_fd[PREV][READ]);
	}
}

static void	setup_child_pipe_output(t_proc *proc, int pipe_fd[2][2])
{
	if (proc->next)
	{
		close(pipe_fd[CURR][READ]);
		if (dup2(pipe_fd[CURR][WRITE], STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2 pipe write");
			close(pipe_fd[CURR][WRITE]);
			exit(EXIT_FAILURE);
		}
		close(pipe_fd[CURR][WRITE]);
	}
}
