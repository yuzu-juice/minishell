/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:20:30 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/25 19:14:11 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*serch_exec_cmd_path(char **env_path, char *cmd);
static char	*get_cmd_only(char *cmd);

char	*create_cmd_path(char *cmd, t_minishell *m_shell)
{
	char	*full_path;
	char	**env_path;

	full_path = NULL;
	if (cmd[0] == '/' || cmd[0] == '.')
		return (get_cmd_only(cmd));
	env_path = get_env_path(m_shell);
	if (env_path == NULL)
		return (get_cmd_only(cmd));
	full_path = serch_exec_cmd_path(env_path, cmd);
	free_string_double_array(env_path);
	return (full_path);
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
		free(cmd_only);
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
	free_string_double_array(temp);
	return (result);
}
