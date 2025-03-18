/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_normal_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:50:42 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/18 15:55:24 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	create_quart_word(char *line, int *index, t_token **head);
static bool	create_token_word(int *start, char *line, t_token **head);

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

static bool	create_quart_word(char *line, int *index, t_token **head)
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

static bool	create_token_word(int *start, char *line, t_token **head)
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
