/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:29:28 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/08 17:46:03 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	change_fds(t_minishell *m_shell, int proc_index, int pipe_fd[2][2])
{
	if (proc_index == 0)
	{
		close(pipe_fd[PREV][WRITE]);
		close(pipe_fd[PREV][READ]);
		close(pipe_fd[CURR][READ]);
		dup2(pipe_fd[CURR][WRITE], STDOUT_FILENO);
	}
	else if (proc_index == m_shell->proc_count - 1)
	{
		close(pipe_fd[PREV][WRITE]);
		close(pipe_fd[CURR][READ]);
		close(pipe_fd[CURR][WRITE]);
		dup2(pipe_fd[PREV][READ], STDIN_FILENO);
	}
	else
	{
		close(pipe_fd[PREV][WRITE]);
		close(pipe_fd[CURR][READ]);
		dup2(pipe_fd[PREV][READ], STDIN_FILENO);
		dup2(pipe_fd[CURR][WRITE], STDOUT_FILENO);
	}
}
