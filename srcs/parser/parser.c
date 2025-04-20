/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 04:43:30 by takitaga          #+#    #+#             */
/*   Updated: 2025/04/20 15:44:30 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int		count_proc(t_proc *proc);
static bool		initial_syntax_checks(char *line, t_token **head_ptr);
static t_proc	*tokenize_expand_and_validate(t_token **head_ptr,
					t_minishell *m_shell);

bool	parser(char *line, t_minishell *m_shell)
{
	t_token	*head;
	t_proc	*proc;

	head = NULL;
	if (initial_syntax_checks(line, &head))
		return (true);
	proc = tokenize_expand_and_validate(&head, m_shell);
	free_token_list(&head);
	if (!proc)
		return (true);
	m_shell->proc = proc;
	m_shell->proc_count = count_proc(proc);
	return (false);
}

static bool	initial_syntax_checks(char *line, t_token **head_ptr)
{
	t_token	*tmp;

	if (has_unclosed_quotes(line))
	{
		syntax_error(head_ptr);
		return (true);
	}
	*head_ptr = create_token_list(line);
	if (!*head_ptr)
		return (true);
	tmp = *head_ptr;
	while (tmp)
	{
		if (is_redirection(tmp->word))
		{
			if ((tmp->next && is_redirection(tmp->next->word)) || !tmp->next)
			{
				syntax_error(head_ptr);
				return (true);
			}
		}
		tmp = tmp->next;
	}
	return (false);
}

static t_proc	*tokenize_expand_and_validate(t_token **head_ptr,
					t_minishell *m_shell)
{
	t_proc	*proc;

	if (expand_dollar(head_ptr, m_shell))
	{
		free_token_list(head_ptr);
		return (NULL);
	}
	proc = create_process_list(head_ptr);
	if (!proc)
	{
		ft_putendl_fd("syntax_error", 2);
		return (NULL);
	}
	return (proc);
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

static int	count_proc(t_proc *proc)
{
	int		count;
	int		index;
	t_proc	*curr;

	count = 0;
	index = 0;
	curr = proc;
	while (curr)
	{
		count++;
		curr->index = index;
		curr = curr->next;
		index++;
	}
	return (count);
}
