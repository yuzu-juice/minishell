/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:26:02 by yohatana          #+#    #+#             */
/*   Updated: 2024/05/14 19:09:25 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*result;
	char	chara;

	i = 0;
	result = (char *)s;
	chara = c;
	while (s[i] != '\0')
	{
		if (s[i] == chara)
		{
			return (result);
		}
		i++;
		result++;
	}
	if (chara == '\0' && s[i] == '\0')
		return (result);
	return (NULL);
}
