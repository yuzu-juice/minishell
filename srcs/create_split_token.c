/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_split_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 16:26:35 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/19 14:28:43 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

static bool	create_redirect_token(char *line, int *i, t_token **head);
static bool	create_double_redirect(char *line, int *index, char **word);

bool	create_split_token(char *line, int *index, t_token **head)
{
	bool	err_flg;
	char	*word;

	err_flg = 0;
	if (line[*index] == '|')
	{
		word = ft_strdup("|");
		if (!word)
			err_flg = true;
		err_flg = add_token_node(head, create_token_node(word));
		*index = *index + 1;
	}
	else if (line[*index] == '<' || line[*index] == '>')
		err_flg = create_redirect_token(line, index, head);
	else
		*index = *index + 1;
	return (err_flg);
}

static bool	create_redirect_token(char *line, int *i, t_token **head)
{
	char	*word;
	int		new_token_flg;
	bool	err_flg;

	err_flg = false;
	new_token_flg = 1;
	if (line[*i] == '<')
		word = ft_strdup("<");
	else
		word = ft_strdup(">");
	if (!word)
		err_flg = true;
	if (err_flg)
		return (err_flg);
	err_flg = create_double_redirect(line, i, &word);
	if (err_flg)
		return (err_flg);
	err_flg = add_token_node(head, create_token_node(word));
	*i = *i + 1;
	return (err_flg);
}

static bool	create_double_redirect(char *line, int *index, char **word)
{
	bool	err_flg;
	char	type;
	char	*temp;

	err_flg = false;
	type = line[*index];
	if (line[*index + 1] == type)
	{
		temp = ft_strjoin(*word, *word);
		if (!temp)
			err_flg = true;
		free(*word);
		*word = temp;
		*index = *index + 1;
	}
	return (err_flg);
}
