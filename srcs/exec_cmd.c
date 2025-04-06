/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:11:36 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/06 11:56:42 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char			**create_cmd_args(char *cmd);
static t_builtin	resolve_builtin_cmd(char *cmd);
static void			exec_builtin(char **cmd_args, t_builtin cmd, t_env **envp);

void	exec_cmd(t_env **env, char *cmd)
{
	char		*cmd_path;
	char		**cmd_args;
	t_builtin	builtin_cmd;
	int			i;

	i = 0;
	cmd_args = create_cmd_args(cmd);
	if (cmd_args == NULL)
		perror(NULL);
	while (cmd_args[i] != NULL)
	{
		cmd_args[i] = remove_quotes(cmd_args[i]);
		i++;
	}
	builtin_cmd = resolve_builtin_cmd(cmd_args[0]);
	if (builtin_cmd != NOT_A_BUILTIN_COMMAND)
	{
		exec_builtin(cmd_args, builtin_cmd, env);
		return ;
	}
	cmd_path = create_cmd_path(cmd);
	if (cmd_path == NULL)
		perror(NULL);
	if (execve(cmd_path, cmd_args, list_to_envp(*env)) == -1)
		perror(NULL);
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

static void	exec_builtin(char **cmd_args, t_builtin builtin_cmd, t_env **envp)
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
		unset(i, cmd_args, envp);
	else if (builtin_cmd == ENV)
		env(i, *envp);
	else if (builtin_cmd == EXPORT)
		export(i, cmd_args, envp);
	else if (builtin_cmd == EXIT)
		minishell_exit(i, cmd_args);
	free_string_double_array(cmd_args);
}
