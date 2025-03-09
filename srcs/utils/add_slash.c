/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_slash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 14:03:46 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/08 14:41:43 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*add_slash(char *path)
{
	char	*post_path;

	post_path = ft_strjoin(path, "/");
	if (!post_path)
		return (NULL);
	return (post_path);
}
