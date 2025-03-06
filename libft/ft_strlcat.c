/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:34:30 by yohatana          #+#    #+#             */
/*   Updated: 2024/05/17 14:05:14 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static void	dest_copy(char *dest, const char *src, size_t destlen, size_t i);

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	destlen;
	size_t	srclen;
	size_t	i;

	i = 0;
	srclen = ft_strlen(src);
	if (dest == NULL && size == 0)
		return (srclen);
	destlen = ft_strlen(dest);
	if (size <= srclen + destlen)
	{
		while (i + destlen + 1 < size)
			dest_copy(dest, src, destlen, i++);
	}
	else
	{
		while (i < srclen)
			dest_copy(dest, src, destlen, i++);
	}
	if (dest != NULL)
		dest[destlen + i] = '\0';
	if (size < destlen)
		return (srclen + size);
	return (destlen + srclen);
}

static void	dest_copy(char *dest, const char *src, size_t destlen, size_t i)
{
	dest[destlen + i] = src[i];
}
