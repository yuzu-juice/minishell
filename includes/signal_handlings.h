/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlings.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 21:12:27 by takitaga          #+#    #+#             */
/*   Updated: 2025/04/22 12:20:06 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLINGS_H
# define SIGNAL_HANDLINGS_H

# include <signal.h>

void	handle_sigint(int sig);
void	handle_sigint_pipe(int sig);
void	set_handle_sigint(t_env *env);
bool	set_handle_sigint_pipe(t_minishell *m_shell);

#endif
