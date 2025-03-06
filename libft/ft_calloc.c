/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 11:09:34 by yohatana          #+#    #+#             */
/*   Updated: 2025/02/23 15:24:23 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;

	if ((count != 0 && SIZE_MAX / count < size)
		|| (size != 0 && SIZE_MAX / size < count))
		return (NULL);
	if (count == 0 || size == 0)
	{
		result = malloc(1);
		if (result == NULL)
			return (NULL);
		return (result);
	}
	result = malloc(size * count);
	if (result == NULL)
		return (NULL);
	ft_bzero(result, size * count);
	return (result);
}
