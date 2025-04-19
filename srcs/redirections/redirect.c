/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:45:26 by takitaga          #+#    #+#             */
/*   Updated: 2025/04/19 13:12:14 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	process_all_heredocs(t_proc *proc);

int	setup_redirections(t_proc *proc)
{
	t_redirection	*redir;
	int				status;

	status = process_all_heredocs(proc);
	if (status != 0)
		return (status);
	redir = proc->redir;
	status = 0;
	while (redir && status == 0)
	{
		if (redir->type == INPUT)
			status = handle_input_redir(redir);
		else if (redir->type == HEREDOC)
			status = handle_heredoc_redir(redir);
		else if (redir->type == OUTPUT)
			status = handle_output_redir(redir);
		else if (redir->type == APPEND)
			status = handle_append_redir(redir);
		redir = redir->next;
	}
	return (status);
}

static int	process_all_heredocs(t_proc *proc)
{
	t_redirection	*redir;
	int				status;

	redir = proc->redir;
	status = 0;
	while (redir)
	{
		if (redir->type == HEREDOC)
		{
			status = create_heredoc_file(redir);
			if (status != 0)
			{
				return (status);
			}
		}
		redir = redir->next;
	}
	return (0);
}
