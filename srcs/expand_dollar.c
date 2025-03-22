/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:33:45 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/22 18:58:12 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	expand_main(t_token *token, int *index, t_env *env);
static char	*split_after_dollar_word(t_token *token, int *index);
static char	*serch_env_value(char *before, t_env *env);
t_env		*serch_env(char *key, t_env *env);
static bool	replace_word(t_token *token, int *index, char *before, char *after);

bool	expand_dollar(t_token **head, t_env *env)
{
	t_token	*curr;
	int		i;
	int		quart_count ;
	bool	err_flg;

	err_flg = false;
	curr = *head;
	while (curr)
	{
		i = 0;
		quart_count = 0;
		while (curr->word[i])
		{
			if (curr->word[i] == '\'')
				quart_count++;
			if (quart_count % 2 == 0 && curr->word[i] == '$')
				err_flg = expand_main(curr, &i, env);
			if (err_flg)
				break ;
			i++;
		}
		if (err_flg)
			break ;
		curr = curr->next;
	}
	return (err_flg);
}

static bool	expand_main(t_token *token, int *index, t_env *env)
{
	char	*before_word;
	char	*after_word;
	bool	err_flg;

	err_flg = false;
	before_word = split_after_dollar_word(token, index);
	if (!before_word)
		return (true);
	after_word = serch_env_value(before_word, env);
	err_flg = replace_word(token, index, before_word, after_word);
	if (err_flg)
	{
		free(before_word);
		free(after_word);
		return (true);
	}
	*index = *index + (int)ft_strlen(after_word) - 1;
	return (false);
}

static bool	replace_word(t_token *token, int *index, char *before, char *after)
{
	int		replace_len;
	char	*replace_word;
	char	*word_left;
	char	*temp;

	replace_len = \
	ft_strlen(token->word) - (int)ft_strlen(before) + (int)ft_strlen(after);
	replace_word = (char *)ft_calloc(replace_len, sizeof(char));
	if (!replace_word)
		return (true);
	ft_strlcpy(replace_word, token->word, *index + 1);
	temp = ft_strjoin(replace_word, after);
	free(replace_word);
	if (!temp)
		return (true);
	replace_word = temp;
	if (!replace_word)
		return (true);
	word_left = ft_substr(token->word, *index + (int)ft_strlen(before), \
	ft_strlen(token->word));
	temp = ft_strjoin(replace_word, word_left);
	free(replace_word);
	free(word_left);
	if (!temp)
		return (true);
	free(token->word);
	token->word = temp;
	return (false);
}

static char	*split_after_dollar_word(t_token *token, int *index)
{
	char	*before_word;
	int		i;

	before_word = NULL;

	i = *index + 1;
	while (token->word[i] != '$' && token->word[i] != ' ' \
		&& token->word[i] != '\0' && !is_quote(token->word[i]))
		i++;
	before_word = ft_substr(token->word, *index, i - *index);
	if (!before_word)
		return (NULL);
	return (before_word);
}

static char	*serch_env_value(char *before, t_env *env)
{
	t_env	*result;

	result = serch_env(before, env);
	if (result == NULL)
		return (NULL);
	return (result->value);
}

// utilの味がする
t_env	*serch_env(char *key, t_env *env)
{
	t_env	*temp;
	char	*trim_dollar;

	temp = env;
	trim_dollar = ft_strtrim(key, "$");
	if (!key)
		return (NULL);
	while (temp)
	{
		if (ft_strcmp(trim_dollar, temp->key) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}
