/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:11:36 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/18 17:04:30 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**create_cmd_args(t_proc *proc);
static void	print_execve_err(char *cmd);

void	exec_cmd(t_minishell *m_shell, \
	t_proc *proc, \
	int pipe_fd[2][2])
{
	char		*cmd_path;
	char		**cmd_args;
	t_builtin	builtin_cmd;
	char		**envp;

	if (m_shell->proc_count > 1)
		change_fds(m_shell, proc->index, pipe_fd);
	cmd_args = create_cmd_args(proc);
	if (cmd_args == NULL)
		perror(NULL);
	remove_args_quotes(cmd_args);
	builtin_cmd = resolve_builtin_cmd(cmd_args[0]);
	if (builtin_cmd != NOT_A_BUILTIN_COMMAND)
	{
		exit(exec_builtin(cmd_args, builtin_cmd, m_shell));
	}
	cmd_path = create_cmd_path(proc->cmd);
	if (cmd_path == NULL)
	{
		perror(NULL);
		exit(1);
	}
	envp = list_to_envp(m_shell->env);
	if (execve(cmd_path, cmd_args, envp) < 0)
		print_execve_err(proc->cmd);
}

void	remove_args_quotes(char **cmd_args)
{
	int	i;

	i = 0;
	while (cmd_args[i] != NULL)
	{
		cmd_args[i] = remove_quotes(cmd_args[i]);
		i++;
	}
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

static void	print_execve_err(char *cmd)
{
	perror(NULL);
	write(2, "cmd: ", 5);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	exit(1);
}
