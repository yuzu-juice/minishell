/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:33:45 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/24 20:17:43 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	expand_main(t_token *token, int *index, t_env *env);
static char	*split_after_dollar_word(t_token *token, int *index);
static char	*search_env_value(char *before, t_env *env);
static bool	create_after_token_word(t_token *token, \
									int *index, \
									t_replace_env replace_env, \
									char **after_token_word);

bool	expand_dollar(t_token **head, t_env *env)
{
	t_token	*curr;
	int		i;
	int		quart_count ;

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
			{
				if (expand_main(curr, &i, env))
					return (true);
			}
			i++;
		}
		curr = curr->next;
	}
	return (false);
}

static bool	expand_main(t_token *token, int *index, t_env *env)
{
	char			*after_token_word;
	bool			err_flg;
	t_replace_env	replace_env;

	err_flg = false;
	after_token_word = NULL;
	replace_env.key = split_after_dollar_word(token, index);
	if (!replace_env.key)
		return (true);
	if (ft_strcmp(replace_env.key, "$") == 0)
	{
		free(replace_env.key);
		return (false);
	}
	replace_env.val = search_env_value(replace_env.key, env);
	err_flg = create_after_token_word(token, \
		index, replace_env, &after_token_word);
	if (err_flg)
		free(replace_env.key);
	free(token->word);
	token->word = after_token_word;
	*index = *index + (int)ft_strlen(replace_env.val) - 1;
	if (err_flg)
		return (true);
	return (false);
}

static bool	create_after_token_word(t_token *token, \
								int *index, \
								t_replace_env env, \
								char **after_token_word)
{
	char	*replace_word;
	char	*word_left;
	char	*temp;

	if (env.val == NULL)
		env.val = ft_strdup("");
	replace_word = (char *)ft_calloc(ft_strlen(token->word) - \
	(int)ft_strlen(env.key) + (int)ft_strlen(env.val), sizeof(char));
	if (!replace_word)
		return (true);
	ft_strlcpy(replace_word, token->word, *index + 1);
	temp = ft_strjoin(replace_word, env.val);
	free(replace_word);
	if (!temp)
		return (true);
	replace_word = temp;
	if (!replace_word)
		return (true);
	word_left = ft_substr(token->word, \
		*index + (int)ft_strlen(env.key), ft_strlen(token->word));
	*after_token_word = ft_strjoin(replace_word, word_left);
	return (false);
}

// if before_word start "$?", return $? only
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

// if (before_word == "$?"){return status;}
static char	*search_env_value(char *before, t_env *env)
{
	t_env	*result;

	result = search_env(before, env);
	if (result == NULL)
		return (NULL);
	return (result->value);
}
