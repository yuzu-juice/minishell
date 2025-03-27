/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_proc_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:21:16 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/27 16:45:59 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

void	*free_proc_list(t_proc_list **list)
{
	t_proc_list	*temp;
	t_proc_list	*curr;

	curr = *list;
	while (curr)
	{
		free(curr->proc->cmd);
		free(curr->proc);
		temp = curr->next;
		free(curr);
		curr = temp;
	}
	list = NULL;
	return (NULL);
}
