/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:31:56 by yohatana          #+#    #+#             */
/*   Updated: 2024/05/19 16:53:58 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_lstsize(t_list *lst)
{
	int	lst_len;

	if (lst == NULL)
		return (0);
	lst_len = 1;
	while (lst->next != NULL)
	{
		lst_len++;
		lst = lst->next;
	}
	return (lst_len);
}
