/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:23:04 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/18 19:29:24 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static bool	replace_word(int i, int end, char *after_word, char *before_word, t_token *current);
static bool	replace_word(int start, int end, char *after_word, char *before_word, t_token *current);

void	expansion(t_token **head)
{
	t_token	*curr;
	int		i;
	int		quart_count;
	int		end;
	char	*after_env;
	char	*before_env;
	int		end_quart_flg;
	int		after_env_len;
	int		before_env_len;
	// char	*after;

	// "$PWD"'$PWD'のときめっちゃ困る
	i = 0;
	curr = *head;
	quart_count = 0;
	end_quart_flg = false;
	after_env_len = 0;
	before_env_len = 0;
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
						&& curr->word[end] != '$' && curr->word[end] != '\"' && curr->word[end] != '\'')
						end++;
					before_env = ft_substr(curr->word, i, end - i);
					before_env_len = (int)ft_strlen(before_env);
					before_env = ft_strtrim(before_env, "$");
					after_env = getenv(before_env);
					if (!after_env)
						after_env_len = 0;
					else
						after_env_len = (int)ft_strlen(after_env);
					replace_word(i, end, after_env, before_env, curr);
				}
			}
			i++;
		}
		printf("curr->word %s\n", curr->word);
		curr = curr->next;
	}
}

static bool	replace_word(int start, int end, char *after_word, char *before_word, t_token *current)
{
	bool	err_flg;
	int		word_len;
	int		after_word_len;
	char	*after_token_word;
	int		i;
	int		after_i;
	(void)end;

	err_flg = false;
	word_len = (int)ft_strlen(current->word);
	after_word_len = word_len - ((int)ft_strlen(before_word) + 1) + (int)ft_strlen(after_word);
	after_token_word = (char *)ft_calloc(sizeof(char), after_word_len);
	if (!after_token_word)
		err_flg = true;
	i = 0;
	after_i = 0;
	while (i < start)
	{
		after_token_word[after_i] = current->word[i];
		i++;
		after_i++;
	}
	after_token_word = ft_strjoin(after_token_word, after_word);
	if (!after_token_word)
		err_flg = true;
	after_i = after_i + (int)ft_strlen(after_word);
	i = i + (int)ft_strlen(before_word) + 1;
	while (current->word[i])
	{
		after_token_word[after_i] = current->word[i];
		i++;
		after_i++;
	}
	free(current->word);
	current->word = after_token_word;
	return (err_flg);
}
