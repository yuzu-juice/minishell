/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 13:26:20 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/27 00:38:24 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_minishell	t_minishell;
typedef enum e_builtin		t_builtin;

// exec_cmd
void		exec_cmd(t_minishell *m_shell, t_proc *proc);
void		remove_args_quotes(char **cmd_args);

// create cmd_path
char		*create_cmd_path(char *cmd, t_minishell *m_shell);

// exec_builtin_cmd
t_builtin	resolve_builtin_cmd(char *cmd);
int			exec_builtin(char **cmd_args, \
								t_builtin cmd, \
								t_minishell *m_shell);
bool		exec_parent_bultin_cmd(t_minishell *m_shell, t_proc *proc);

#endif
