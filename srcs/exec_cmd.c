/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:11:36 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/02 19:08:20 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**create_cmd_args(char *cmd);

void	exec_cmd(char **envp, char *cmd)
{
	char	*cmd_path;
	char	**cmd_args;

	cmd_path = create_cmd_path(cmd);
	if (cmd_path == NULL)
		perror(NULL);
	cmd_args = create_cmd_args(cmd);
	if (execve(cmd_path, cmd_args, envp) == -1)
		perror(NULL);
}

static char	**create_cmd_args(char *cmd)
{
	char	**cmd_args;

	cmd_args = ft_split(cmd, ' ');
	return (cmd_args);
}
