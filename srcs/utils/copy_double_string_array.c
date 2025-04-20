/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_double_string_array.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 11:16:21 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/20 15:30:38 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	copy_double_string_array(char **src, char **new, char *word)
{
	int		i;
	bool	err_flg;

	err_flg = false;
	if (src == NULL && word == NULL)
		return (false);
	i = 0;
	if (src != NULL)
	{
		while (src[i])
		{
			new[i] = ft_strdup(src[i]);
			if (!new[i])
			{
				err_flg = true;
				break ;
			}
			i++;
		}
	}
	new[i] = ft_strdup(word);
	new[i + 1] = NULL;
	if (err_flg)
		return (true);
	return (false);
}

// debug
void	print_double_string_array(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
}
