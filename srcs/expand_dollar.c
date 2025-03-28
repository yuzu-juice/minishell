/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:33:45 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/28 15:31:32 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	expand_exec(t_token *curr, int *index, t_env *env);
static void	skip_single_quote(t_token *curr, int *index);
bool	replace_env_word(t_token *curr, int *index, t_env *env);

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
			printf("curr->word[i] %c\n", curr->word[i]);

			if (is_quote(curr->word[i]) || curr->word[i] == '$')
				err_flg = expand_exec(curr, &i, env);
			if (err_flg)
				break ;
			i++;
		}
		if (err_flg)
			break ;
		printf("word :%s\n", curr->word);
		curr = curr->next;
	}
	if (err_flg)
		return (true);
	return (false);
}

static bool	expand_exec(t_token *curr, int *index, t_env *env)
{
	int	i;
	(void)env;

	if (curr->word[*index] == '\'')
		skip_single_quote(curr, index);
	else if (curr->word[*index] == '\"')
	{
		i = *index + 1;
		while (curr->word[i])
		{
			if (curr->word[i] == '$')
			{
				printf("double quote $\n");
			}
			i++;
		}
	}
	else
	{
		replace_env_word(curr, index, env);
	}
	return (false);
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

bool	replace_env_word(t_token *curr, int *index, t_env *env)
{
	t_env	replace;

	replace.key = split_env_key();
	replace.value = search_env(replace.key, env)->value;
	return (false);
}
