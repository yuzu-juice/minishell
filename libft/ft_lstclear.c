/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:32:17 by yohatana          #+#    #+#             */
/*   Updated: 2024/05/22 18:45:06 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	if (lst == NULL || del == NULL)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
	*lst = NULL;
}

// int main()
// {
// 	t_list *lst = ft_lstnew(ft_strdup("111"));
// 	t_list *lst2 = ft_lstnew(ft_strdup("222"));

// 	ft_lstadd_back(&lst, lst2);
// 	// lst->next = lst2;

// 	ft_lstclear(&lst, free);
// 	// free(lst2);
// 	// free(lst);
// }
