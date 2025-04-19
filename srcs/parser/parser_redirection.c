/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:01:36 by takitaga          #+#    #+#             */
/*   Updated: 2025/04/19 04:30:18 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_redirection(char *word)
{
	if (ft_strcmp(word, "<") == 0)
		return (true);
	if (ft_strcmp(word, ">") == 0)
		return (true);
	if (ft_strcmp(word, "<<") == 0)
		return (true);
	if (ft_strcmp(word, ">>") == 0)
		return (true);
	return (false);
}

t_redirection_type	get_redirection_type(char *word)
{
	if (ft_strcmp(word, "<") == 0)
		return (INPUT);
	if (ft_strcmp(word, ">") == 0)
		return (OUTPUT);
	if (ft_strcmp(word, "<<") == 0)
		return (HEREDOC);
	if (ft_strcmp(word, ">>") == 0)
		return (APPEND);
	return (-1);
}

bool	add_redirection(t_proc *proc, t_redirection_type type, char *filename)
{
	t_redirection	*new;
	t_redirection	*curr;

	if (!proc || !filename)
		return (true);
	new = (t_redirection *)ft_calloc(sizeof(t_redirection), 1);
	if (!new)
		return (true);
	new->type = type;
	new->filename = ft_strdup(filename);
	if (!new->filename)
		return (free(new), true);
	new->next = NULL;
	if (!proc->redir)
		proc->redir = new;
	else
	{
		curr = proc->redir;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
	return (false);
}
