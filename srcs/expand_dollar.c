/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:33:45 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/30 13:21:04 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	expand_exec(t_token *curr, int *index, t_env *env);
static void	skip_single_quote(t_token *curr, int *index);
static bool	replace_env_word(t_token *curr, int *index, t_env *env);
static char	*split_env_key(t_token *curr, int *index);

bool	expand_dollar(t_token **head, t_env *env)
{
	t_token	*curr;
	int		i;
	bool	err_flg;

	curr = *head;
	err_flg = false;
	while (curr)
	{
		i = 0;
		while (curr->word[i])
		{
			if (is_quote(curr->word[i]) || curr->word[i] == '$')
				err_flg = expand_exec(curr, &i, env);
			if (err_flg)
				break ;
			i++;
		}
		if (err_flg)
			break ;
		curr = curr->next;
	}
	if (err_flg)
		return (true);
	return (false);
}

static bool	expand_exec(t_token *curr, int *index, t_env *env)
{
	int		i;
	bool	err_flg;

	err_flg = false;
	if (curr->word[*index] == '\'')
		skip_single_quote(curr, index);
	else if (curr->word[*index] == '\"')
	{
		i = *index + 1;
		while (curr->word[i])
		{
			if (curr->word[i] == '$')
			{
				*index = i;
				err_flg = replace_env_word(curr, index, env);
			}
			i++;
		}
	}
	else
		err_flg = replace_env_word(curr, index, env);
	return (err_flg);
}

static void	skip_single_quote(t_token *curr, int *index)
{
	int	i;

	i = *index + 1;
	while (curr->word[i])
	{
		if (curr->word[i] == '\'')
			break ;
		i++;
	}
	*index = i;
}

static bool	replace_env_word(t_token *curr, int *index, t_env *env)
{
	t_env	replace;

	replace.key = split_env_key(curr, index);
	if (!replace.key)
		return (true);
	if (ft_strcmp(replace.key, "$") == 0)
	{
		*index = *index + 1;
		return (false);
	}
	replace.value = ft_strdup(serch_env_value(replace.key, env));
	if (replace_word(curr, index, replace))
	{
		free(replace.key);
		return (true);
	}
	*index = *index + ft_strlen(replace.value) - 1;
	return (false);
}

// char	*serch_env_value(char *key, t_env *env)
// {
// 	t_env	*find;

// 	find = search_env(key, env);
// 	if (find == NULL)
// 		return ("");
// 	return (find->value);
// }

static char	*split_env_key(t_token *curr, int *index)
{
	char	*key;
	int		i;

	i = *index + 1;
	while (curr->word[i] && curr->word[i] != ' ' && \
		!is_quote(curr->word[i]) && curr->word[i] != '$')
		i++;
	key = ft_substr(curr->word, *index, i - *index);
	if (!key)
		return (NULL);
	return (key);
}

// bool	replace_word(t_token *curr, int *index, t_env replace)
// {
// 	char	*after_token_word;
// 	char	*temp;
// 	char	*dollar_after_word;

// 	after_token_word = ft_calloc(ft_strlen(curr->word) - \
// 						ft_strlen(replace.key) + ft_strlen(replace.value), \
// 						sizeof(char));
// 	if (!after_token_word)
// 		return (true);
// 	after_token_word = ft_substr(curr->word, 0, *index);
// 	temp = ft_strjoin(after_token_word, replace.value);
// 	free(after_token_word);
// 	dollar_after_word = split_after_word(curr, index, replace);
// 	if (!dollar_after_word)
// 		return (true);
// 	after_token_word = ft_strjoin(temp, dollar_after_word);
// 	free(curr->word);
// 	free(temp);
// 	if (!after_token_word)
// 		return (true);
// 	curr->word = after_token_word;
// 	return (false);
// }

// char	*split_after_word(t_token *curr, int *index, t_env replace)
// {
// 	char	*split_after_word;

// 	split_after_word = ft_substr(curr->word, \
// 								*index + ft_strlen(replace.key), \
// 								ft_strlen(curr->word));
// 	return (split_after_word);
// }
