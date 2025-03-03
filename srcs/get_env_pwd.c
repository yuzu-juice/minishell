/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:49:14 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/02 19:09:16 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*add_slash(char *path);

char	*get_env_pwd(void)
{
	char	*path;
	int		i;
	char	*env_pwd;

	i = 0;
	path = getenv("PWD");
	if (path == NULL)
		return (NULL);
	env_pwd = add_slash(path);
	if (!env_pwd)
		return (NULL);
	return (env_pwd);
}

static char	*add_slash(char *path)
{
	char	*post_path;

	post_path = ft_strjoin(path, "/");
	if (!post_path)
		return (NULL);
	return (post_path);
}
