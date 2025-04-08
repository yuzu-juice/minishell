/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:37:47 by takitaga          #+#    #+#             */
/*   Updated: 2025/04/08 19:38:09 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**split_string(char *str, char delimiter)
{
	char	*delimiter_pos;
	char	**result;
	int		first_str_len;
	int		second_str_len;

	result = ft_calloc(3, sizeof(char *));
	if (result == NULL)
		return (NULL);
	delimiter_pos = ft_strchr(str, delimiter);
	if (delimiter_pos == NULL)
	{
		result[0] = ft_strdup(str);
		result[1] = NULL;
	}
	else
	{
		first_str_len = delimiter_pos - str;
		second_str_len = ft_strlen(str) - first_str_len - 1;
		result[0] = ft_substr(str, 0, first_str_len);
		result[1] = ft_substr(str, first_str_len + 1, second_str_len);
	}
	return (result);
}
