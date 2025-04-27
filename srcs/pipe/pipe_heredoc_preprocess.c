/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_heredoc_preprocess.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 00:01:15 by takitaga          #+#    #+#             */
/*   Updated: 2025/04/27 00:12:39 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	process_heredocs_for_proc(t_proc *proc);

int	preprocess_all_heredocs_in_pipeline(t_proc *proc_list)
{
	t_proc	*curr_proc;

	curr_proc = proc_list;
	while (curr_proc)
	{
		if (process_heredocs_for_proc(curr_proc) == -1)
			return (1);
		curr_proc = curr_proc->next;
	}
	return (0);
}

static int	process_heredocs_for_proc(t_proc *proc)
{
	t_redirection	*redir;

	redir = proc->redir;
	while (redir)
	{
		if (redir->type == HEREDOC)
		{
			if (create_heredoc_file(redir))
			{
				perror("Error creating heredoc file");
				return (1);
			}
		}
		redir = redir->next;
	}
	return (0);
}
