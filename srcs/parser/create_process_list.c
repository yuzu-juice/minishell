/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 05:05:14 by takitaga          #+#    #+#             */
/*   Updated: 2025/04/20 14:29:21 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool		handle_redirection_token(
					t_token **curr_token_ptr,
					t_proc **list);
static bool		token_to_cmd(
					t_token **curr_token_ptr,
					t_token *prev,
					t_proc **list);
static bool		handle_pipe_logic(t_token *prev, t_token *curr, t_proc **list);

t_proc	*create_process_list(t_token **head)
{
	t_proc	*list;
	t_token	*curr;
	t_token	*prev;
	bool	err_flg;

	list = NULL;
	err_flg = false;
	curr = *head;
	prev = NULL;
	while (curr)
	{
		err_flg = token_to_cmd(&curr, prev, &list);
		if (err_flg)
			break ;
		prev = curr;
		curr = curr->next;
	}
	if (err_flg)
		return (free_proc_list(&list));
	return (list);
}

static bool	handle_redirection_token(t_token **curr_token_ptr, t_proc **list)
{
	t_token				*curr;
	t_token				*filename_token;
	t_proc				*last_proc;
	t_redirection_type	redir_type;

	curr = *curr_token_ptr;
	filename_token = curr->next;
	if (filename_token == NULL || !filename_token->word
		|| is_redirection(filename_token->word)
		|| ft_strcmp(filename_token->word, "|") == 0)
	{
		syntax_error(NULL);
		return (true);
	}
	last_proc = get_last_proc(list);
	if (!last_proc)
		return (true);
	redir_type = get_redirection_type(curr->word);
	if (add_redirection(last_proc, redir_type, filename_token->word))
		return (true);
	*curr_token_ptr = filename_token;
	return (false);
}

static bool	handle_pipe_logic(t_token *prev, t_token *curr, t_proc **list)
{
	if (validation_pipe(prev, curr->next, list))
	{
		syntax_error(NULL);
		return (true);
	}
	return (false);
}

static bool	token_to_cmd(t_token **curr_token_ptr, t_token *prev, t_proc **list)
{
	t_token	*curr;
	bool	is_new_proc;

	curr = *curr_token_ptr;
	is_new_proc = (prev == NULL
			|| (prev->word && ft_strcmp(prev->word, "|") == 0));
	if (*list == NULL && (!curr->word || ft_strcmp(curr->word, "|") != 0))
	{
		if (add_proc_list(list, create_proc_node(NULL)))
			return (true);
		is_new_proc = false;
	}
	if (curr->word && ft_strcmp(curr->word, "|") == 0)
		return (handle_pipe_logic(prev, curr, list));
	else if (curr->word && is_redirection(curr->word))
	{
		if (*list == NULL || get_last_proc(list) == NULL)
			return (true);
		return (handle_redirection_token(curr_token_ptr, list));
	}
	else
	{
		return (add_to_cmd(list, curr->word, is_new_proc));
	}
}
