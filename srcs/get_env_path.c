/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:01:36 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/02 19:09:13 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**add_slash(char **path);

char	**get_env_path(void)
{
	char	**path;
	char	*temp;
	int		i;
	char	**env_path;

	i = 0;
	temp = getenv("PATH");
	if (!temp)
		return (NULL);
	path = ft_split(temp, ':');
	if (!path)
		return (NULL);
	env_path = add_slash(path);
	if (!env_path)
		free_string_double_array(path);
	return (env_path);
}

static char	**add_slash(char **path)
{
	int		i;
	char	*post_path;

	i = 0;
	while (path[i])
	{
		post_path = ft_strjoin(path[i], "/");
		if (!post_path)
			return (NULL);
		free(path[i]);
		path[i] = post_path;
		i++;
	}
	return (path);
}
