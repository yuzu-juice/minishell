/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process_list_utils2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 05:04:18 by takitaga          #+#    #+#             */
/*   Updated: 2025/04/20 15:30:53 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	append_word_to_cmd(t_proc *curr_proc, char *word);
static char	**add_cmd_args(char **old, char *word);

t_proc	*create_proc_node(char *word)
{
	t_proc	*proc;

	proc = (t_proc *)ft_calloc(sizeof(t_proc), 1);
	if (!proc)
		return (NULL);
	if (word)
	{
		proc->cmd = ft_strdup(word);
		if (!proc->cmd)
		{
			free(proc);
			return (NULL);
		}
		proc->cmd_args = add_cmd_args(proc->cmd_args, word);
	}
	else
	{
		proc->cmd = NULL;
		proc->cmd_args = NULL;
	}
	proc->next = NULL;
	return (proc);
}

static bool	append_word_to_cmd(t_proc *curr_proc, char *word)
{
	char	*temp_cmd;
	char	*spaced_cmd;

	spaced_cmd = ft_strjoin(curr_proc->cmd, " ");
	if (!spaced_cmd)
		return (true);
	temp_cmd = ft_strjoin(spaced_cmd, word);
	free(spaced_cmd);
	if (!temp_cmd)
		return (true);
	free(curr_proc->cmd);
	curr_proc->cmd = temp_cmd;
	curr_proc->cmd_args = add_cmd_args(curr_proc->cmd_args, word);
	return (false);
}

bool	add_to_cmd(t_proc **list, char *word, bool is_new_proc)
{
	t_proc	*curr_proc;

	if (!word)
		return (false);
	if (is_new_proc || *list == NULL)
	{
		return (add_proc_list(list, create_proc_node(word)));
	}
	else
	{
		curr_proc = get_last_proc(list);
		if (!curr_proc)
			return (true);
		if (!curr_proc->cmd)
		{
			curr_proc->cmd = ft_strdup(word);
			curr_proc->cmd_args = add_cmd_args(curr_proc->cmd_args, word);
			return (!curr_proc->cmd);
		}
		else
			return (append_word_to_cmd(curr_proc, word));
	}
	return (false);
}

bool	add_proc_list(t_proc **list, t_proc *new)
{
	t_proc	*temp;

	if (!new)
		return (true);
	if (*list == NULL)
		*list = new;
	else
	{
		temp = get_last_proc(list);
		temp->next = new;
	}
	return (false);
}

static char	**add_cmd_args(char **old, char *word)
{
	char	**new;
	int		size;

	size = count_double_string_array(old);
	new = ft_calloc(sizeof(char *), size + 1 + 1);
	if (!new)
		return (NULL);
	copy_double_string_array(old, new, word);
	free_string_double_array(old);
	old = NULL;
	return (new);
}
