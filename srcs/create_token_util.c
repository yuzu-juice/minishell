/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:10:32 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/16 15:58:25 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

bool	create_token_word(int *start, char *line, t_token **head)
{
	char	*word;
	int		j;
	int		len;
	bool	err_flg;

	err_flg = false;
	len = (int)ft_strlen(line);
	j = *start + 1;
	while (!is_split_char(line[j]) && !is_quart(line[j]) && j < len)
		j++;
	word = ft_substr(line, *start, j - *start);
	if (!word)
		return (true);
	if (*start == 0 || is_split_char(line[*start - 1]))
		err_flg = add_token(head, create_token_node(word));
	else
		err_flg = add_current_token(word, head);
	*start = j;
	return (err_flg);
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

bool	add_token(t_token **head, t_token *new)
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

bool	is_split_char(char c)
{
	if (c == ' ' || c == '|' || c == '\t' || c == '\n' || c == '>' || c == '<')
		return (true);
	return (false);
}

bool	is_quart(char c)
{
	if (c == '\'' || c == '\"')
		return (true);
	return (false);
}
