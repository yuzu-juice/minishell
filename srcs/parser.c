/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:22:31 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/22 18:58:09 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	parser(char *line, t_env *env)
{
	t_token	*head;

	head = NULL;
	if (has_unclosed_quotes(line))
	{
		syntax_error(&head);
		return (true);
	}
	head = create_token_list(line);
	if (!head)
		return (true);
	if (expand_dollar(&head, env))
		return (true);
	return (false);
}

bool	has_unclosed_quotes(char *line)
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
