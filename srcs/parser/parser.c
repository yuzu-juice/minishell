/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:22:31 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/06 17:07:04 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_proc(t_proc *proc);

bool	parser(char *line, t_minishell *m_shell)
{
	t_token	*head;
	t_proc	*proc;

	head = NULL;
	if (has_unclosed_quotes(line))
	{
		syntax_error(&head);
		return (true);
	}
	head = create_token_list(line);
	if (!head)
		return (true);
	if (expand_dollar(&head, m_shell->env))
		return (true);
	proc = create_process_list(&head);
	free_token_list(&head);
	if (!proc)
	{
		ft_putendl_fd("syntax_error", 2);
		return (true);
	}
	m_shell->proc = proc;
	m_shell->proc_count = count_proc(proc);
	return (false);
}

bool	has_unclosed_quotes(char *line)
{
	int		i;
	int		j;
	char	type;

	i = 0;
	j = 0;
	type = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (line[i] == '\'')
				type = '\'';
			if (line[i] == '\"')
				type = '\"';
			j = i + 1;
			while (line[j] != type && j < (int)ft_strlen(line))
				j++;
			if (j == (int)ft_strlen(line))
				return (true);
			i = j;
		}
		i++;
	}
	return (false);
}

void	syntax_error(t_token **head)
{
	ft_putendl_fd("syntax_error", 2);
	free_token_list(head);
}

static int	count_proc(t_proc *proc)
{
	int		count;
	t_proc	*curr;

	count = 0;
	curr = proc;
	while (curr)
	{
		count++;
		curr = curr->next;
	}
	return (count);
}
