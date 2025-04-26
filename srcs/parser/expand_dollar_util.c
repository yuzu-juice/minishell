/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 13:18:13 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/26 14:33:40 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*split_after_word(t_token *curr, int *index, t_env replace);

bool	replace_word(t_token *curr, int *index, t_env replace)
{
	char	*after_token_word;
	char	*temp;
	char	*dollar_after_word;

	after_token_word = ft_substr(curr->word, 0, *index);
	temp = ft_strjoin(after_token_word, replace.value);
	free(after_token_word);
	dollar_after_word = split_after_word(curr, index, replace);
	if (!dollar_after_word)
		return (true);
	after_token_word = ft_strjoin(temp, dollar_after_word);
	free(curr->word);
	free(temp);
	if (!after_token_word)
		return (true);
	curr->word = after_token_word;
	free(dollar_after_word);
	return (false);
}

static char	*split_after_word(t_token *curr, int *index, t_env replace)
{
	char	*split_after_word;

	split_after_word = ft_substr(curr->word, \
								*index + ft_strlen(replace.key), \
								ft_strlen(curr->word));
	return (split_after_word);
}

char	*search_env_value(char *key, t_minishell *m_shell)
{
	t_env	*find;
	char	*value_str;

	if (ft_strcmp(key, "$?") == 0)
	{
		value_str = ft_itoa(m_shell->prev_status);
		return (value_str);
	}
	find = search_env(key, m_shell->env);
	if (find == NULL)
		value_str = ft_strdup("");
	else
		value_str = ft_strdup(find->value);
	return (value_str);
}
