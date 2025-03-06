/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:53:12 by yohatana          #+#    #+#             */
/*   Updated: 2024/05/01 13:10:54 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	a;
	unsigned char	*p;

	a = c;
	i = 0;
	p = (unsigned char *)b;
	while (i < len)
	{
		*p = a;
		p++;
		i++;
	}
	return (b);
}
