/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 13:26:20 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/13 14:16:58 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_minishell	t_minishell;
typedef enum e_builtin		t_builtin;

// exec_cmd
void		exec_cmd(t_minishell *m_shell, \
	char *cmd, \
	int proc_index, \
	int pipe_fd[2][2]);
void		remove_args_quotes(char **cmd_args);

// create cmd_path
char		*create_cmd_path(char *cmd);

// exec_builtin_cmd
t_builtin	resolve_builtin_cmd(char *cmd);
int			exec_builtin(char **cmd_args, \
								t_builtin cmd, \
								t_minishell *m_shell);
bool		exec_parent_bultin_cmd(t_minishell *m_shell, t_proc *proc);

#endif
