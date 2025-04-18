/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:11:36 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/18 14:02:21 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**create_cmd_args(char *cmd);
static void	print_execve_err(char *cmd);

void	exec_cmd(t_minishell *m_shell, \
				char *cmd, \
				int proc_index, \
				int pipe_fd[2][2])
{
	char		*cmd_path;
	char		**cmd_args;
	t_builtin	builtin_cmd;
	char		**envp;

	if (m_shell->proc_count > 1)
		change_fds(m_shell, proc_index, pipe_fd);
	cmd_args = create_cmd_args(cmd);
	if (cmd_args == NULL)
		perror(NULL);
	remove_args_quotes(cmd_args);
	builtin_cmd = resolve_builtin_cmd(cmd_args[0]);
	if (builtin_cmd != NOT_A_BUILTIN_COMMAND)
	{
		exit(exec_builtin(cmd_args, builtin_cmd, m_shell));
	}
	cmd_path = create_cmd_path(cmd);
	if (cmd_path == NULL)
	{
		perror(NULL);
		exit(1);
	}
	envp = list_to_envp(m_shell->env);
	if (execve(cmd_path, cmd_args, envp) < 0)
		print_execve_err(cmd);
}

void	remove_args_quotes(char **cmd_args)
{
	int		i;

	i = 0;
	while (cmd_args[i] != NULL)
	{
		cmd_args[i] = remove_quotes(cmd_args[i]);
		i++;
	}
}

static char	**create_cmd_args(char *cmd)
{
	char	**cmd_args;

	cmd_args = ft_split(cmd, ' ');
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
