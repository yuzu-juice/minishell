/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:11:36 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/02 15:00:10 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**create_cmd_args(char *cmd);

/*
	allow command and command args
	ex)
	exec_cmd(envp, "ls -l"); -> OK
	exec_cmd(envp, "./a.out"); -> OK
	exec_cmd(envp, "/usr/bin/ls"); -> OK
	exec_cmd(envp, "ls -l home/yohatana/work/minishell"); -> OK
	exec_cmd(envp, "echo "echos args string""); -> OK
	exec_cmd(envp, "ls -l > outfile"); -> NG
*/
void	exec_cmd(char **envp, char *cmd)
{
	char	*cmd_path;
	char	**cmd_args;

	cmd_path = create_cmd_path(envp, cmd);
	if (cmd_path == NULL)
		perror("");
	cmd_args = create_cmd_args(cmd);
	if (execve(cmd_path, cmd_args, envp) == -1)
		perror("");
}

static char	**create_cmd_args(char *cmd)
{
	char	**cmd_args;

	cmd_args = ft_split(cmd, ' ');
	return (cmd_args);
}
