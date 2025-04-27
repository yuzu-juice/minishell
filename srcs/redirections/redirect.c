/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:45:26 by takitaga          #+#    #+#             */
/*   Updated: 2025/04/27 00:08:02 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	setup_redirections(t_proc *proc)
{
	t_redirection	*redir;
	int				status;

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

void	free_redirection_list(t_redirection **list)
{
	t_redirection	*temp;
	t_redirection	*curr;

	if (!list || !*list)
		return ;
	curr = *list;
	while (curr)
	{
		free(curr->filename);
		temp = curr->next;
		free(curr);
		curr = temp;
	}
	*list = NULL;
}
