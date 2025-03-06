/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:07:35 by yohatana          #+#    #+#             */
/*   Updated: 2024/05/15 14:27:38 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strnstr(const char *str, const char *find, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	count;

	if (ft_strlen(find) == 0)
		return ((char *)str);
	if (len == 0)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && i < len)
	{
		count = i;
		j = 0;
		while (find[j] != '\0' && str[count] == find[j] && count < len)
		{
			j++;
			count++;
		}
		if (find[j] == '\0')
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}
