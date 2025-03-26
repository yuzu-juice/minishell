/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:45:26 by takitaga          #+#    #+#             */
/*   Updated: 2025/03/26 12:26:20 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	output(t_proc *process, t_redirection *redir, t_env *env);

void	redirect(t_proc *process, t_redirection *redir, t_env *env)
{
	while (redir)
	{
		if (redir->type == OUTPUT)
			output(process, redir, env);
		redir = redir->next;
	}
}

static void	output(t_proc *process, t_redirection *redir, t_env *env)
{
	int	outfile_fd;

	outfile_fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd < 0)
	{
		perror("open");
		return ;
	}
	dup2(outfile_fd, STDOUT_FILENO);
	if (redir->next == NULL)
		exec_cmd(&env, process->cmd);
	close(outfile_fd);
}
