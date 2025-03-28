/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:01:36 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/08 14:19:18 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**add_slash_last(char **path);

char	**get_env_path(void)
{
	char	**path;
	char	*temp;
	char	**env_path;

	temp = getenv("PATH");
	if (!temp)
		return (NULL);
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
