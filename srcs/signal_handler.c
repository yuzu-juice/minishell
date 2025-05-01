/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 21:12:57 by takitaga          #+#    #+#             */
/*   Updated: 2025/04/27 12:23:18 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_sig_flag;

void	handle_sigint(int sig)
{
	(void)sig;
	rl_on_new_line();
	ft_putendl_fd("", STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigint_pipe(int sig)
{
	(void)sig;
	g_sig_flag = 1;
	ft_putendl_fd("", STDOUT_FILENO);
}

void	set_handle_sigint(t_env *env)
{
	signal(SIGQUIT, SIG_IGN);
	if (signal(SIGINT, handle_sigint) == SIG_ERR)
	{
		perror(NULL);
		free_all_env(env);
		rl_clear_history();
		exit(EXIT_FAILURE);
	}
}

bool	set_handle_sigint_pipe(t_minishell *m_shell)
{
	if (signal(SIGINT, handle_sigint_pipe) == SIG_ERR)
	{
		perror("signal failed");
		free(m_shell->child_pids);
		m_shell->child_pids = NULL;
		return (true);
	}
	return (false);
}
