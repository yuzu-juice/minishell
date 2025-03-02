/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:22:32 by yohatana          #+#    #+#             */
/*   Updated: 2024/05/19 14:54:50 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;
	int				result;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	result = 0;
	while (i < n)
	{
		result = (unsigned char)str1[i] - (unsigned char)str2[i];
		if (result != 0)
			return (result);
		i++;
	}
	return (result);
}
