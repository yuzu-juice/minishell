/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 13:03:04 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/23 17:22:30 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

static bool			add_to_cmd(t_proc_list **list, char *word);
static bool			add_space(t_proc_list *curr);
static t_proc_list	*create_node(char *word);
static t_proc		*create_proc(char *word);
static bool			add_proc_list(t_proc_list **list, t_proc_list *new);
t_proc_list			*get_last_proc(t_proc_list **list);

t_proc_list	*create_process_list(t_token **head)
{
	t_proc_list	*list;
	t_token		*curr;
	bool		err_flg;

	list = NULL;
	err_flg = false;
	curr = *head;
	while (curr)
	{
		if (ft_strcmp(curr->word, "|") == 0)
		{
			printf("this is pipe\n");
			err_flg = add_proc_list(&list, create_node(NULL));
			curr = curr->next;
		}
		else
		{
			printf("add to cmd\n");
			err_flg = add_to_cmd(&list, curr->word);
		}
		if (err_flg)
			break ;
		curr = curr->next;
	}

	t_proc_list *test;
	test = list;
	while (test)
	{
		printf("cmd %s\n", test->proc->cmd);
		test = test->next;
	}
	return (list);
}

static t_proc_list	*create_node(char *word)
{
	t_proc_list	*node;

	node = (t_proc_list *)ft_calloc(sizeof(t_proc_list), 1);
	if (!node)
		return (NULL);
	node->proc = create_proc(word);
	node->next = NULL;
	return (node);
}

static t_proc	*create_proc(char *word)
{
	t_proc	*proc;

	proc = (t_proc *)ft_calloc(sizeof(proc), 1);
	if (!proc)
		return (NULL);
	proc->cmd = word;
	proc->status = 0;
	return (proc);
}

static bool	add_to_cmd(t_proc_list **list, char *word)
{
	t_proc_list	*curr;
	char		*temp;
	bool		err_flg;

	err_flg = false;
	curr = get_last_proc(list);
	if (*list == NULL || curr->proc->cmd == NULL)
	{
		printf("new create node\n");
		err_flg = add_proc_list(list, create_node(word));
	}
	else
	{
		// curr = get_last_proc(list);
		if (curr->proc->cmd)
		{
			printf("add cmd\n");
			err_flg = add_space(curr);
		}
		if (err_flg)
			return (true);
		temp = ft_strjoin(curr->proc->cmd, word);
		if (!temp)
			return (true);
		free(curr->proc->cmd);
		curr->proc->cmd = temp;
	}
	return (false);
}

static bool	add_proc_list(t_proc_list **list, t_proc_list *new)
{
	t_proc_list	*temp;

	if (!new)
		return (true);
	if (*list == NULL)
	{
		*list = new;
	}
	else
	{
		temp = *list;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = new;
	}
	return (false);
}

static bool	add_space(t_proc_list *curr)
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
