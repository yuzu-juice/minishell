/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_string_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:54:52 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/23 13:42:31 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_string_double_array(char **str)
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
	free(str);
}
