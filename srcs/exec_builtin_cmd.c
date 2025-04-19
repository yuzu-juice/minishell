/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 13:18:47 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/18 17:04:21 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**create_cmd_args(t_proc *proc);

t_builtin	resolve_builtin_cmd(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (ECHO);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (PWD);
	if (ft_strcmp(cmd, "cd") == 0)
		return (CD);
	if (ft_strcmp(cmd, "unset") == 0)
		return (UNSET);
	if (ft_strcmp(cmd, "env") == 0)
		return (ENV);
	if (ft_strcmp(cmd, "export") == 0)
		return (EXPORT);
	if (ft_strcmp(cmd, "exit") == 0)
		return (EXIT);
	return (NOT_A_BUILTIN_COMMAND);
}

int	exec_builtin(char **cmd_args, \
						t_builtin builtin_cmd, \
						t_minishell *m_shell)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (cmd_args[i] != NULL)
		i++;
	if (builtin_cmd == ECHO)
		status = echo(i, cmd_args);
	else if (builtin_cmd == PWD)
		status = pwd(i);
	else if (builtin_cmd == CD)
		status = cd(i, cmd_args);
	else if (builtin_cmd == UNSET)
		status = unset(i, cmd_args, m_shell);
	else if (builtin_cmd == ENV)
		status = env(i, m_shell);
	else if (builtin_cmd == EXPORT)
		status = export(i, cmd_args, m_shell);
	else if (builtin_cmd == EXIT)
		status = minishell_exit(i, cmd_args);
	free_string_double_array(cmd_args);
	return (status);
}

bool	exec_parent_bultin_cmd(t_minishell *m_shell, t_proc *proc)
{
	char	**cmd_args;
	int		builtin_cmd;

	if (m_shell->proc_count != 1)
		return (false);
	cmd_args = create_cmd_args(proc);
	if (cmd_args == NULL)
	{
		perror(NULL);
		return (true);
	}
	remove_args_quotes(cmd_args);
	builtin_cmd = resolve_builtin_cmd(cmd_args[0]);
	if (builtin_cmd == NOT_A_BUILTIN_COMMAND)
		return (false);
	m_shell->prev_status = exec_builtin(cmd_args, builtin_cmd, m_shell);
	return (true);
}

static char	**create_cmd_args(t_proc *proc)
{
	char	**cmd_args;
	t_token	*token;
	int		count_word;
	int		i;

	count_word = count_token(&proc->token);
	cmd_args = (char **)ft_calloc(sizeof(char *), count_word + 1);
	if (!cmd_args)
		return (NULL);
	token = proc->token;
	i = 0;
	while (token)
	{
		cmd_args[i] = ft_strdup(token->word);
		if (!cmd_args[i])
		{
			free_string_double_array(cmd_args);
			return (NULL);
		}
		i++;
		token = token->next;
	}
	cmd_args[i] = NULL;
	return (cmd_args);
}
