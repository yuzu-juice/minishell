/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:18:01 by yohatana          #+#    #+#             */
/*   Updated: 2024/05/19 13:04:42 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest_c;
	unsigned char	*src_c;

	dest_c = (unsigned char *)dst;
	src_c = (unsigned char *)src;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (dst != NULL && src != NULL && len == 0)
		return (dst);
	if (dst < src)
		dst = ft_memcpy(dst, src, len);
	else
	{
		dest_c = dest_c + len - 1;
		src_c = src_c + len - 1;
		while ((unsigned char *)src <= src_c)
			*dest_c-- = *src_c--;
	}
	return (dst);
}
