/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:59:40 by yohatana          #+#    #+#             */
/*   Updated: 2024/05/14 22:57:57 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_c;
	unsigned char	*src_c;
	size_t			i;

	if (dst == NULL && src == NULL)
		return (NULL);
	dst_c = (unsigned char *)dst;
	src_c = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dst_c[i] = src_c[i];
		i++;
	}
	return (dst);
}
