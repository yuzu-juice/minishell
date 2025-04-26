/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process_list_utils1.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:28:04 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/26 14:10:58 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	add_space(t_proc *curr)
{
	char	*temp;

	temp = ft_strjoin(curr->cmd, " ");
	if (!temp)
		return (true);
	curr->cmd = temp;
	return (false);
}

t_proc	*get_last_proc(t_proc **list)
{
	t_proc	*temp;

	if (*list == NULL)
		return (*list);
	temp = *list;
	while (temp->next)
	{
		temp = temp->next;
	}
	return (temp);
}

bool	validation_pipe(t_token *prev, t_token *next, t_proc **list)
{
	(void)list;
	if (prev == NULL || next == NULL)
		return (true);
	if (ft_strcmp(prev->word, "|") == 0 || ft_strcmp(next->word, "|") == 0)
		return (true);
	return (false);
}

void	*free_proc_list(t_proc **list)
{
	t_proc	*temp;
	t_proc	*curr;

	curr = *list;
	while (curr)
	{
		free_string_double_array(curr->cmd_args);
		free(curr->cmd);
		free_redirection_list(&curr->redir);
		temp = curr->next;
		free(curr);
		curr = temp;
	}
	*list = NULL;
	return (NULL);
}
