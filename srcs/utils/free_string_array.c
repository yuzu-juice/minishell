/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_string_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:54:52 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/02 14:56:42 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include"../../includes/minishell.h"

void	free_string_doble_array(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free (str);
}
