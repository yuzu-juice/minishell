/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 13:18:13 by yohatana          #+#    #+#             */
/*   Updated: 2025/05/02 19:52:40 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*split_after_word(t_token *curr, int *index, t_env replace);

bool	replace_word(t_token *curr, int *index, t_env replace)
{
	char	*after_token_word;
	char	*temp;
	char	*dollar_after_word;

	printf("replace_word\n");
	after_token_word = ft_substr(curr->word, 0, *index);
	printf("after_token_word %s\n", after_token_word);
	temp = ft_strjoin(after_token_word, replace.value);
	printf("kokok\n");
	free(after_token_word);
	dollar_after_word = split_after_word(curr, index, replace);
	printf("dollar_after_word %s\n", dollar_after_word);
	if (!dollar_after_word)
		return (true);
	after_token_word = ft_strjoin(temp, dollar_after_word);
	printf("after_token_word %s\n", after_token_word);
	free(curr->word);
	free(temp);
	if (!after_token_word)
	{
		printf("if (!after_token_word)\n");
		return (true);
	}
	curr->word = after_token_word;
	free(dollar_after_word);
	printf("aaaaa\n");
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
	printf("search_env_value\n");
	printf("find %p\n", find);
	if (find == NULL)
		value_str = ft_strdup("");
	if (find->value)
		value_str = ft_strdup(find->value);
	else
		return (NULL);
	return (value_str);
}
