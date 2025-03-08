/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:49:14 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/08 14:19:14 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env_pwd(void)
{
	char	*path;
	char	*env_pwd;

	path = getenv("PWD");
	if (path == NULL)
		return (NULL);
	env_pwd = add_slash(path);
	if (!env_pwd)
		return (NULL);
	return (env_pwd);
}
