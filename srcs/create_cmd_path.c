/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:20:30 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/26 13:43:20 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*search_exec_cmd_path(char **env_path, char *cmd);
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
	full_path = search_exec_cmd_path(env_path, cmd);
	free_string_double_array(env_path);
	return (full_path);
}

static char	*search_exec_cmd_path(char **env_path, char *cmd)
{
	char	*full_path;
	int		i;
	char	*cmd_only;

	cmd_only = get_cmd_only(cmd);
	if (!cmd_only)
		return (NULL);
	i = 0;
	while (env_path[i])
	{
		full_path = ft_strjoin(env_path[i], cmd_only);
		if (!full_path)
		{
			free(cmd_only);
			return (NULL);
		}
		if (access(full_path, F_OK) == 0)
		{
			free(cmd_only);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	return (cmd_only);
}

static char	*get_cmd_only(char *cmd)
{
	bool	has_space;
	int		i;
	char	**temp;
	char	*result;

	has_space = false;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == ' ')
			has_space = true;
		i++;
	}
	if (!has_space)
		return (ft_strdup(cmd));
	temp = ft_split(cmd, ' ');
	if (!temp)
		return (NULL);
	result = ft_strdup(temp[0]);
	if (!result)
		return (free_string_double_array(temp), NULL);
	free_string_double_array(temp);
	return (result);
}
