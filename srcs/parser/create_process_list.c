/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 13:03:04 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/30 18:34:38 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_proc	*create_proc_node(char *word);
static bool		add_proc_list(t_proc **list, t_proc *new);
static bool		add_to_cmd(t_proc **list, char *word, bool is_new_proc);
static bool		token_to_cmd(t_token *curr, t_token *prev, t_proc **list);

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
	head = NULL;
	while (curr)
	{
		err_flg = token_to_cmd(curr, prev, &list);
		if (err_flg)
			break ;
		prev = curr;
		curr = curr->next;
	}
	if (err_flg)
		return (free_proc_list(&list));
	return (list);
}

static t_proc	*create_proc_node(char *word)
{
	t_proc	*proc;

	proc = (t_proc *)ft_calloc(sizeof(t_proc), 1);
	if (!proc)
		return (NULL);
	proc->cmd = word;
	proc->redir = NULL;
	proc->next = NULL;
	return (proc);
}

static bool	add_to_cmd(t_proc **list, char *word, bool is_new_proc)
{
	t_proc	*curr;
	char	*temp;
	bool	err_flg;

	err_flg = false;
	curr = get_last_proc(list);
	if (is_new_proc)
		err_flg = add_proc_list(list, create_proc_node(word));
	else
	{
		curr = get_last_proc(list);
		if (curr->cmd)
			err_flg = add_space(curr);
		if (err_flg)
			return (true);
		temp = ft_strjoin(curr->cmd, word);
		if (!temp)
			return (true);
		free(curr->cmd);
		curr->cmd = temp;
	}
	return (false);
}

static bool	add_proc_list(t_proc **list, t_proc *new)
{
	t_proc	*temp;

	if (!new)
		return (true);
	if (*list == NULL)
	{
		*list = new;
	}
	else
	{
		temp = *list;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = new;
	}
	return (false);
}

static bool	token_to_cmd(t_token *curr, t_token *prev, t_proc **list)
{
	bool	err_flg;
	bool	is_new_proc;

	err_flg = false;
	is_new_proc = false;
	if (prev == NULL || ft_strcmp(prev->word, "|") == 0)
		is_new_proc = true;
	else
		is_new_proc = false;
	if (ft_strcmp(curr->word, "|") == 0)
		err_flg = validation_pipe(prev, curr->next);
	else
		err_flg = add_to_cmd(list, curr->word, is_new_proc);
	return (err_flg);
}
