/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 13:18:13 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/11 19:19:10 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*split_after_word(t_token *curr, int *index, t_env replace);

bool	replace_word(t_token *curr, int *index, t_env replace)
{
	char	*after_token_word;
	char	*temp;
	char	*dollar_after_word;

	after_token_word = ft_calloc(ft_strlen(curr->word) - \
						ft_strlen(replace.key) + ft_strlen(replace.value), \
						sizeof(char));
	if (!after_token_word)
		return (true);
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

char	*serch_env_value(char *key, t_minishell *m_shell)
{
	t_env	*find;
	char	*status;

	if (strcmp(key, "$?") == 0)
	{
		status = ft_itoa(m_shell->prev_status);
		return (status);
	}
	find = search_env(key, m_shell->env);
	if (find == NULL)
		return ("");
	return (find->value);
}
