/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_string_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 11:10:46 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/20 15:03:48 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_double_string_array(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		i++;
	}
	if (str != NULL && i == 0)
	{
		return (1);
	}
	printf("count i %d\n", i);
	return (i);
}
