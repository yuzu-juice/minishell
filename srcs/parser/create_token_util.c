/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:10:32 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/21 18:15:31 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_split_char(char c)
{
	if (c == ' ' || c == '|' || c == '\t' || c == '\n' || c == '>' || c == '<')
		return (true);
	return (false);
}

bool	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (true);
	return (false);
}

bool	add_current_token(char *word, t_token **head)
{
	char	*temp;
	bool	err_flg;

	err_flg = false;
	temp = ft_strjoin(get_last_token(head)->word, word);
	free(get_last_token(head)->word);
	free(word);
	if (!temp)
		return (true);
	get_last_token(head)->word = temp;
	return (err_flg);
}

t_token	*get_last_token(t_token **head)
{
	t_token	*temp;

	temp = *head;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

int	count_token(t_token **head)
{
	t_token	*token;
	int		count;

	count = 0;
	token = *head;
	while (token)
	{
		count++;
		token = token->next;
	}
	return (count);
}
