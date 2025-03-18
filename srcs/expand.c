/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:23:04 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/18 21:22:57 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	split_before_env(char **before_env, int i, t_token *curr);
static bool	replace_word(int start, char *after_word, char *before_word, t_token *current);
static void	copy_word(int *before, char *before_w, int *after, char *after_w);

/*
	＄がある
	　＄の後ろに文字列がある
	　　＄の後ろの文字列の環境変数を取得
	　　＄の後ろの文字列と環境変数を交換する
*/

void	expand(t_token **head)
{
	t_token	*curr;
	int		i;
	int		quart_count;
	bool	err_flg;
	char	*after_env;
	char	*before_env;

	i = 0;
	curr = *head;
	err_flg = false;
	quart_count = 0;
	before_env = NULL;
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
					err_flg = split_before_env(&before_env, i, curr);
					after_env = getenv(before_env);
					replace_word(i, after_env, before_env, curr);
				}
			}
			i++;
		}
		printf("curr->word %s\n", curr->word);
		curr = curr->next;
	}
}

static bool	split_before_env(char **before_env, int i, t_token *curr)
{
	int		end;
	bool	err_flg;

	err_flg = false;
	end = i + 1;
	while (curr->word[end] != ' ' && curr->word[end] \
		&& curr->word[end] != '$' && !is_quart(curr->word[end]))
		end++;
	*before_env = ft_substr(curr->word, i, end - i);
	if (!*before_env)
		return (true);
	*before_env = ft_strtrim(*before_env, "$");
	if (!*before_env)
		return (true);
	return (err_flg);
}

static bool	replace_word(int start, char *after_word, char *before_word, t_token *current)
{
	bool	err_flg;
	char	*after_token_word;
	int		i;
	int		after_i;
	int		current_word_len;
	int		after_token_len;
	int		after_word_len;
	int		before_word_len;
	char	*temp;

	// mitaiou
	// after_word = NULL
	// before_word = NULL($のみの場合)
	// $?の場合

	// ここきれいに出来ないか？
	before_word_len = 0;
	after_word_len = 0;
	err_flg = false;
	if (after_word)
		after_word_len = (int)ft_strlen(after_word);
	if (before_word)
		before_word_len = (int)ft_strlen(before_word) + 1;
	current_word_len = (int)ft_strlen(current->word);
	after_token_len = current_word_len - before_word_len + after_word_len;

	after_token_word = (char *)ft_calloc(sizeof(char), after_token_len);
	if (!after_token_word)
		return (true);
	i = 0;
	after_i = 0;
	while (i < start)
		copy_word(&i, current->word, &after_i, after_token_word);
	temp = ft_strjoin(after_token_word, after_word);
	if (!temp)
	{
		free(after_token_word);
		free(after_word);
		return (true);
	}
	after_token_word = temp;
	after_i = after_i + after_word_len;
	i = i + before_word_len;
	while (current->word[i])
		copy_word(&i, current->word, &after_i, after_token_word);
	free(current->word);
	current->word = after_token_word;
	return (err_flg);
}

static void	copy_word(int *before, char *before_w, int *after, char *after_w)
{
	after_w[*after] = before_w[*before];
	*before = *before + 1;
	*after = *after + 1;
}
