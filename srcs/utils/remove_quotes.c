/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:33:20 by takitaga          #+#    #+#             */
/*   Updated: 2025/04/18 13:57:52 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_quotes(char *token);
static char	*copy_token(char *token, char *ret);

char	*remove_quotes(char *token)
{
	char	*ret;
	int		remove_char_count;

	remove_char_count = count_quotes(token);
	if (remove_char_count == 0)
		return (token);
	ret = ft_calloc(ft_strlen(token) - remove_char_count, sizeof(char));
	if (ret == NULL)
		return (NULL);
	ret = copy_token(token, ret);
	return (ret);
}

static int	count_quotes(char *token)
{
	int		remove_char_count;
	int		i;
	int		j;
	char	quote_type;

	remove_char_count = 0;
	i = 0;
	quote_type = 0;
	while (token[i] != '\0')
	{
		if (token[i] == '\'' || token[i] == '"')
		{
			remove_char_count++;
			quote_type = token[i];
			j = i + 1;
			while (token[j] != quote_type)
				j++;
			remove_char_count++;
			i = j;
		}
		i++;
	}
	return (remove_char_count);
}

static char	*copy_token(char *token, char *ret)
{
	int		i;
	char	quote_type;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (token[i] != '\0')
	{
		if (token[i] == '\'' || token[i] == '"')
			quote_type = token[i];
		j = i + 1;
		while (token[j] != quote_type)
		{
			ret[k] = token[j];
			j++;
			k++;
		}
		i = j;
		i++;
	}
	ret[k] = '\0';
	return (ret);
}
