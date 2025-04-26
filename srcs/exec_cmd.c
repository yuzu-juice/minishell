/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:11:36 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/25 18:40:53 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_execve_err(char *cmd);
static void	print_permission_err(char *cmd);

void	exec_cmd(t_minishell *m_shell, \
	t_proc *proc, \
	int pipe_fd[2][2])
{
	char		*cmd_path;
	t_builtin	builtin_cmd;
	char		**envp;

	if (m_shell->proc_count > 1)
		change_fds(m_shell, proc->index, pipe_fd);
	remove_args_quotes(proc->cmd_args);
	builtin_cmd = resolve_builtin_cmd(proc->cmd_args[0]);
	if (builtin_cmd != NOT_A_BUILTIN_COMMAND)
		exit(exec_builtin(proc->cmd_args, builtin_cmd, m_shell));
	cmd_path = create_cmd_path(proc->cmd_args[0], m_shell);
	if (cmd_path == NULL)
	{
		perror(NULL);
		exit(1);
	}
	if (access(cmd_path, X_OK) != 0)
		print_permission_err(cmd_path);
	envp = list_to_envp(m_shell->env);
	if (execve(cmd_path, proc->cmd_args, envp) < 0)
		print_execve_err(proc->cmd);
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

static void	print_execve_err(char *cmd)
{
	perror(NULL);
	write(2, "cmd: ", 5);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	exit(127);
}

static void	print_permission_err(char *cmd)
{
	write(2, "permission denied\n", 19);
	write(2, "cmd: ", 5);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	exit(126);
}
