/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:49:14 by yohatana          #+#    #+#             */
/*   Updated: 2025/02/25 17:29:19 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*add_slash(char *path);

char	*get_env_pwd(char **envp)
{
	char	*path;
	int		i;
	char	*env_pwd;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], PWD, 4) == 0)
			break ;
		i++;
	}
	if (envp[i] == NULL)
		perror("env pwd can not get");
	path = ft_strtrim(envp[i], PWD);
	if (!path)
		return (NULL);
	env_pwd = add_slash(path);
	if (!env_pwd)
		return (NULL);
	return (env_pwd);
}

static char	*add_slash(char *path)
{
	int		i;
	char	*post_path;

	i = 0;
	post_path = ft_strjoin(path, "/");
	if (!post_path)
		return (NULL);
	return (path);
}
