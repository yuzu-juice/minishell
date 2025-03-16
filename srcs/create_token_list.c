/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:48:17 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/16 13:11:14 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

bool	create_normal_token(char *line, int *i, t_token **head);
bool	create_quart_word(char *line, int *index, t_token **head);

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
		syntax_error();
	return (head);
}

bool	create_normal_token(char *line, int *i, t_token **head)
{
	int		word_len;
	int		len;
	bool	err_flg;

	err_flg = false;
	word_len = 0;
	len = (int)ft_strlen(line);
	if (is_quart(line[*i]))
		err_flg = create_quart_word(line, i, head);
	else
		err_flg = create_token_word(i, line, head);
	return (err_flg);
}

bool	create_quart_word(char *line, int *index, t_token **head)
{
	bool	err_flg;
	int		j;
	char	type;
	char	*word;

	err_flg = false;
	type = line[*index];
	j = 1;
	while (line[*index + j] != type)
		j++;
	word = ft_substr(line, *index, j + 1);
	if (!word)
		return (true);
	if (*index == 0 || is_split_char(line[*index - 1]))
		err_flg = add_token(head, create_token_node(word));
	else
		err_flg = add_current_token(word, head);
	*index = *index + j + 1;
	return (err_flg);
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
