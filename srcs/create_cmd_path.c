/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:20:30 by yohatana          #+#    #+#             */
/*   Updated: 2025/02/28 16:12:19 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*serch_exec_cmd_path(char **env_path, char *cmd);
static char	*get_cmd_only(char *cmd);
static void	free_path(char **env_path);

// TODO :serch_exec_cmd_path()
// 	when 'return cmd_only',
// 	error message shoud be "command not found"
char	*create_cmd_path(char **envp, char *cmd)
{
	char	*full_path;
	char	*dir_path;
	char	*cmd_only;
	char	**env_path;

	full_path = NULL;
	if (cmd[0] == '/')
		return (ft_strdup(cmd));
	else if (cmd[0] == '.')
	{
		dir_path = get_env_pwd(envp);
		cmd_only = ft_strtrim(cmd, "./");
		full_path = ft_strjoin(dir_path, cmd_only);
		free(dir_path);
		free(cmd_only);
		return (full_path);
	}
	env_path = get_env_path(envp);
	full_path = serch_exec_cmd_path(env_path, cmd);
	free_path(env_path);
	return (full_path);
}

static void	free_path(char **env_path)
{
	int	i;

	if (env_path == NULL)
		return ;
	i = 0;
	while (env_path[i])
	{
		free(env_path[i]);
		i++;
	}
	free(env_path);
}

static char	*serch_exec_cmd_path(char **env_path, char *cmd)
{
	char	*full_path;
	int		i;
	char	*cmd_only;

	cmd_only = get_cmd_only(cmd);
	i = 0;
	while (env_path[i])
	{
		full_path = ft_strjoin(env_path[i], cmd_only);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (cmd_only);
}

static char	*get_cmd_only(char *cmd)
{
	int		space_flg;
	int		i;
	char	**temp;
	char	*result;

	space_flg = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == ' ')
			space_flg = 1;
		i++;
	}
	if (space_flg == 0)
		return (ft_strdup(cmd));
	temp = ft_split(cmd, ' ');
	if (!temp)
		return (NULL);
	result = ft_strdup(temp[0]);
	if (!result)
		return (NULL);
	free_path(temp);
	return (result);
}
