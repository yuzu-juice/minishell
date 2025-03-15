/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:10:32 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/14 18:55:40 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

char	*create_token_word(int *start, char *line, t_token **head)
{
	char	*word;
	int		new_token_flg;
	int		j;
	int		len;
	char	*temp_word;

	len = (int)ft_strlen(line);
	j = *start + 1;
	while (!is_split_char(line[j]) && !is_quart(line[j]) && j < len)
		j++;
	word = ft_substr(line, *start, j - *start);
	if (!word)
		return (NULL);
	*start = j - 1;
	if (*start != 0 && is_quart(line[*start - 1]))
		new_token_flg = 0;
	else
		new_token_flg = 1;

	if (new_token_flg == 0)
	{
		temp_word = ft_strjoin(get_last_token(head)->word, word);
		free(get_last_token(head)->word);
		free(word);
		get_last_token(head)->word = temp_word;
	}
	else
		add_token(head, create_token_node(word));

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
