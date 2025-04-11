/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:16:50 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/11 16:06:58 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parent_process(int pipe_fd[2][2], int index, t_proc *proc, int proc_count);
void	chiled_process(t_minishell *m_shell, t_proc *proc, int index, int pipe_fd[2][2]);
static bool	return_prpcess_err(char *str);


/*
	まずは単体パイプを完成させよう->invaled readなん？
	・ls | ls
	・ls | cat
*/
bool	minishell_pipe(t_minishell *m_shell)
{
	t_proc	*curr;
	int		pid;
	int		pipe_fd[2][2];
	int		index;

	curr = m_shell->proc;
	index = 0;
	while (curr)
	{
		printf("m_shell->proc_count %d\n", m_shell->proc_count);
		if (m_shell->proc_count > 1)
		{
			if (pipe(pipe_fd[CURR]) < 0)
				return_prpcess_err("failed: create pipe\n");
		}
		pid = fork();
		if (pid < 0)
			return_prpcess_err("failed: create process\n");
		if (pid == 0)
			chiled_process(m_shell, curr, index, pipe_fd);
		else
			parent_process(pipe_fd, index, curr, m_shell->proc_count);
		waitpid(pid, &(m_shell->prev_status), 0);
		curr = curr->next;
		index++;
	}
	m_shell->prev_status = WEXITSTATUS(m_shell->prev_status);
	return (false);
}

static bool	return_prpcess_err(char *str)
{
	write(2, str, ft_strlen(str));
	return (true);
}

void	parent_process(int pipe_fd[2][2], int index, t_proc *proc, int proc_count)
{

	(void)index;
	if (proc_count == 1)
		return ;
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

void	chiled_process(t_minishell *m_shell, t_proc *proc, int index, int pipe_fd[2][2])
{
	// redirect
	exec_cmd(m_shell, proc->cmd, index, pipe_fd);
}
