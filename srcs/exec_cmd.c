/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:11:36 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/27 11:19:41 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_execve_err(char *cmd, t_proc *proc);
static void	print_permission_err(char *cmd, t_proc *proc);
static void	print_no_such_file_error(char *cmd, t_proc *proc);

void	exec_cmd(t_minishell *m_shell, t_proc *proc)
{
	char		*cmd_path;
	t_builtin	builtin_cmd;
	char		**envp;

	if (proc->cmd_args == NULL)
		return ;
	remove_args_quotes(proc->cmd_args);
	builtin_cmd = resolve_builtin_cmd(proc->cmd_args[0]);
	if (builtin_cmd != NOT_A_BUILTIN_COMMAND)
		exit(exec_builtin(proc->cmd_args, builtin_cmd, m_shell));
	if (ft_strcmp(proc->cmd_args[0], "") == 0)
		print_no_such_file_error("", proc);
	cmd_path = create_cmd_path(proc->cmd_args[0], m_shell);
	if (cmd_path == NULL)
	{
		perror(NULL);
		exit(1);
	}
	if (access(cmd_path, F_OK) != 0)
		print_no_such_file_error(cmd_path, proc);
	if (access(cmd_path, X_OK) != 0)
		print_permission_err(cmd_path, proc);
	envp = list_to_envp(m_shell->env);
	if (execve(cmd_path, proc->cmd_args, envp) < 0)
		print_execve_err(proc->cmd_args[0], proc);
}

void	remove_args_quotes(char **cmd_args)
{
	int		i;

	if (cmd_args == NULL)
		return ;
	i = 0;
	while (cmd_args[i] != NULL)
	{
		cmd_args[i] = remove_quotes(cmd_args[i]);
		i++;
	}
}

static void	print_execve_err(char *cmd, t_proc *proc)
{
	write(2, "cmd: ", 5);
	write(2, cmd, ft_strlen(cmd));
	write(2, ":", 1);
	perror(NULL);
	free_string_double_array(proc->cmd_args);
	free_redirection_list(&proc->redir);
	free(proc);
	exit(127);
}

static void	print_permission_err(char *cmd, t_proc *proc)
{
	write(2, "cmd: ", 5);
	write(2, cmd, ft_strlen(cmd));
	write(2, ":", 1);
	write(2, "permission denied\n", 19);
	free_string_double_array(proc->cmd_args);
	free_redirection_list(&proc->redir);
	free(proc);
	exit(126);
}

static void	print_no_such_file_error(char *cmd, t_proc *proc)
{
	(void)proc;
	write(2, "cmd: ", 5);
	write(2, cmd, ft_strlen(cmd));
	write(2, ":", 1);
	write(2, "not found\n", 11);
	exit(127);
}
