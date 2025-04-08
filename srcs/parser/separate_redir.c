/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:12:49 by takitaga          #+#    #+#             */
/*   Updated: 2025/04/08 19:49:37 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool					is_valid_redir(char *cmd);
static t_redirection_type	redir_type(char *cmd);

void	separate_redir(t_proc *proc)
{
	t_proc	*tmp;
	char	*cmd;
	char	**splited_str;
	char	*redir_char;

	tmp = proc;
	while (tmp)
	{
		cmd = ft_strdup(tmp->cmd);
		if (!is_valid_redir(cmd))
			return ;
		tmp->redir->type = redirection_type(cmd);
		if (tmp->redir->type == INPUT)
			redir_char = "<";
		else if (tmp->redir->type == OUTPUT)
			redir_char = ">";
		else if (tmp->redir->type == APPEND)
			redir_char = ">>";
		else if (tmp->redir->type == HEREDOC)
			redir_char = "<<";
		splited_str = split_string(cmd, DELIMITER);
		if (split_string == NULL)
			return ;
		tmp->cmd = splited_str[0];
		cmd = splited_str[1];
		tmp->redir->type = redirection_type(cmd);
		while (splited_str[1])
		{
			splited_str[0];
		}
		tmp->cmd = split_string(cmd, DELIMITER);
		tmp = tmp->next;
		free(cmd);
	}
}

static bool	is_valid_redir(char *cmd)
{
	if (ft_strchr(cmd, '<') || ft_strchr(cmd, '>'))
		return (true);
	return (false);
}

static t_redirection_type	redirection_type(char *cmd)
{
	if (ft_strnstr(cmd, ">>", ft_strlen(cmd)) != NULL)
		return (APPEND);
	if (ft_strnstr(cmd, "<<", ft_strlen(cmd)) != NULL)
		return (HEREDOC);
	if (ft_strnstr(cmd, ">", ft_strlen(cmd)) != NULL)
		return (OUTPUT);
	if (ft_strnstr(cmd, "<", ft_strlen(cmd)) != NULL)
		return (INPUT);
}
