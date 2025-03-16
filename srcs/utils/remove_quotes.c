/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:33:20 by takitaga          #+#    #+#             */
/*   Updated: 2025/03/16 12:13:01 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int  count_quotes(char *token);

char	*remove_quotes(char *token)
{
    char    *ret;
    int     remove_char_count;
    int     i;

    remove_char_count = count_quotes(token);
    i = 0;
    if (remove_char_count == 0)
        return (token);
    ret = ft_calloc(remove_char_count, sizeof(char));
    if (ret == NULL)
        return (NULL);
    i = 0;
    while (*token != '\0')
    {
        if (*token == '\'' || *token == '"')
        {
            token++;
            continue ;
        }
        ret[i] = *token;
        token++;
        i++;
    }
    return (ret);
}

static int  count_quotes(char *token)
{
    int     remove_char_count;
    int     i;

    remove_char_count = 0;
    i = 0;
    while (token[i] != '\0')
    {
        if (token[i] == '\'' || token[i] == '"')
            remove_char_count++;
        i++;
    }
    return (remove_char_count);
}
