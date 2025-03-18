/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:22:31 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/18 16:04:41 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	parser(char *line)
{
	t_token	*head;
	bool	err_flg;

	err_flg = false;
	// TODO: line too long

	head = NULL;
	if (validation_quart(line))
	{
		syntax_error(&head);
		return (true);
	}
	head = create_token_list(line);
	if (!head)
		return (true);
	expansion(&head);
	// create_cmds()
	// free_token_list()
	return (false);
}

bool	validation_quart(char *line)
{
	int		i;
	int		j;
	char	type;

	i = 0;
	j = 0;
	type = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (line[i] == '\'')
				type = '\'';
			if (line[i] == '\"')
				type = '\"';
			j = i + 1;
			while (line[j] != type && j < (int)ft_strlen(line))
				j++;
			if (j == (int)ft_strlen(line))
				return (true);
			i = j;
		}
		i++;
	}
	return (false);
}

void	syntax_error(t_token **head)
{
	print_msg("syntax_error");
	free_token_list(head);
}
