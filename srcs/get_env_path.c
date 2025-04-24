/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:01:36 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/23 16:22:32 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**add_slash_last(char **path);

char	**get_env_path(t_minishell *m_shell)
{
	char	**path;
	char	*temp;
	t_env	*path_env;
	char	**env_path;

	path_env = search_env("PATH", m_shell->env);
	if (!path_env)
		return (NULL);
	temp = path_env->value;
	path = ft_split(temp, ':');
	if (!path)
		return (NULL);
	env_path = add_slash_last(path);
	if (!env_path)
		free_string_double_array(path);
	return (env_path);
}

static char	**add_slash_last(char **path)
{
	int		i;
	char	*post_path;

	i = 0;
	while (path[i])
	{
		post_path = add_slash(path[i]);
		free(path[i]);
		path[i] = post_path;
		i++;
	}
	return (path);
}
