/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 12:23:12 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/08 17:45:29 by yohatana         ###   ########.fr       */
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

#endif
