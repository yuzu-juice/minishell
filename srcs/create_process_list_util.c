/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process_list_util.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:28:04 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/27 17:00:16 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	add_space(t_proc_list *curr)
{
	char	*temp;

	temp = ft_strjoin(curr->proc->cmd, " ");
	if (!temp)
		return (true);
	curr->proc->cmd = temp;
	return (false);
}

t_proc_list	*get_last_proc(t_proc_list **list)
{
	t_proc_list	*temp;

	if (*list == NULL)
		return (*list);
	temp = *list;
	while (temp->next)
	{
		temp = temp->next;
	}
	return (temp);
}

bool	validation_pipe(t_token *prev, t_token *next)
{
	if (prev == NULL || next == NULL)
		return (true);
	if (ft_strcmp(prev->word, "|") == 0 || ft_strcmp(next->word, "|") == 0)
		return (true);
	return (false);
}

bool	token_to_cmd(t_token *curr, t_token *prev, t_proc_list **list)
{
	bool	err_flg;
	bool	new_proc_flg;

	err_flg = false;
	new_proc_flg = false;
	if (prev == NULL || ft_strcmp(prev->word, "|") == 0)
		new_proc_flg = true;
	else
		new_proc_flg = false;
	if (ft_strcmp(curr->word, "|") == 0)
		err_flg = validation_pipe(prev, curr->next);
	else
		err_flg = add_to_cmd(list, curr->word, new_proc_flg);
	return (err_flg);
}
