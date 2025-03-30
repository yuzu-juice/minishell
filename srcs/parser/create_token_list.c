/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:48:17 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/30 18:34:31 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_token_list(char *line)
{
	t_token	*head;
	int		index;
	bool	err_flg;

	index = 0;
	head = NULL;
	while (line[index])
	{
		if (is_split_char(line[index]))
			err_flg = create_split_token(line, &index, &head);
		else
			err_flg = create_normal_token(line, &index, &head);
		if (err_flg)
			break ;
	}
	if (err_flg)
	{
		syntax_error(&head);
		return (NULL);
	}
	return (head);
}

t_token	*create_token_node(char *word)
{
	t_token	*token;

	token = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (NULL);
	token->word = word;
	token->next = NULL;
	return (token);
}

bool	add_token_node(t_token **head, t_token *new)
{
	t_token	*temp;
	bool	err_flg;

	err_flg = false;
	if (new == NULL || head == NULL)
		return (true);
	if (*head == NULL)
		*head = new;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	return (err_flg);
}

void	free_token_list(t_token **head)
{
	t_token	*curr;
	t_token	*temp;

	if (head == NULL)
		return ;
	curr = *head;
	while (curr)
	{
		temp = curr->next;
		free(curr->word);
		free(curr);
		curr = temp;
	}
}
