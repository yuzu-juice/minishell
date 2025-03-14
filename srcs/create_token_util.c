/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:10:32 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/14 15:43:52 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

char	*create_token_word(int start, int end, char *line)
{
	char	*word;

	word = ft_substr(line, start, end - start);
	if (!word)
		return (NULL);
	return (word);
}

t_token	*create_token_node(char *word)
{
	t_token	*token;

	token = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (NULL); // TODO error
	token->word = word;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **head, t_token *new)
{
	t_token	*temp;

	if (head == NULL || *head == NULL)
	{
		*head = new;
	}
	else
	{
		temp = *head;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = new;
	}
}
