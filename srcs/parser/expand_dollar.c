/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:33:45 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/22 15:29:40 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	expand_exec(t_token *curr, int *index, t_minishell *m_shell);
static void	skip_single_quote(t_token *curr, int *index);
static bool	replace_env_word(t_token *curr, int *index, t_minishell *m_shell);
static char	*split_env_key(t_token *curr, int *index);

bool	expand_dollar(t_token **head, t_minishell *m_shell)
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
				err_flg = expand_exec(curr, &i, m_shell);
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

static bool	expand_exec(t_token *curr, int *index, t_minishell *m_shell)
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
				err_flg = replace_env_word(curr, index, m_shell);
			}
			if (curr->word[i] == '\"')
				break ;
			i++;
		}
		*index = i;
	}
	else
		err_flg = replace_env_word(curr, index, m_shell);
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

static bool	replace_env_word(t_token *curr, int *index, t_minishell *m_shell)
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
	replace.value = ft_strdup(search_env_value(replace.key, m_shell));
	if (replace_word(curr, index, replace))
	{
		free(replace.key);
		return (true);
	}
	*index = *index + ft_strlen(replace.value) - 1;
	return (false);
}

static char	*split_env_key(t_token *curr, int *index)
{
	char	*key;
	int		i;

	i = *index + 1;
	if (ft_strncmp(&curr->word[*index], "$?", 2) == 0)
		return (ft_strdup("$?"));
	while (curr->word[i] && curr->word[i] != ' ' && \
		!is_quote(curr->word[i]) && curr->word[i] != '$')
	{
		i++;
	}
	key = ft_substr(curr->word, *index, i - *index);
	if (!key)
		return (NULL);
	return (key);
}
