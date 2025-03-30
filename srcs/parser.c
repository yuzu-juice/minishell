/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:22:31 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/30 15:49:46 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	parser(char *line)
{
	t_token	*head;
	t_proc	*proc;

	head = NULL;
	if (has_unclosed_quotes(line))
	{
		syntax_error(&head);
		return (true);
	}
	head = create_token_list(line);
	if (!head)
		return (true);
	proc = create_process_list(&head);
	if (!proc)
	{
		print_msg("syntax_error");
		return (true);
	}
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
	ft_putendl_fd("syntax_error", 2);
	free_token_list(head);
}
