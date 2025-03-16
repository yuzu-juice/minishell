/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:23:04 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/16 17:46:42 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expansion(t_token **head)
{
	t_token	*curr;
	int		i;
	int		quart_count;
	int		end;
	// char	*env;
	char	*search;

	// "$PWD"'$PWD'のときめっちゃ困る
	i = 0;
	curr = *head;
	quart_count = 0;
	while (curr)
	{
		while (curr->word[i])
		{
			if (curr->word[i] == '\'')
				quart_count++;
			else if (curr->word[i] == '$')
			{
				if (quart_count % 2 == 0)
				{
					end = i + 1;
					while (curr->word[end] != ' ' && curr->word[end] \
						&& curr->word[end] != '$' && curr->word[end] != '\"')
						end++;
					search = ft_substr(curr->word, i, end - i);
					search = ft_strtrim(search, "$");
					search = ft_strtrim(search, "\"");
					printf("search %s\n", search);
					// env = getenv(search);
					// replace


				}
			}
			i++;
		}
		curr = curr->next;
	}
}
