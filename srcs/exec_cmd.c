/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:11:36 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/08 17:46:24 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char			**create_cmd_args(char *cmd);
static t_builtin	resolve_builtin_cmd(char *cmd);
static void			exec_builtin(char **cmd_args, \
								t_builtin cmd, \
								t_minishell *m_shell);
static void			remove_args_quotes(char **cmd_args);

void	exec_cmd(t_minishell *m_shell, \
				char *cmd, \
				int proc_index, \
				int pipe_fd[2][2])
{
	char		*cmd_path;
	char		**cmd_args;
	t_builtin	builtin_cmd;
	char		**envp;

	change_fds(m_shell, proc_index, pipe_fd);
	cmd_args = create_cmd_args(cmd);
	if (cmd_args == NULL)
		perror(NULL);
	remove_args_quotes(cmd_args);
	builtin_cmd = resolve_builtin_cmd(cmd_args[0]);
	if (builtin_cmd != NOT_A_BUILTIN_COMMAND)
	{
		exec_builtin(cmd_args, builtin_cmd, m_shell);
		return ;
	}
	cmd_path = create_cmd_path(cmd);
	if (cmd_path == NULL)
	{
		perror(NULL);
		exit(1);
	}
	envp = list_to_envp(m_shell->env);
	if (execve(cmd_path, cmd_args, envp) == -1)
	{
		perror(NULL);
		write(2, "cmd: ", 5);
		write(2, cmd, ft_strlen(cmd));
		write(2, "\n", 1);
		exit(1);
	}
	free_string_double_array(envp);
}

static void	remove_args_quotes(char **cmd_args)
{
	int	i;

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

static t_builtin	resolve_builtin_cmd(char *cmd)
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

static void	exec_builtin(char **cmd_args, \
						t_builtin builtin_cmd, \
						t_minishell *m_shell)
{
	int	i;

	i = 0;
	while (cmd_args[i] != NULL)
		i++;
	if (builtin_cmd == ECHO)
		echo(i, cmd_args);
	else if (builtin_cmd == PWD)
		pwd(i);
	else if (builtin_cmd == CD)
		cd(i, cmd_args);
	else if (builtin_cmd == UNSET)
		unset(i, cmd_args, m_shell);
	else if (builtin_cmd == ENV)
		env(i, m_shell);
	else if (builtin_cmd == EXPORT)
		export(i, cmd_args, m_shell);
	else if (builtin_cmd == EXIT)
		minishell_exit(i, cmd_args);
	free_string_double_array(cmd_args);
}
