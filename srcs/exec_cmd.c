/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:11:36 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/16 12:29:08 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char			**create_cmd_args(char *cmd);
static t_builtin	resolve_builtin_cmd(char *cmd);
static void			exec_builtin(char **cmd_args, t_builtin cmd);

void	exec_cmd(char **envp, char *cmd)
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
		exec_builtin(cmd_args, builtin_cmd);
	cmd_path = create_cmd_path(cmd);
	if (cmd_path == NULL)
		perror(NULL);
	if (execve(cmd_path, cmd_args, envp) == -1)
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
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (ECHO);
	return (NOT_A_BUILTIN_COMMAND);
}

static void	exec_builtin(char **cmd_args, t_builtin builtin_cmd)
{
	int	i;

	i = 0;
	while (cmd_args[i] != NULL)
		i++;
	if (builtin_cmd == ECHO)
		echo(i, cmd_args);
	free_string_double_array(cmd_args);
	exit(EXIT_SUCCESS);
}
