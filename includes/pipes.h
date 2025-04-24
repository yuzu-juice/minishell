/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 12:23:12 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/22 12:31:32 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

# define PREV 0
# define CURR 1
# define READ 0
# define WRITE 1

typedef struct s_minishell	t_minishell;

bool	minishell_pipe(t_minishell *minishell);
void	change_fds(t_minishell *m_shell, int proc_index, int pipe_fd[2][2]);
void	parent_process(int pipe_fd[2][2], t_proc *proc, int proc_count);
void	child_process(t_minishell *m_shell, t_proc *proc, int pipe_fd[2][2]);
void	close_pipe_fd(int pipe_fd[2]);

#endif
